float sc = 0.1;

void drawMinimap(int xPos, int yPos, float s){  
  float x = xPos == LEFT ? s*0.6 : width - s*0.6;
  float y = yPos == TOP ? s*0.6 : height - s*0.6;
  
  fill(40);
  stroke(255);
  
  rect(x-s/2, y-s/2, s, s, s*0.1);
  noFill();
  
  stroke(255,0,0);
  line(x-clamp(NOMAD_X*sc, -s/2,s/2), y-clamp(NOMAD_Y*sc,-s/2,s/2),x-clamp(NOMAD_X*sc, -s/2,s/2)+(cos(NOMAD_A+PI)*40), y-clamp(NOMAD_Y*sc,-s/2,s/2)+(sin(NOMAD_A+PI)*40));
  
  stroke(0,255,0);
  ellipse(x-clamp(NOMAD_X*sc, -s/2,s/2)+(cos(NOMAD_A+PI)*COA_Y*sc), y-clamp(NOMAD_Y*sc,-s/2,s/2)+(sin(NOMAD_A+PI)*COA_Y*sc),sc*height*zoom/SF,sc*height*zoom/SF);
  
  stroke(255,0,255);
  rect(clamp(trestle[0]*sc, -s/2,s/2)+x,clamp(trestle[1]*sc, -s/2,s/2)+x,trestle[2]*sc,trestle[3]*sc);
}
