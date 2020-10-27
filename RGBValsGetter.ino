/**
 * Code to use light sensor to detect color components RGB
 */

#include "MeMCore.h"
#include "Wire.h"

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

double RED;
double GREEN;
double BLUE;

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
  RED = lightsensor.read();

  rgbled.setColor(0,255,0);
  rgbled.show();
  delay(1000);
  GREEN = lightsensor.read();

  rgbled.setColor(0,0,255);
  rgbled.show();
  delay(1000);
  BLUE = lightsensor.read();

  Serial.println("Red value is" + RED);
  Serial.println("Green value is" + GREEN);
  Serial.println("Blue value is" + BLUE);
}
