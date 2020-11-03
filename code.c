/*
 * mBot code for Group 3a2
 *
 * Members:
 * Sungmin
 * Kishor
 * Svetha
 * Alvin
 */
#include "MeMCore.h"

MeLineFollower lineFinder(PORT_2); //TO STOP AT THE BLACK STRIP 
MeUltrasonicSensor ultraSensor(PORT_3); //MEASURE DISTANCE BETWEEN WALL AND MBOT 
MeLightSensor lightsensor(PORT_6); //FOR COLOR DETECTION ON TOP
MeRGBLed rgbled(PORT_7); //FOR COLOR DETECTION ON TOP
MeDCMotor motor_right(M1); //RIGHT WHEEL
MeDCMotor motor_left(M2); //LEFT WHEEL

int motorspeed = 100;

//Stop 
void stop()
{
   motor_right.stop();
   motor_left.stop();
} 

//Move Forward
void forward()
{
 motor_right.run(+motorSpeed); 
 motor_left.run(-motorSpeed);
}

//Turn Right
void right_turn()
{
 motor_right.run(+motorSpeed); 
 motor_left.run(+motorSpeed);
 stop();
 //then readjust
}

//Turn Left
void left_turn()
{
motor_right.run(-motorSpeed); 
motor_left.run(-motorSpeed); 

 //then readjust
}

//Detect Black Strip
bool black_strip()
{
   switch(sensorState)
  {
    case S1_IN_S2_IN:
    colour_challenge();
    break;
    case S1_IN_S2_OUT: 
    case S1_OUT_S2_IN: 
    case S1_OUT_S2_OUT:
    motor_right.run(+motorSpeed); 
    motor_left.run(-motorSpeed); 
    break;
    default: 
    break;
  }//Line follower code
}

//Ultrasound (distance from wall)
float dist_front() {
  float dist = ultraSensor.distanceCm();
  return dist;
}

//colour challenge
void colour_challenge(){
  //detect color 
  if (//parameters here) {
      red_task();
      }
      else if (//parameters){
        green_task();
        }
        else if (//parameters) {
          yellow_task();
          }
          else if(//parameters) {
            purple_task();
           }
           else if(//parameters) {
             lightblue_task();
            }
             else if(//parameters) {
               black_task();
}
            
//red (left turn)
void red_task(){
  left_turn();
}

//green (right turn)
void green_task(){
  right_turn();
}

//yellow (U-turn within same grid)
void yellow_task(){
  right_turn();
  right_turn();
}

//purple (2x left in 2 grid)
void purple_task(){
  left_turn();
  while(dist_front() > 4) {
    //go straight
  }    
  //stop
  left_turn();
  }
}

//light blue (2x right in 2 grid)
void lightblue_task(){
  right_turn();
  while(dist_front() > 4) {
    //go straight
  }    
  //stop
 right_turn();
  }
}

//black (make noise)
void black_task(){
  stop();
  music();
  exit(0);
}

void setup(){
  
}

void loop() {
  forward();
  if(black_strip()){
    color_challenge();
  }
}
