float Full_MM_S = 255; //the MM/S when the wheel is at full-speed

//enums
int S_POSITIONS = 0;
int RAD = 1;
int DEG = 2;
int MM = 3;
int E_POSITIONS = 4;

int S_SPEEDS = 5;
int RAD_S = 6;
int DEG_S = 7;
int MM_S = 8;
int PWM = 9;
int E_SPEEDS = 10;

float speed2MM_S(float s, int sm, float wr){
  if(sm == PWM){
    return (s/255) * Full_MM_S;
  }
  if(sm == RAD_S){
    return s*wr;
  }
  if(sm == DEG_S){
    return radians(s)*wr;
  }
  return s;
}

float speed2MM_S(float s, int sm){
  if(sm == PWM){
    return (s/255) * Full_MM_S;
  }
  return s;
}

float clamp(float i, float min, float max){
  return max(min, min(max, i));
}

float[] TankDrive(float xIn, float yIn){
  float ret[] = {0,0};
  
  float r = sqrt(pow(xIn,2)+pow(yIn,2));
  float a = atan2(xIn,yIn);
  
  a+=PI/4;
  
  ret[0] = clamp(r * cos(a) * sqrt(2),-1,1);
  ret[1] = clamp(r * sin(a) * sqrt(2),-1,1);
  
  return ret;
}

void calcTravel(float fr){  
  float dT = 1/fr; //delta time based off the framerate
  
  float[] speed = TankDrive(joyX, joyY);
  float dL = speed[0] * Full_MM_S * dT;
  float dR = speed[1] * Full_MM_S * dT;
  
  NOMAD_A += (dR - dL) / COA_D;
  
  NOMAD_X += (dL + dR) * 0.5 * cos(NOMAD_A) ;
  NOMAD_Y += (dL + dR) * 0.5 * sin(NOMAD_A);
}
