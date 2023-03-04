//NOMAD Computer Vision - v0.1 [BETA]
String AppVersion = "v0.1 [BETA]";

//Thickness of the wireframe lines
int WireframeWidth = 4;

//Zoom of the main model
float zoom = 0.5;

//setup variables
float NOMAD_X = 0;
float NOMAD_Y = 0;
float NOMAD_A = 0;

//config variables
float COA_Y = 80; //centre of axle y-offset from centre of body
float COA_D = 150; //drive axis distance between wheels

//simulated trestle table configuration for AI training
float trestle[] = {-900,-450,1800,900}; //x,y,w,h - same as rectangle config

void setup(){
  fullScreen();
  Setup();
}

void draw(){
  background(bg);
  strokeWeight(WireframeWidth);
  
  calcTravel(frameRate);
  
  //transform
  translate(width/2, height/2 + COA_Y*SF);
  rotate((PI/2)-NOMAD_A);
  translate(NOMAD_X*SF, NOMAD_Y*SF);
  
  //Draw Enviromental objects
  noStroke();
  fill(trestleColor);
  rect(trestle[0]*SF,trestle[1]*SF, trestle[2]*SF,trestle[3]*SF);
  
  //world border
  stroke(30);
  noFill();
  rect(SF*0.5*-height*0.3/sc,SF*0.5*-height*0.3/sc,SF*height*0.3/sc,SF*height*0.3/sc, SF*height*0.03/sc);
  
  //reverse transformation
  translate(-NOMAD_X*SF, -NOMAD_Y*SF);
  rotate((-PI/2)+NOMAD_A);
  translate(-width/2, -height/2 - COA_Y*SF);
  
  //draw model. variable 'rs' is in mm
  drawModel(width/2, height/2, height*zoom, 400, PI*0);
  
  //joystick
  drawVirtualJoystick(LEFT, BOTTOM, height*0.2);
  
  //minimap
  drawMinimap(LEFT,TOP,height*0.3);
  
  //Arduino GUI
  drawArduino(RIGHT, TOP, height*0.2);
  
  Loop();
}
