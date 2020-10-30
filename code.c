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

//define the required variables here
int motorspeed = 100;
MeDCMotor motor_right(M1);
MeDCMotor motor_left(M2);

//stop 
void stop()
{
   motor_right.stop();
   motor_left.stop();
} 

//move forward
void forward()
{
 motor_right.run(+motorSpeed); 
 motor_left.run(-motorSpeed);
 stop();
 //then readjust
}

//turn right
void right_turn()
{
 motor_right.run(+motorSpeed); 
 motor_left.run(+motorSpeed);
 stop();
 //then readjust
}

//turn left
void left_turn()
{
motor_right.run(-motorSpeed); 
motor_left.run(-motorSpeed); 
 stop();
 //then readjust
}

//detect black strip
bool black_strip()
{
  //Line follower code
  
}

//ultrasound(distance in front)
float dist_front() {
  float dist = ;
  return dist;
}

//colour challenge
void colour_challenge(){
  //detect color 
  if (colour //parameters here) {
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
