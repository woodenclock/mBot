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
  //move forward till it hits black strip
  //detect color on top
  //carry out appropriate action
}

void colour_check(){
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
   
  //condition for red
  //condition for blue
  //condition for purple
  //condition for yellow
  //condition for green
  //condition for black
  //ending else check again?
}
