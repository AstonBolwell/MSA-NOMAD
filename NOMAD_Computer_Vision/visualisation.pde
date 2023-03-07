color bg = color(0);
color trestleColor = color(30);
color wireframeR = color(255,50,0);
color wireframeG = color(0,255,0);
color wireframeB = color(0,100,255);

color wireframeY = color(255,255,0);

float SF; //scale factor to use when converting from Real Dimentions to Pixels (and vice-versa)

int preRes = 10;   //prediction resolution
float preDis = 200; //prediction distance (mm) 

float preva;

void drawWheel(float x, float y, float r, float w){ //real measurements (mm)
  rect((x-w/2)*SF, (y-r)*SF, w*SF, 2*r*SF, WireframeWidth);
}

void drawRotWheel(float x, float y, float r){
  stroke(wireframeB);
  ellipse(x*SF,y*SF,r*2*SF,r*2*SF);
}

void drawPowWheel(float x, float y, float r, float w, float speed, int sm){
  stroke(wireframeB);
  drawWheel(x,y,r,w);
  stroke(wireframeR);
  
  //visualise speed
  line(x*SF,y*SF,x*SF,(y-speed2MM_S(speed, sm))*SF);
}

void drawCOA(float x, float y){
  stroke(wireframeG);
  point(x*SF, y*SF);
}

void drawModel(int x, int y, float s, float rs, float a){
  
  SF = s/rs;
  
  //Model of "MSA's NOMAD" - model version: 1.0
  
  //Outline
  noFill();
  stroke(wireframeG);
  ellipse(x,y,s,s);
  
  //apply transformations for rotation
  translate(x, y);
  rotate(a);
  
  //Wheels
  noFill();
  drawPowWheel(COA_D/2, COA_Y, 40, 25, TankDrive(joyX, joyY)[0] * 255, PWM);
  drawPowWheel(-COA_D/2, COA_Y, 40, 25, TankDrive(joyX, joyY)[1] * 255, PWM);
  
  //caster wheel
  stroke(wireframeB);
  drawRotWheel(0, -COA_Y, 30);
  
  //draw centre of axle
  drawCOA(0,COA_Y);
  
  //draw sensors
  PIN(A0,createSensor(120,120,-PI/4));
  PIN(A2,createSensor(-120,-120,-PI/4));
  PIN(A1,createSensor(120,-120,PI/4));
  PIN(A3,createSensor(-120,120,PI/4));
  
  //reset transformations
  rotate(-a);
  translate(-x, -y);  
}
