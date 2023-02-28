#include "my_library.h"

Servo Servo_L;
Servo Servo_R;
int start_angle = 0;

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



