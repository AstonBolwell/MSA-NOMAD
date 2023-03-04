//virtual joystick implementation using mouse
float joyX = 0;
float joyY = 0;

void drawVirtualJoystick(int xPos, int yPos, float s){
  joyY = map(mouseY, 0, height, 1, -1);
  joyX = map(mouseX, 0, width, -1, 1);
  
  float x = xPos == LEFT ? s*0.6 : width - s*0.6;
  float y = yPos == TOP ? s*0.6 : height - s*0.6;
  
  fill(40);
  stroke(255);
  
  rect(x-s/2, y-s/2, s, s, s*0.1);
  
  stroke(100);
  line(x-s*0.4, y, x+s*0.4, y);
  line(x, y-s*0.4, x, y+s*0.4);
  
  stroke(255);
  line(x-s*0.4, y - (joyY*s*0.4), x+s*0.4, y - (joyY*s*0.4));
  line(x + (joyX*s*0.4), y-s*0.4, x + (joyX*s*0.4), y+s*0.4);
}
