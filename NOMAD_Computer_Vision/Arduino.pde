float pinstates[] = new float[20]; //UNO: 14D + 6A = 20 pins total
int pinmodes[] = new int[20];

//enums
int A0 = 14;
int A1 = 15;
int A2 = 16;
int A3 = 17;
int A4 = 18;
int A5 = 19;

int INPUT = 0;
int OUTPUT = 1;
int INPUT_PULLUP = 0;
int INPUT_PULLDOWN = 0;

boolean LOW = false;
boolean HIGH = true;

//states
boolean useJoystick = true;
float autoX = 0;
float autoY = 0;

int analogRead(int pin){
  if(pinmodes[pin]==INPUT && pin>=A0){
    return round(pinstates[pin] * 1023);
  }else{
    return 0;
  }
}

boolean digitalRead(int pin){
  if(pinmodes[pin]==INPUT){
    return pinstates[pin] > 0.5;
  }else{
    return false;
  }
}

void digitalWrite(int pin, boolean state){
  if(pinmodes[pin]==OUTPUT){
    pinstates[pin] = state ? 1 : 0;
  }
}

void analogWrite(int pin, int state){
  if(pinmodes[pin]==OUTPUT){
    pinstates[pin] = clamp(state,0,255)/255;
  }
}

void pinMode(int pin, int state){
  pinmodes[pin] = state;
}

void PIN(int pin, float value){
  if(pinmodes[pin]==INPUT){
    pinstates[pin] = value;
  }
}

float PIN(int pin){
  if(pinmodes[pin]==OUTPUT){
    return pinstates[pin];
  }else{
    return 0;
  }
}

void drawArduino(int xPos, int yPos, float s){  
  float p = s*0.03;
  float x = xPos == LEFT ? s*1.1 : width - s*1.1;
  float y = yPos == TOP ? s*0.6 : height - s*0.6;
  
  fill(40);
  stroke(255); 
  rect(x-s, y-s/2, s*2, s, s*0.1);
  line(x-s, (y-s*0.5)+p*6, x+s, (y-s*0.5)+p*6);
  
  //tabs
  noStroke();
  textAlign(CENTER,CENTER);
  textSize(p*3);
  
  //Serial Monitor
  fill(100);
  rect(p*1+x-s, p*1+y-s/2, p*21, p*4, s*0.2);
  fill(0);
  text("Serial Monitor",p*11.5+x-s, p*2.5+y-s/2);
  
  //Run & Pause Code
  fill(100);
  rect(p*23+x-s, p*1+y-s/2, p*4, p*4, s*0.2);
  fill(0);
  textSize(p*2);
  text("▶",p*25.1+x-s, p*2.6+y-s/2);
  
  //Restart Code
  fill(100);
  rect(p*28+x-s, p*1+y-s/2, p*4, p*4, s*0.2);
  fill(0);
  textSize(p*2);
  text("■",p*30.1+x-s, p*2.6+y-s/2);
}

void setAuto(boolean auto){
  useJoystick = !auto;
}

void drive(float x,float y){
  if(!useJoystick){
    autoX = x;
    autoY = y;
  }
}

void driveX(float x){
  if(!useJoystick){
    autoX = x;
  }
}

void driveY(float y){
  if(!useJoystick){
    autoY = y;
  }
}
