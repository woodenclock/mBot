/** 
 * Drives to a black strip, detects the color above and carries out an action
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
float colorarr[]={0,0,0};

