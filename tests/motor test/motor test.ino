/*
Test sketch for the Motor Shield (Adafruit assembled Motor Shield for Arduino v2)
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4.
Adafruit_DCMotor *myMotor = AFMS.getMotor(3);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Looking for Motor Shield");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found. Starting test.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
}

void loop() {

  Serial.println("Motor should spin forward for 5 seconds...");
  myMotor->run(FORWARD);
  myMotor->setSpeed(150);
  delay(5000);

  Serial.println("Motor should now spin in the opposite direction for 5 seconds...");
  myMotor->run(BACKWARD);
  delay(5000);

  Serial.println("Releasing motor for 2 seconds...");
  myMotor->run(RELEASE);
  delay(2000);
}