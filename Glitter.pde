class Glitter { 
  float x = random(width);
  float y = random(-500,100);
float a = map(pitchFromArduino,0,360,4,10);
 float yspeed = random(a);
 
  void fall() {
    y = y+yspeed;
    x = x+yspeed;
    
    if (y > height) {
      y = random(-500,-100);
    }
    if (x > width) {
      x = random(-200,-100);
    }
  } 
  
  void show() {
     fill(255,pitchFromArduino,rollFromArduino);
    noStroke();
   float p = map(rollFromArduino,0,360,5,15);
   float s = random(p);
    circle(x,y,s);
  }
  
}
