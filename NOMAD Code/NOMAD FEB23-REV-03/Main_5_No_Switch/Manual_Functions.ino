// == NETWORK

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false; // https://www.arduino.cc/en/pmwiki.php?n=Reference/Static
  static byte ndx = 0; // Static means that variables aren't destroyed once this function ends, but can't be accessed outside of it
  // "static variables persist beyond the function call, preserving their data between function calls"

  char startMarker = '<';
  char endMarker = '>'; // Markers to signify the start and end of a packet
  char rc; // Holds the incoming string

  while (Serial.available() > 0 && newData == false) { // Checks if there is data in the Serial Monitor. Loops until newData becomes true on line 65, when the current string is finished being read
    rc = Serial.read(); // Stores the incoming data into a character variable

    if (rc == startMarker) {
      recvInProgress = true;
    }
    else if (recvInProgress == true) { // Copies the received string into another for manipulation
      if (rc != endMarker) { // Ensures that the final marker hasn't been read
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1; // Loops to store the array, and then sets ndx to the final character
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true; // Sets up for the next set of data
      }
    }
  }
}

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
  y_value = atoi(strtokIndx);    // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  x_value = atoi(strtokIndx);     // convert this part to a float

  strtokIndx = strtok(NULL, ">");     // get the first part - the string. Line 31 stores the incoming string into tempChars, which is a global variable and thus can be accessed here
  strcpy(switch_val, strtokIndx); // copy it to messageFromPC

  // Explaining strtok: https://www.cplusplus.com/reference/cstring/strtok/
  // strtok is able to save characters from a string into a pointer
  // char * strtok ( char * str, const char * delimiters );
  // pointer strtok(variable, character to stop at (non-inclusive));
  // First time its called, call the start of the string
  // Subsequent times use NULL to pick up from the last delimeter

  // These are all then saved as they go along, ready for manipulation
  // Ensure that these save locations are either global, or pointers passed to the function

}

// == MOVEMENT
void manual_move()
{
  // Iteration 1:
  /*
     Forward: Straight, slightly left, slightly right
     Backward: See Above

     SLight turns are achieved by sending a lower PWM to the other wheel

     Turns: Directly Right = CW, Directly Left = CCW (within a range)

     Distance from 0 and 1024 along y-axis for forward and backward dictate speed
     Distance from 0 and 1024 along x-axis for turns dictate speed

  */

  // X and Y distance are stored in x_value and y_value
  // Would it be easier to use vector math? Unnecessarily complex?

  // Origin has been measure to be about 507 to 520 then about 490 when mapped
  // Therefore, anything from 480 to 520 will be discarded
  int origin_min = 480;
  int origin_max = 520;
  // IN FUTURE MEASURE THE ORIGIN DURING THE FIRST FEW PACKETS

  // int slight_min =

  // ASSUMING 0,0 IS TOP RIGHT. THIS HAS BEEN MOVED TO THE THUMBSTICK SENDER ITSELF
  //y_value = map(y_value, 0, 1024, 1024, 0);
  //x_value = map(x_value, 0, 1024, 1024, 0);

  // === Forward and Backward

  if (origin_min < x_value < origin_max) // If x is in the middle, then go forward or backward
  {
    // Take the relative distance between y and its maxima/minima and feed it into the function for speed control
    if (y_value > origin_max)
    {
      // y_value = map(y_value,0,1024, 0, 255);
      nomad_forward(toSpeed(y_value));
    }
    else if (y_value < origin_min)
      nomad_backward(toSpeed(y_value));
  }

  // === CW and CCW
  if (origin_min < y_value < origin_max)
  {
    if (x_value > origin_max)
    {
      nomad_CCW(toSpeed(x_value));
    }
    else if (x_value < origin_min)
      nomad_CW(toSpeed(x_value));
  }

  // === Slights
  /*
     These are the most complicated action
     The combination between y and x dictates how much the robot turns
     The distance to the edge dictates the speed, yet this is dependent on BOTH not ONE

  */

  // === Forward Slightly Right and Slightly Left
  // If Y is greater than origin, and X is greater or less than origin, go slightly right

  // X is greater = FWR, lesser = FWL
  if (y_value > origin_max)
  {
    if (x_value > origin_max)
    {
      // GO FORWARD RIGHT
      //nomad_stop();


      // Left wheel's speed is dictated by Y-axis distance -> Higher = Faster -> Linear
      // Right wheel's speed is dictated by X-axis distance -> Higher = Slower -> Reversed
      int MA_speed = toSpeed(y_value);

      x_value = map(x_value, 520, 1024, 520, 0); // The greater the stick to right, the less the right motor needs to move
      int MB_speed = toSpeed(x_value);

      // Motor Combs:
      // void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
      // Motor A is left, Motor B is right

      nomad_forward_turn(MA_speed, MB_speed);
    }
    else if (x_value < origin_min)
    {
      // GO FORWARD LEFT
      //nomad_stop();

      // Motor A and Motor B are flipped for left turns

      int MB_speed = toSpeed(y_value);
      int MA_speed = toSpeed(x_value);

      // Motor Combs:
      // void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
      // Motor A is left, Motor B is right

      nomad_forward_turn(MA_speed, MB_speed);
    }
  }


  // === Backward Slightly Right and Slightly Left
  if (y_value < origin_min)
  {
    if (x_value > origin_max)
    {
      // GO BACKWARD RIGHT
      //nomad_stop();


      // Left wheel's speed is dictated by Y-axis distance -> Higher = Faster -> Linear
      // Right wheel's speed is dictated by X-axis distance -> Higher = Slower -> Reversed
      int MA_speed = toSpeed(y_value);

      x_value = map(x_value, 520, 1024, 520, 0);  // The greater the stick to right, the less the right motor needs to move
      int MB_speed = toSpeed(x_value);

      // Motor Combs:
      // void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
      // Motor A is left, Motor B is right

      nomad_backward_turn(MA_speed, MB_speed);
    }
    else if (x_value < origin_min)
    {
      // GO BACKWARD LEFT

      //nomad_stop();

      // Motor A and Motor B are flipped for left turns

      int MB_speed = toSpeed(y_value);
      int MA_speed = toSpeed(x_value);

      // Motor Combs:
      // void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
      // Motor A is left, Motor B is right

      nomad_backward_turn(MA_speed, MB_speed);
    }
  }
}

int toSpeed(int val)
{
  // IN FUTURE, 480 and 520 NEED TO BE MEASURED AND PASSED
  int min_pwm = 25;
  int max_pwm = 255;

  if (val > 520) // If the value is above origin, range from origin upwards
  {
    return map(val, 520, 1024, min_pwm, max_pwm);
  }

  else if (val < 480) // If the value is under origin, range from origin downwards and BACKWARDS
  {
    return map(val, 0, 520, max_pwm, min_pwm);
  }

  // return map(val,0,1024, 0, 255);
}
