/** 
 * Drives to a black strip, detects the color above and carries out an action
 */

#include "MeMCore.h"
#include "Wire.h"
#define RED colorarr[0]
#define GREEN colorarr[1]
#define BLUE colorarr[2]
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

MeLineFollower lineFinder(PORT_2); 

MeUltrasonicSensor ultraSensor(PORT_3);

MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);

MeBuzzer buzzer;
MeDCMotor motor_right(M1);
MeDCMotor motor_left(M2);
uint8_t motorSpeed = 150;

double r;
double g;
double b;

float blackcalibarr[]={376,280,309};
float grayarr[]={229,173,184};
float colorarr[]={0,0,0};

int melody[] = {
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
 };
int noteDurations[] = {
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  };
  
void setup() {
  Serial.begin(9600);
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
  delay(370);
}

void turn_right() {
  motor_right.run(-motorSpeed); 
  motor_left.run(-motorSpeed);
  delay(370);
}

void black(){
  for (int thisNote = 0; thisNote < 112; thisNote++) {
    int noteDuration = 375 / noteDurations[thisNote];
    buzzer.tone(melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.00;
    delay(pauseBetweenNotes);
    
    buzzer.noTone();
  }
}

void red(){
  turn_left();
}

void green() {
  turn_right();
}

void blue() {
  turn_right();
  float dist = ultraSensor.distanceCm();
  while(dist > 9) {
    Serial.println(dist);
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed);
    dist = ultraSensor.distanceCm();
  }
  motor_right.stop();
  motor_left.stop();
  delay(300);
  turn_right();
  
}

void yellow(){
  turn_left();
  turn_left();
}

void purple(){
  turn_left();
  float dist = ultraSensor.distanceCm();
  while(dist > 9) {
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed);
    dist = ultraSensor.distanceCm();
  }
  motor_right.stop();
  motor_left.stop();
  delay(300);
  turn_left();
}

void colour_check(){
  int count = 0;
  while (count < 3) { // checks a max of 3 times. If fail detect all 3 times, the robot will just continue going forward and crash
  rgbled.setColor(255,0,0);
  rgbled.show();
  delay(100);
  r = lightsensor.read();

  rgbled.setColor(0,255,0);
  rgbled.show();
  delay(100);
  g = lightsensor.read();

  rgbled.setColor(0,0,255);
  rgbled.show();
  delay(100);
  b = lightsensor.read(); 
  colorarr[0]= 255 * (r-blackcalibarr[0])/grayarr[0];
  colorarr[1]= 255 * (g-blackcalibarr[1])/grayarr[1];
  colorarr[2]= 255 * (b-blackcalibarr[2])/grayarr[2];

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
  else if(abs(RED-GREEN) < 20 && BLUE > RED) {
    purple(); 
    count = 3;
  }
  else if(abs(GREEN-BLUE) < 20 && RED < GREEN) {
    blue();
    count = 3;
  }
  else if(abs(RED-BLUE) < 20 && GREEN > BLUE) {
    green();
    count = 3;
  }
  else {
    count += 1;
  }
  }
}
