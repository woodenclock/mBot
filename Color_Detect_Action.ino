/** 
 * Drives to a black strip, detects the color above and carries out an action
 */

#include "MeMCore.h"
#include "Wire.h"
#define RED colorarr[0]
#define GREEN colorarr[1]
#define BLUE colorarr[2]

MeLineFollower lineFinder(PORT_2); 

MeUltrasonicSensor ultraSensor(PORT_3);

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

MeDCMotor motor_right(M1);
MeDCMotor motor_left(M2);
uint8_t motorSpeed = 100;

double red;
double green;
double blue;


float blackcalibarr[]={376,280,309};
float grayarr[]={229,173,184};
float colorarr[]={0,0,0};

void setup() {
  
}

void loop() {
  mbotactions();
}

void mbotactions(){
  //check for black strip
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN:
    motor_right.stop();
    motor_left.stop();
    colour_check();
    break;
    case S1_IN_S2_OUT: 
    case S1_OUT_S2_IN: 
    case S1_OUT_S2_OUT:
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed); 
    break;
    default: 
    break;
  }
}

void turn_left() {//change delay to change left turn angle
  motor_right.run(+motorSpeed); 
  motor_left.run(+motorSpeed);
  delay(890);
}

void turn_right() {
  motor_right.run(-motorSpeed); 
  motor_left.run(-motorSpeed);
  delay(890);
}

void black(){
  //play music
}

void red(){
  turn_left();
}

void green() {
  turn_right();
}

void blue() {
  turn_right();
  int dist = ultraSensor.distanceCm();
  delay(100);
  while(dist > 4) {
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed);
    dist = ultraSensor.distanceCm();
    delay(100);
  }
  motor_right.stop();
  motor_left.stop();
  turn_right();
  
}

void yellow(){
  turn_left();
  turn_left();
}

void purple(){
  turn_left();
  int dist = ultraSensor.distanceCm();
  delay(100);
  while(dist > 4) {
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed);
    dist = ultraSensor.distanceCm();
    delay(100);
  }
  motor_right.stop();
  motor_left.stop();
  turn_left();
}

void colour_check(){
  int count = 0;
  while (count < 3) { // checks a max of 3 times. If fail detect all 3 times, the robot will just continue going forward and crash
  rgbled.setColor(255,0,0);
  rgbled.show();
  delay(1000);
  red = lightsensor.read();

  rgbled.setColor(0,255,0);
  rgbled.show();
  delay(1000);
  green = lightsensor.read();

  rgbled.setColor(0,0,255);
  rgbled.show();
  delay(1000);
  blue = lightsensor.read(); 
  colorarr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  colorarr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  colorarr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();
  
  if (RED < 20 && GREEN < 20 && BLUE < 20) {
    black();
    count = 3;
  }
  else if (abs(GREEN-BLUE) < 20 && RED > GREEN) {
    red();
    count = 3;
  }
  else if (RED > 200 & RED > GREEN && GREEN > BLUE) {
    yellow();
    count = 3;
  }
  else if(abs(RED-GREEN) < 20 && BLUE < RED) {
    purple(); 
    count = 3;
  }
  else if(abs(GREEN-BLUE) < 20 && RED < GREEN) {
    blue();
    count = 3;
  }
  else if(abs(RED-BLUE) < 20 && GREEN > BLUE) {
    green();
    count = 3
  }
  else {
    count += 1;
  }
  
}
