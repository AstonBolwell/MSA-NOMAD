// ==================== Thumbstick Definitions ====================
#define thumbpin A0
#define aswitch D0


int x_val = 0;
char x_valstr[5] = {};

int y_val = 0;
char y_valstr[5] = {};

// ==================== Wifi Definitions ====================
/*
   PLEASE NOTE THAT A LOT OF THIS HAS JUST BEEN COPIED OVER FROM THE PREVIOUS, SEPERATE MODULES

   NOW, WE DO NOT NEED AN LLC IN THE FIRST STEP OR NEED TO PASS DATA BETWEEN BOARDS

   THE DATA IS PACKAGED AND SENT ON ONE BOARD

*/

//#include <MemoryFree.h>
//#include <pgmStrToRAM.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

// Set WIFI credentials
#define WIFI_SSID "BofaDeez"
#define WIFI_PASS "NuckulusRift" // PASSWORDS NEED TO BE LONGER THAN 8 CHARACTERS

// UDP
WiFiUDP UDP;
IPAddress remote_IP(192, 168, 4, 1);
#define UDP_PORT 4210

// Example 5 - Receive with start- and end-markers combined with parsing
// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
// This is intended to work with the Character_Array_Sender when the switch_val is disabled

// FOR SOME REASON, THE TX GOES TO RX AND RX TO TX WHEN USING A LOGIC LEVEL CONVERTOR
// IF THIS IS NOT OBEYED, THEN THE SENDER WILL OVERRIDE THE RECEIVER

const byte numChars = 32; // Size of the string coming in
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing
char sendingstr[200] = {0};

// variables to hold the parsed data
//char switch_val[numChars] = {0};
//int x_val = 0;
//int y_val = 0;

boolean newData = false;

int freeheap = 0;

void setup() {
  // Begin the Serial at 115200 Baud
  Serial.begin(115200);

  pinMode(aswitch, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  // ==================== Wifi Setup ====================

  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  Serial.println();

  // WiFi.persistent( false ); // https://stackoverflow.com/questions/44139082/esp8266-takes-long-time-to-connect. Although https://randomnerdtutorials.com/solved-reconnect-esp8266-nodemcu-to-wifi/ - For reconnecting last WiFi
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);

  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW. This is HIGH since reversed
}

void loop() {

  digitalWrite(aswitch, LOW);

  x_val = analogRead(thumbpin);

  delay(10);

  digitalWrite(aswitch, HIGH);

  delay(10);

  y_val = analogRead(thumbpin);

  delay(10);

  // ASSUMING 0,0 IS BOTTOM LEFT. THIS HAS BEEN COPIED SO EASIER HERE TO MEASURE
  y_val = map(y_val, 0, 1024, 1024, 0);
  x_val = map(x_val, 0, 1024, 1024, 0);

  // Time to package them using markers

  //Serial.print(x_val);
  //Serial.print(" , ");
  //Serial.println(y_val);

  itoa(x_val, x_valstr, 10);
  itoa(y_val, y_valstr, 10);

  startstring(sendingstr, x_valstr);
  endstring(sendingstr, y_valstr);

  //Serial.write(sendingstr, sizeof(sendingstr));
  //Serial.write('\n');

  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);
  UDP.write(sendingstr); // https://www.arduino.cc/en/Reference/EthernetUDPWrite
  UDP.endPacket();

  Serial.println(sendingstr);

  freeheap = ESP.getFreeHeap();
  // https://arduino-esp8266.readthedocs.io/en/latest/libraries.html

  Serial.println(freeheap);

  sendingstr[0] = '\0';
  // To reset a cstring simply set the value of the first index to 0 (or '\0'). https://forum.arduino.cc/t/solved-how-reset-a-char-array/537178

  //delay(10);

}

// https://forum.arduino.cc/t/passing-array-as-parameter/44562/4
// When you use a name of the array as an argument in a function call, the compiler treats it as a pointer whose
// value is the address of the first element of the array using pointer notation or using array notation.

void startstring(char str[], char startval[])
{
  strcat(str, "<");
  strcat(str, "<");
  strcat(str, "<");
  strcat(str, startval);
  strcat(str, ",");
}

void addstring(char str[], char stringtoadd[])
{
  strcat(str, stringtoadd);
  strcat(str, ",");
}

void endstring(char str[], char endval[])
{
  strcat(str, endval);
  strcat(str, ">");
  // Manual Null Termination
  //strcat(str, '\0');
}
