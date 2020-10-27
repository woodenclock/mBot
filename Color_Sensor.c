#include "MeMCore.h"
#include "Wire.h"

MeColorSensor colorsensor(PORT_4);

//initialise the color values to 0.
uint16_t redvalue=0, greenvalue=0, bluevalue=0;

void setup() {
  //CALIBRATION STEPS
  Serial.begin(9600);
  colorsensor.SensorInit();
  systime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
while(1)
{
    redvalue   = colorsensor.ReturnRedData();
    greenvalue = colorsensor.ReturnGreenData();
    bluevalue  = colorsensor.ReturnBlueData();
   }
}
