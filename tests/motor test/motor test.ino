/*
Test sketch for the Motor Shield (Adafruit assembled Motor Shield for Arduino v2)
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select motors using relevant ports M1, M2, M3 or M4.
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

int i = 0;

void lookForMotorShield() {
  Serial.println("Looking for Motor Shield");

  if (!AFMS.begin()) { // create with the default frequency 1.6KHz
    Serial.println("Warning: Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found. Starting test.");
}
void setMotorSpeeds(int speed) {
  leftMotor->setSpeed(speed);
  rightMotor->setSpeed(speed);
}
void releaseMotors() {
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}
void driveForward() {
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}
void driveBackward() {
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void turnLeft() {
  leftMotor->run(RELEASE);
  rightMotor->run(FORWARD);
  
}
void turnRight() {
  leftMotor->run(FORWARD);
  rightMotor->run(RELEASE);
}

void turnLeftReversing() {
  leftMotor->run(BACKWARD);
  rightMotor->run(RELEASE);
}

void turnRightReversing() {
  leftMotor->run(RELEASE);
  rightMotor->run(BACKWARD);
}

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  lookForMotorShield();

  // Set the speed to start, from 0 (off) to 255 (max speed)
  setMotorSpeeds(255);
  releaseMotors();
}

void loop() {
  if(i == 0){
    driveForward();
    delay(400);
    releaseMotors();
    delay(300);

    turnLeftReversing();
    delay(2900);
    releaseMotors();
    delay(300);
    
    driveForward();
    delay(200);
    releaseMotors();
    delay(300);

    releaseMotors();
    delay(2000);

    driveBackward();
    delay(400);
    releaseMotors();
    delay(300);

    turnRight();
    delay(2900);
    releaseMotors();
    delay(300);

    driveForward();
    delay(2000);
    releaseMotors();
    delay(300);

    releaseMotors();
  }
  i = 1;
}