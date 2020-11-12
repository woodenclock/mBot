/** 
 *  An arduino code using c++ which allows the mBot to complete a given maze filled with waypoint challenges.
 *  The mBot moves until it detects the black strip and stops . After which it does the color challenge and
 *  based on that it performs the wanted movement.
 *  
 *  Team members :
 *  Alvin
 *  Kishor
 *  Sungmin
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

//Initialize ports for the different sensors/components
MeLineFollower lineFinder(PORT_2); 
MeUltrasonicSensor ultraSensor(PORT_3);
MeLightSensor lightsensor(PORT_6);
MeRGBLed rgbled(PORT_7);
MeBuzzer buzzer;

//Initialize motors
MeDCMotor motor_right(M1);
MeDCMotor motor_left(M2);

//Initialize the mBOts speed
uint8_t motorSpeed_R = 230;
uint8_t motorSpeed_L = 255;
//defining the color variables
double r;
double g;
double b;
float blackcalibarr[]={376,280,309}; //from calibration
float grayarr[]={229,173,184}; //from calibration (the scale)
float colorarr[]={0,0,0};//to store the detected intensity values

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
 //nothing here, everything is in the loop
}

void loop() {
  mbotactions();
}

//code responsible for preventing the mBot from running into the walls on its sides
void autocorrection() {
  int Right_IR = analogRead(A0);//Left sensor
  int Left_IR = analogRead(A1);//Right sensor
  if(Right_IR>250 && Left_IR>200)//In the event of no obstacle being detected by any of the sensors, move straight
  {   
      motor_right.run(+motorSpeed_R);
  motor_left.run(-motorSpeed_L);
  }
  else if(Right_IR<250)//If the right sensor is near an obstacle, shift left
  {    
      motor_right.run(+motorSpeed_R);
      motor_left.run(+motorSpeed_L-10);
      delay(1);
  }
  else if(Left_IR<200)//If the left sensor is near an obstacle, shift right
  {   
      motor_right.run(-motorSpeed_R);
      motor_left.run(-motorSpeed_L-10);
      delay(1);
  }
}

//function encapsulating the main tasks of the mbot
void mbotactions(){
  //check for black strip
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN://represents that both sides of the line sensor are in the black strip and the mBot stops.
    motor_right.stop();
    motor_left.stop();
    colour_check();
    break;
    case S1_OUT_S2_OUT://represents that boths sides are out of black strip.
    //include IR rectification
    autocorrection();
    break;
    default: //if only 1 is inside, it will continue what it was already doing before 1 sensor detected a strip(i.e. approaching a strip from the side)
    break;
  }
}

//To turn left
void turn_left() {//change delay to change left turn angle
  motor_right.run(+motorSpeed_R); 
  motor_left.run(+motorSpeed_L);
  delay(239);
}

//To turn right
void turn_right() {//change delay to chang right turn angle
  motor_right.run(-motorSpeed_R); 
  motor_left.run(-motorSpeed_L);
  delay(241);
}

//Play victory music
void black(){
  for (int thisNote = 0; thisNote < 112; thisNote++) {
    int noteDuration = 375 / noteDurations[thisNote]; // Calculation of note duration
    buzzer.tone(melody[thisNote], noteDuration); // Send signal to the buzzer to play tone
    int pauseBetweenNotes = noteDuration * 1.00; // Pause of beep inbetween tones
    delay(pauseBetweenNotes);
    buzzer.noTone(); // Tone stops
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
  float dist = ultraSensor.distanceCm(); // Measures the distance between the wall and the mBot itself
  while(dist > 9) { // Moves until the mBot is greater than 9cm away from the wall
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
  if (Right_IR < Left_IR-15) { // U turns from the left
  motor_right.run(+motorSpeed_R); 
  motor_left.run(+motorSpeed_L);
  delay(454);
  }
  else { // U turns from the right
  motor_right.run(-motorSpeed_R); 
  motor_left.run(-motorSpeed_L);
  delay(452);
  }
}

//Two successive left turns in two grids
void purple(){
  turn_left();
  float dist = ultraSensor.distanceCm(); // Measures the distance between the wall and the mBot itself
  while(dist > 9) { // Moves until the mBot is greater than 9cm away from the wall
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
  //turns on red led and measures reflected intensity
  rgbled.setColor(255,0,0);
  rgbled.show();
  delay(100);
  r = lightsensor.read();
  //turns on green led and measures reflected intensity
  rgbled.setColor(0,255,0);
  rgbled.show();
  delay(100);
  g = lightsensor.read();
  //turns on blue led and measures reflected intensity
  rgbled.setColor(0,0,255);
  rgbled.show();
  delay(100);
  b = lightsensor.read(); 
  // Values of R,G,B are calculated based on the range detected above
  RED = 255 * (r-blackcalibarr[0])/grayarr[0];
  GREEN = 255 * (g-blackcalibarr[1])/grayarr[1];
  BLUE = 255 * (b-blackcalibarr[2])/grayarr[2];

  rgbled.setColor(0,0,0);
  rgbled.show();
// Based on the light sensor reading if the outputs for the light intensity of each color(R,G,B)
// falls under any of the below ranges, specified color is detected and an action is performed
  if (RED < 20 && GREEN < 20 && BLUE < 20) {
    black();
  }
  else if (abs(GREEN-BLUE) < 20 && RED > GREEN) {
    red();
  }
  else if (RED > 130 & RED > GREEN && abs(GREEN-BLUE)>25) {
    yellow();
  }
  else if(abs(RED-GREEN) < 20 && BLUE > RED) {
    purple(); 
  }
  else if(abs(GREEN-BLUE) < 20 && RED < GREEN) {
    blue();
  }
  else if(abs(RED-BLUE) < 20 && GREEN > BLUE) {
    green();
  }
}
  
