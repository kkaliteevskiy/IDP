#include "my_library.h"

Servo Servo_L;
Servo Servo_R;
int start_angle = 0;
int close_angle = 60;//corresponds to 90 degrees irl

void set_servos(){
  Servo_L.attach(SERVO_LEFT);
  Servo_R.attach(SERVO_RIGHT);
  Servo_L.write(start_angle);
  Servo_R.write(179 - start_angle);
}

void writeServos(int angle){
  Servo_L.write(angle);
  Servo_R.write(179 - angle);
}

void captureBlock(){
  Servo_L.write(close_angle);
  Servo_R.write(179 - close_angle);
}

void captureBlock(){
  Servo_L.write(start_angle);
  Servo_R.write(179 - start_angle);
}



