#include "MeMCore.h"
#include "Wire.h"
#define RED colorarr[0]
#define GREEN colorarr[1]
#define BLUE colorarr[2]

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

double red;
double green;
double blue;

float blackcalibarr[]={376,280,309};
float grayarr[]={229,173,184};
float colorarr[]={0,0,0};

void setup(){
  Serial.begin(9600);
  Serial.println("PLACE COLORED PAPER TO DETECT");
  delay(4000);
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
    Serial.println("Black");
  }
  else if (abs(GREEN-BLUE) < 20 && RED > GREEN) {
    Serial.println("Red");
  }
  else if (RED > 200 & RED > GREEN && GREEN > BLUE) {
    Serial.println("Yellow");
  }
  else if(abs(RED-GREEN) < 20 && BLUE < RED) {
    Serial.println("Purple");
  }
  else if(abs(GREEN-BLUE) < 20 && RED < GREEN) {
    Serial.println("Blue");
  }
  else if(abs(RED-BLUE) < 20 && GREEN > BLUE) {
    Serial.println("Green");
  }
  else {
   Serial.println("IDK");
  }
  }
  
  void loop(){
  }
