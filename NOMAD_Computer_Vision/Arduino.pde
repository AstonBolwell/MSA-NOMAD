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

float analogRead(int pin){
  if(pinmodes[pin]==INPUT && pin>=A0){
    return pinstates[pin];
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
