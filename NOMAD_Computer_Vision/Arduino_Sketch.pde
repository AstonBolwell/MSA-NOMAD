//this code can be changed - it's a slightly different version of the Arduino sketch which you can use to program the robot.
//This is for testing sensor/motor auto-movement code before using the algorithm on the real thing
void Setup(){
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(13, OUTPUT); //Left PWM
  pinMode(12, OUTPUT); //Left Direction
  
  pinMode(11, OUTPUT); //Right PWM
  pinMode(10, OUTPUT); //Right Direction
}

void Loop(){
  
}
