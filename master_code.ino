/** 
 *  An arduino code using c++ which allows the mBot to complete a given maze filled with waypoint challenges.
 *  The mBot moves until it detects the black strip and stops . After which it does the color challenge and
 *  based on that it performs the wanted movement.
 *  
 *  Team members :
 *  Alvin
 *  Kishor
 *  Sung Min
 *  Svetha
 */
// Libraries 
#include "MeMCore.h"
#include "Wire.h"

//Macros(sound and color definition)
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

//Initialize ports for the different sensors
MeLineFollower lineFinder(PORT_2); 
MeUltrasonicSensor ultraSensor(PORT_3);
MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);
MeBuzzer buzzer;

//Initialize motors
MeDCMotor motor_right(M1);
MeDCMotor motor_left(M2);

//Initialize the mBOts speed
uint8_t motorSpeed = 200;

//color var def
double r;
double g;
double b;
float blackcalibarr[]={376,280,309}; //from calibration
float grayarr[]={229,173,184}; //from calibration
float colorarr[]={0,0,0};

//definition for music
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
 
//Duration of each notes
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
 
}

void loop() {
  mbotactions();
}

void autocorrection() {
  int Right_IR = analogRead(A0);//Left sensor
int Left_IR = analogRead(A1);//Right sensor
  if(Right_IR>300 && Left_IR>200)//In the event of no obstacle being detected by any of the sensors
  {   
      motor_right.run(+motorSpeed);
  motor_left.run(-motorSpeed);
  }
  else if(Right_IR<300)//If the right sensor is near an obstacle
  {    
  motor_right.run(+motorSpeed);
  motor_left.run(+motorSpeed);
      delay(5);
  }
  else if(Left_IR<200)//If the left sensor is near an obstacle
  {   
       motor_right.run(-motorSpeed);
  motor_left.run(-motorSpeed);
      delay(5);
  }
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
    case S1_OUT_S2_OUT:
    //include IR rectification
    autocorrection();
    break;
    default: 
    break;
  }
}

//To turn left
void turn_left() {//change delay to change left turn angle
  motor_right.run(+motorSpeed); 
  motor_left.run(+motorSpeed);
  delay(320);
}

//To turn right
void turn_right() {
  motor_right.run(-motorSpeed); 
  motor_left.run(-motorSpeed);
  delay(320);
}

//Play victory music
void black(){
  for (int thisNote = 0; thisNote < 112; thisNote++) {
    int noteDuration = 375 / noteDurations[thisNote];
    buzzer.tone(melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.00;
    delay(pauseBetweenNotes);
    buzzer.noTone();
  }
}

//Turn left
void red(){
  turn_left();
}

//Turn right
void green() {
  turn_right();
}

//Two successive right turns in two grids
void blue() {
  turn_right();
  float dist = ultraSensor.distanceCm();
  while(dist > 9) {
    autocorrection();
    dist = ultraSensor.distanceCm();
  }
  motor_right.stop();
  motor_left.stop();
  delay(300);
  turn_right();
  
}

//U-Turn
void yellow(){
  int Right_IR = analogRead(A0);//Left sensor
  int Left_IR = analogRead(A1);//Right sensor
  if (Right_IR < Left_IR - 100) {
  turn_left();
  turn_left();}
  else {
    turn_right();
    turn_right();
  }
}

//Two successive left turns in two grids
void purple(){
  turn_left();
  float dist = ultraSensor.distanceCm();
  while(dist > 9) {
    autocorrection();
    dist = ultraSensor.distanceCm();
  }
  motor_right.stop();
  motor_left.stop();
  delay(300);
  turn_left();
}

//Color Challenge
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
  RED = 255 * (r-blackcalibarr[0])/grayarr[0];
  GREEN = 255 * (g-blackcalibarr[1])/grayarr[1];
  BLUE = 255 * (b-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();


  if (RED < 20 && GREEN < 20 && BLUE < 20) {
    black();
    break;
  }
  else if (abs(GREEN-BLUE) < 20 && RED > GREEN) {
    red();
    break;
  }
  else if (RED > 130 & RED > GREEN && abs(GREEN-BLUE)>25) {
    yellow();
    break;
  }
  else if(abs(RED-GREEN) < 20 && BLUE > RED) {
    purple(); 
    break;
  }
  else if(abs(GREEN-BLUE) < 20 && RED < GREEN) {
    blue();
    break;
  }
  else if(abs(RED-BLUE) < 20 && GREEN > BLUE) {
    green();
    break;
  }
  else {
    count += 1;
  }
  }
}
