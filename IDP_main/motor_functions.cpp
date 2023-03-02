#include "IDP_header.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select motors using relevant ports M1, M2, M3 or M4.
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

// some constants
int runSpeed = 255;
int leftTurnValue = 0;
int leftLineValue = 0;
int rightLineValue = 0;
int rightTurnValue = 0;

void lookForMotorShield() {
    if (!AFMS.begin()) {
        Serial.println("Warning: Could not find Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Motor Shield found.");
}
void setMotorSpeeds(int speed) {
    // range is from 0 (min) to 255 (max)
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
}
void releaseMotors() {
  if (drivingState != NOT_MOVING) {
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    drivingState = NOT_MOVING;
  }
}
void driveForward() {
  if (drivingState != MOVING_FORWARD) {
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    drivingState = MOVING_FORWARD;
  }
}
void driveBackward() {
  if (drivingState != MOVING_BACKWARD) {
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    drivingState = MOVING_BACKWARD;
  }
}
void turnLeft() {
  if (drivingState != TURNING_LEFT) {
    leftMotor->run(RELEASE);
    rightMotor->run(FORWARD);
    drivingState = TURNING_LEFT;
  }
}
void turnRight() {
  if (drivingState != TURNING_RIGHT) {
    leftMotor->run(FORWARD);
    rightMotor->run(RELEASE);
    drivingState = TURNING_RIGHT;
  }
}
void getLineFollowerValues() {
    leftLineValue = digitalRead(LINE_FOLLOWER_LEFT);
    rightLineValue = digitalRead(LINE_FOLLOWER_RIGHT);
    leftTurnValue = digitalRead(TURN_DETECTOR_LEFT);
    rightTurnValue = digitalRead(TURN_DETECTOR_RIGHT);
}
void followLine() {
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
}

void turnRight(int angle){

}

void turnLeft(int angle){

}

void errorRecoverySequence() {

}

void startSequence() {
  do {
    driveForward();
    getLineFollowerValues();
  } while (leftLineValue == 0 && rightLineValue == 0);
  // now the robot has reached its first white line
  do {
    // driveForward() doesn't need to be called again
    getLineFollowerValues();
  } while (leftLineValue == 1 || rightLineValue == 1);
  // now the robot has entirely crossed the first line
  do {
    // driveForward() doesn't need to be called again
    getLineFollowerValues();
  } while (rightLineValue == 0);
  // now the robot has reached the second white line - time to start line following
  // only checking for rightLineValue == 0 so that line following does not try a left turn when left sensor hits line first
}