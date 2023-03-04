float createSensor(float x, float y, float r){
  //sense data
  color c = get(round(width/2+x*SF), round(height/2+y*SF));
  
  //transform
  translate(x*SF,y*SF);
  rotate(r);
  
  //draw sensor
  stroke(wireframeY);
  //noFill();
  fill(c);
  rect(-20*SF,-8*SF,40*SF,16*SF);
  
  //undo transform
  rotate(-r);
  translate(-x*SF,-y*SF);
  
  //return brightness (mimmics distance)
  return (red(c) + green(c) + blue(c)) / 765;
}
