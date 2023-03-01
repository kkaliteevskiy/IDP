#include <Servo.h>

/* Test for Servos
On the Motor Shield, "Servo 1" input corresponds to pin D10 - right servo and "Servo 2" corresponds to pin D9 - left servo
*/

Servo myServo_right;
Servo myServo_left;
int angle_1, angle_2;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Test Starting: Servos should sweep back and forth across their max range (270 degrees)");
  Serial.println("Note that the servo readings and arguments only range from 0 to 179");
  myServo_right.attach(10); // attach servo to pin D10
  myServo_left.attach(9);
}
void loop() {
  myServo_right.write(0);
  myServo_left.write(179);
  delay(2000); // wait 2 seconds - needs to be at least long enough to allow servo to reach the position
  
  Serial.println("Rotated to first angle.");
  angle_1 = myServo_right.read();
  angle_2 = myServo_left.read();
  Serial.print("Servo 1 (RIGHT) reading : ");
  Serial.println(angle_1);
  Serial.print("Servo 2 (LEFT) reading : ");
  Serial.println(angle_2);
  
  myServo_right.write(179);
  myServo_left.write(0);//max argument is 179
  delay(2000);
  
  Serial.println("Rotated to second angle.");
  angle_1 = myServo_right.read();
  angle_2 = myServo_left.read();
  Serial.print("Servo 1 (RIGHT) reading : ");
  Serial.println(angle_1);
  Serial.print("Servo 2 (LEFT) reading : ");
  Serial.println(angle_2);
  }