int USS_Read(int trigPin, int echoPin) // AX is treated as int for some reason bruh moment
{
  // Taken from https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6

   // defines variables
  long duration; // variable for the duration of sound wave travel
  int distance; // variable for the distance measurement
  
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  /* Here, we would rather return the distance
  // Displays the distance on the Serial Monitor
  // https://www.youtube.com/watch?v=xaqCPARmBjA
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  */

  return distance;
}

bool USS_Looper_Forward() // Only Loops the first two
{
  // int sens_array[] = {us1t,us1e,us2t,us2e,us3t,us3e,us4t,us4e};
  edge_detected = false;
  
  for(int i = 0; i <= 3; i+=2) // 01, 23, 45, 67 // Set i <= 3 to 7
  {
    int distance = 0;
    
    int current_trig = sens_array[i];
    int current_echo = sens_array[i + 1];
    
    distance = USS_Read(current_trig, current_echo);

    if (distance > distance_to_table)
    {
      current_activated_sensor_trig = i;
      edge_detected = true;
      break;
    }
    else
      current_activated_sensor_trig = 50; // Arbitrary number for the edge check
  }

  return edge_detected;
}

bool USS_Looper_Backward() // Only Loops the first two
{
  // int sens_array[] = {us1t,us1e,us2t,us2e,us3t,us3e,us4t,us4e};
  edge_detected = false;
  
  for(int i = 4; i <= 7; i+=2) // 01, 23, 45, 67 // Set i <= 3 to 7
  {
    int distance = 0;
    
    int current_trig = sens_array[i];
    int current_echo = sens_array[i + 1];
    
    distance = USS_Read(current_trig, current_echo);

    if (distance > distance_to_table)
    {
      current_activated_sensor_trig = i;
      edge_detected = true;
      break;
    }
    else
      current_activated_sensor_trig = 50; // Arbitrary number for the edge check
  }

  return edge_detected;
}

bool USS_Looper()
{
  // int sens_array[] = {us1t,us1e,us2t,us2e,us3t,us3e,us4t,us4e};
  edge_detected = false;
  
  for(int i = 0; i <= 7; i+=2) // 01, 23, 45, 67 // Set i <= 3 to 7
  {
    int distance = 0;
    
    int current_trig = sens_array[i];
    int current_echo = sens_array[i + 1];
    
    distance = USS_Read(current_trig, current_echo);

    if (distance > distance_to_table)
    {
      current_activated_sensor_trig = i;
      edge_detected = true;
      break;
    }
    else
      current_activated_sensor_trig = 50; // Arbitrary number for the edge check
  }

  return edge_detected;
}

/*
bool USS_Single(int trigPin, int echoPin)
{

  int distance = 100;
  
    do
    {
      
    distance = USS_Read(trigPin, echoPin);
    
    }while(distance > 20);
}
*/
