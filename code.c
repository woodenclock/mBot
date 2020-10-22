/*
 * mBot code for Group 3a2
 *
 * Members:
 * Sung Min
 * Kishor
 * Svetha
 * Alvin
 */

//define the required variables here
int motorspeed = ;

//turn right
void right_turn(){
  
}

//turn left
void left_turn(){
  
}

//detect black strip
void black_strip(){
  //stop
}

//ultrasound(distance in front)
float dist_front() {
  float dist = ;
  return dist;
}

//red (left turn)
void red_task(){
  left_turn();
}

//green (right turn)
void green_task(){
  right_turn()
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
  
}

