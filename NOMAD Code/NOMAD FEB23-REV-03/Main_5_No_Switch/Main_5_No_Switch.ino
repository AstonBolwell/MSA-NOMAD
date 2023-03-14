// -- Program Start -- //
/*

   This program provides the simple relation between the sensors and actuators of the Nomad MK1

   When an edge is detected, a clockwise turn is actuated

   NEW:
   - Pin 13 is connected to a WIRE such that when it is pulled high, an infinite loop is entered
   - This will allow control of the robot using an ESP8266 Wireless Module
*/

// Manual Definitions

#define manual_pin 13

// Example 5 - Receive with start- and end-markers combined with parsing
// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
// This is intended to work with the Character_Array_Sender when the switch_val is disabled

// FOR SOME REASON, THE TX GOES TO RX AND RX TO TX WHEN USING A LOGIC LEVEL CONVERTOR
// IF THIS IS NOT OBEYED, THEN THE SENDER WILL OVERRIDE THE RECEIVER

const byte numChars = 32; // Size of the string coming in
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char switch_val[numChars] = {0};
int x_val = 0;
int y_val = 0;

boolean newData = false;

//float min_x = 400;
//float max_x = 600;

int x_value = 0;
int y_value = 0;

byte thumbstate[2] = {0, 0}; // Create an array to send to the serial monitor. Have to use BYTE https://forum.arduino.cc/t/serial-write-error-when-sending-an-array/139417

//============

// Defining Sensor Pins
/*
   The USS take all the analog pins (which act as digital GPIO) and pins 8 and 9
   They require an output sound and input reading, therefore two pins per sensor
*/
#define us1t A0 // UltraSonic 1 Trigger. Input
#define us1e A1 // UltraSonic 1 Echo. Output

#define us2t A2
#define us2e A3

#define us3t A4
#define us3e A5

#define us4t 8
#define us4e 9

// Defining Actuator Pins
/*
   Please see https://www.youtube.com/watch?v=dyjo_ggEtVU for a detailed explanation
*/

// Enables are PWM and take precedence for pin choice
#define enA 5
#define enB 6

// F/B are digital
#define in1 2 // Motor A Forward
#define in2 3 // Motor A Backward

#define in3 4 // Motor B Forward
#define in4 7 // Motor B Forward


// --- Defining Global Variables

// Sensor Array

int sens_array[] = {us1t, us1e, us2t, us2e, us3t, us3e, us4t, us4e};

// Other

bool edge_detected = false;

const int distance_to_table = 5;

float pi = 3.14;

int current_activated_sensor_trig = 0;

const int set_pwm = 175; // 255 = Full Speed, 0 = Stop. 100 is good for a slow speed

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

// --

bool canAuto = false; //This determines if the robot will go to auto when no data is found. Set to false to just stop

// Prototypes
void nomad_CW(int pwm_val = set_pwm);
void nomad_CCW(int pwm_val = set_pwm);
void nomad_forward(int pwm_val = set_pwm);
void nomad_backward(int pwm_val = set_pwm);
void nomad_stop();
void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm);
void nomad_backward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm);

void MA_PWM(char dir, int pwm_val);
void MB_PWM(char dir, int pwm_val);

bool USS_Looper();
bool USS_Looper_Forward(); // Only Loops the first two
bool USS_Looper_Backward(); // Only Loops the last two
int USS_Read(int trigPin, int echoPin);

void recvWithStartEndMarkers();
void parseData();

void manual_move();
int toSpeed(int val);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // Wire Pin 13 For Manual
  pinMode(manual_pin, INPUT_PULLUP);


  // Inputs
  // A0, A2, A4
  // D8
  pinMode(us1e, INPUT);
  pinMode(us2e, INPUT);
  pinMode(us3e, INPUT);
  pinMode(us4e, INPUT);

  // Outputs
  // A1, A3, A5
  // D9
  pinMode(us1t, OUTPUT);
  pinMode(us2t, OUTPUT);
  pinMode(us3t, OUTPUT);
  pinMode(us4t, OUTPUT);

  // D2 to D7
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // --------------  MANUAL MODE
  // Wire Pin 13 to GND for Auto, Wire HIGH for Manual

  // delay(20);
  // Decode UART comms
  recvWithStartEndMarkers(); // Receive the data

  if (newData == true)
  {
    strcpy(tempChars, receivedChars); // Store the actual data in a buffer
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0

    Serial.println(tempChars);

    if (isDigit(tempChars[0])) // If number, then Manual
    {
      char * strtokIndx; // this is used by strtok() as an index

      strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
      y_value = atoi(strtokIndx);    // convert this part to an integer
    
      strtokIndx = strtok(NULL, ">");
      x_value = atoi(strtokIndx);     // convert this part to a float
    
      strtokIndx = strtok(NULL, ">");     // get the first part - the string. Line 31 stores the incoming string into tempChars, which is a global variable and thus can be accessed here
      strcpy(switch_val, strtokIndx);

      //translate x and y joy inputs into l and r wheel speeds with MATH!! :D
      // 0 - 512 - 1024

      float r = sqrt(pow(x_value-512,2)+pow(y_value-512,2)); //polar coords (r & t)
      float t = atan2(y_value-512,x_value-512);
      
      t+=pi/4; //rotate polar coords by 45deg

      int left = round(r * cos(t) * sqrt(2)); //motor speeds
      int right = round(r * sin(t) * sqrt(2));

      Serial.print(left/2);
      Serial.print(",");
      Serial.println(right/2);

      if(r<10){
        nomad_stop(); //deadzone - stop motors        
      }else{
        //MA_PWM(left>0?'F':'B',abs(left)/2); //set motors
        //MB_PWM(right>0?'F':'B',abs(right)/2);

        //LEFT
        analogWrite(enA, abs(left)/2);
        digitalWrite(in1, left>0?HIGH:LOW);
        digitalWrite(in2, left>0?LOW:HIGH);

        //LEFT
        analogWrite(enB, abs(right)/2);
        digitalWrite(in3, right>0?HIGH:LOW);
        digitalWrite(in4, right>0?LOW:HIGH);
      }

      delay(100);
      // Loop
    }else{//Else stop
      //nomad_stop();
      //delay(1000);
    }
    newData = false; // Sets up for the next package of data
  }


  // --------------  AUTO MODE
  /*
     1. Go forward
     2. Cycle through all sensors. Ensure readings are all below the average of 15 cm or so
     3. IF distance exceeds, then turn clockwise
     4. Keep turning until all readings are less than the distance to the table
     5. Loop


  */

}
