#include <Servo.h>

Servo myServo_1;
Servo myServo_2;
int angle_1, angle_2;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Test Starting: Servo should sweep back and forth across its max range (270 degrees)");
  Serial.println("Note that the servo readings and arguments only range from 0 to 179");
  myServo_1.attach(10); // attach servo to pin D10
  myServo_2.attach(9);
}

void loop() {
  myServo_1.write(0);
  myServo_2.write(0);
  delay(2000); // wait 2 seconds - needs to be at least long enough to allow servo to reach the position
  
  Serial.println("Rotated to 0 degrees.");
  angle_1 = myServo_1.read();
  angle_2 = myServo_2.read();
  Serial.print("Servo 1 reading : ");
  Serial.println(angle_1);
  Serial.print("Servo 2 reading : ");
  Serial.println(angle_2);
  
  myServo_1.write(179);
  myServo_2.write(179);//max argument is 179
  delay(2000);
  
  Serial.println("Rotated to 180 degrees.");
  angle_1 = myServo_1.read();
  angle_2 = myServo_2.read();
  Serial.print("Servo 1 reading : ");
  Serial.println(angle_1);
  Serial.print("Servo 2 reading : ");
  Serial.println(angle_2);
  }
