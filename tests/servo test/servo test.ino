#include <Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Test Starting: Servo should sweep back and forth across its max range (270 degrees)");
  Serial.println("Note that the servo readings and arguments only range from 0 to 180");
  myServo.attach(10); // attach servo to pin D10
}

void loop() {
  myServo.write(0);
  delay(2000); // wait 2 seconds - needs to be at least long enough to allow servo to reach the position
  
  Serial.print("Rotated to 0 degrees. Servo reading: ");
  int angle = myServo.read();
  Serial.println(angle);
  
  myServo.write(180);
  delay(2000);
  
  Serial.print("Rotated to max angle. Servo reading: ");
  angle = myServo.read();
  Serial.println(angle);
  }
