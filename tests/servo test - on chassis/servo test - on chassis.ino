#include <Servo.h>

/* Test for Servos
On the Motor Shield, "Servo 1" input corresponds to pin D10 - right servo and "Servo 2" corresponds to pin D9 - left servo
*/

Servo myServo_right;
Servo myServo_left;
int start_angle = 0;
int close_angle = 60;
int angle_1, angle_2;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Test Starting: Servos should sweep back and forth across their max range (270 degrees)");
  Serial.println("Note that the servo readings and arguments only range from 0 to 179");
  myServo_right.attach(10); // attach servo to pin D10
  myServo_left.attach(9);
  myServo_right.write(start_angle);
  myServo_left.write(179 - start_angle);
}
void loop() {
  myServo_right.write(start_angle);
  myServo_left.write(179 - start_angle);  
  delay(2000);
  myServo_right.write(close_angle);
  myServo_left.write(179 - close_angle);  
  delay(2000);
  }