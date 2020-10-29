/**
 * Code to use light sensor to detect color components RGB of 5 colors, green blue purple yellow red
 * 
 * DETECTED COLORS
 * GREEN : 
 * BLUE : 
 * PURPLE :
 * YELLOW :
 * RED : 
 * BLACK : 
 */

#include "MeMCore.h"
#include "Wire.h"

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

double red;
double green;
double blue;


float blackcalibarr[]={376,280,309};
float grayarr[]={229,173,184};
float greenarr[]={0,0,0};
float bluearr[]={0,0,0};
float yellowarr[]={0,0,0};
float purplearr[]={0,0,0};
float blackarr[]={0,0,0};


void setup(){
  Serial.begin(9600);
  color_detect_test();
}

void loop(){

}

void color_detect_test(){
  Serial.println("Put green Paper");
  delay(500);
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
  greenarr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  greenarr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  greenarr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();

  Serial.println("Put blue Paper");
  delay(500);
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
  bluearr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  bluearr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  bluearr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();

  Serial.println("Put purple Paper");
  delay(500);
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
  purplearr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  purplearr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  purplearr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();

  Serial.println("Put yellow Paper");
  delay(500);
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
  yellowarr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  yellowarr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  yellowarr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();

  Serial.println("Put black Paper");
  delay(500);
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
  blackarr[0]= 255 * (red-blackcalibarr[0])/grayarr[0];
  blackarr[1]= 255 * (green-blackcalibarr[1])/grayarr[1];
  blackarr[2]= 255 * (blue-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();

  Serial.println("GREEN OBTAINED RGB VALUES:");
  Serial.print("RED: ");
  Serial.println(greenarr[0]);
  Serial.print("GREEN: ");
  Serial.println(greenarr[1]);
  Serial.print("BLUE: ");
  Serial.println(greenarr[2]);
  
  Serial.println("BLUE OBTAINED RGB VALUES:");
  Serial.print("RED: ");
  Serial.println(bluearr[0]);
  Serial.print("GREEN: ");
  Serial.println(bluearr[1]);
  Serial.print("BLUE: ");
  Serial.println(bluearr[2]);

  Serial.println("PURPLE OBTAINED RGB VALUES:");
  Serial.print("RED: ");
  Serial.println(purplearr[0]);
  Serial.print("GREEN: ");
  Serial.println(purplearr[1]);
  Serial.print("BLUE: ");
  Serial.println(purplearr[2]);

  Serial.println("YELLOW OBTAINED RGB VALUES:");
  Serial.print("RED: ");
  Serial.println(yellowarr[0]);
  Serial.print("GREEN: ");
  Serial.println(yellowarr[1]);
  Serial.print("BLUE: ");
  Serial.println(yellowarr[2]);

  Serial.println("BLACK OBTAINED RGB VALUES:");
  Serial.print("RED: ");
  Serial.println(blackarr[0]);
  Serial.print("GREEN: ");
  Serial.println(blackarr[1]);
  Serial.print("BLUE: ");
  Serial.println(blackarr[2]);
}
