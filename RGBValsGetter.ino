/**
 * Code to use light sensor to detect color components RGB
 */

#include "MeMCore.h"
#include "Wire.h"

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

double red;
double green;
double blue;

float colourarr[]={0,0,0};

void setup(){
  Serial.begin(9600);
  color_detect_test();
}

void loop(){

}

void color_detect_test(){
  Serial.println("Put Paper");
  delay(5000);
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

  Serial.print("Red value is ");
  Serial.println(red);
  Serial.print("Green value is ");
  Serial.println(green);
  Serial.print("Blue value is ");
  Serial.println(blue);
}
