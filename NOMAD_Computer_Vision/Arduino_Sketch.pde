//this code can be changed - it's a slightly different version of the Arduino sketch which you can use to program the robot.
//This is for testing sensor/motor auto-movement code before using the algorithm on the real thing
int USSthreshhold = 100;

void Setup(){
  pinMode(A0, INPUT); //USS Bottom Right
  pinMode(A1, INPUT); //USS Top Right
  pinMode(A2, INPUT); //USS Top Left
  pinMode(A3, INPUT); //USS Bottom Left
  
  pinMode(13, OUTPUT); //Left PWM
  pinMode(12, OUTPUT); //Left Direction
  
  pinMode(11, OUTPUT); //Right PWM
  pinMode(10, OUTPUT); //Right Direction
  
  setAuto(false);
}

void Loop(){
  if(analogRead(A1) < USSthreshhold){
    drive(-1,0);
  }else if(analogRead(A2) < USSthreshhold){
    drive(1,0);
  }else{
    drive(0,1);
  }
}
