/*
Program for motor functions and line following capability
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// initialise IR sensor pin locations for line following
int lineFollowerLeft = 1;
int lineFollowerRight = 2;
int turnDetectorLeft = 3;
int turnDetectorRight = 4;
// other constants
int runSpeed = 150;
int lineFollowerValues[4];
int leftTurnValue = 0;
int leftLineValue = 0;
int rightLineValue = 0;
int rightTurnValue = 0;


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select motors using relevant ports M1, M2, M3 or M4.
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

void lookForMotorShield() {
  if (!AFMS.begin()) {
    Serial.println("Warning: Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
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
void turnLeft() {
  leftMotor->run(RELEASE);
  rightMotor->run(FORWARD);
}
void turnRight() {
  leftMotor->run(FORWARD);
  rightMotor->run(RELEASE);
}
void getLineFollowerValues() {
  leftLineValue = digitalRead(lineFollowerLeft);
  rightLineValue = digitalRead(lineFollowerRight);
  leftTurnValue = digitalRead(turnDetectorLeft);
  rightTurnValue = digitalRead(turnDetectorRight);
}
void setLineFollowerValueArray () {
  lineFollowerValues[0] = leftTurnValue;
  lineFollowerValues[1] = leftLineValue;
  lineFollowerValues[2] = rightLineValue;
  lineFollowerValues[3] = rightTurnValue;
}


void setup() {
  Serial.begin(9600); // set up Serial library

  lookForMotorShield();

  setMotorSpeeds(runSpeed);
  releaseMotors();
  
  // set line follower inputs
  pinMode(lineFollowerLeft, INPUT);
  pinMode(lineFollowerRight, INPUT);
  pinMode(turnDetectorLeft, INPUT);
  pinMode(turnDetectorRight, INPUT);
}

void loop() {
  getLineFollowerValues();
  setLineFollowerValueArray();

  if (leftLineValue == 1 && rightLineValue == 1) {
    driveForward();
  }
  else if (leftLineValue == 1 && rightLineValue == 0) {
    turnLeft();
  }
  else if (leftLineValue == 0 && rightLineValue == 1) {
    turnRight();
  }
  else if (leftLineValue == 0 && rightLineValue == 0) {
    releaseMotors();
  }
  delay(20);
}