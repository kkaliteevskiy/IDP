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
int stepDelay = 500;
int rotationDelay = 2850;
bool atJunction = false; //flag to test whether the robot is currently going over a line
int turnNo = 0;
int currentSpeed = 0;
int noBlocksDelivered = 0;

void lookForMotorShield() {
  if (!AFMS.begin()) {
      Serial.println("Warning: Could not find Motor Shield. Check wiring.");
      while (1);
  }
  Serial.println("Motor Shield found.");
}
void setMotorSpeeds(int speed) {
    // range is from 0 (min) to 255 (max)
    if (speed != currentSpeed) {
      leftMotor->setSpeed(speed);
      rightMotor->setSpeed(speed);
      currentSpeed = speed;
    }
}
void releaseMotors() {
  if (drivingState != NOT_MOVING) {
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    digitalWrite(AMBER_LED, LOW);
    drivingState = NOT_MOVING;
  }
}
void driveForward() {
  if (drivingState != MOVING_FORWARD) {
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    digitalWrite(AMBER_LED, HIGH);
    drivingState = MOVING_FORWARD;
  }
}
void driveBackward() {
  if (drivingState != MOVING_BACKWARD) {
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    digitalWrite(AMBER_LED, HIGH);
    drivingState = MOVING_BACKWARD;
  }
}
void turnLeft() {
  if (drivingState != TURNING_LEFT) {
    leftMotor->run(RELEASE);
    rightMotor->run(FORWARD);
    digitalWrite(AMBER_LED, HIGH);
    drivingState = TURNING_LEFT;
  }
}
void turnRight() {
  if (drivingState != TURNING_RIGHT) {
    leftMotor->run(FORWARD);
    rightMotor->run(RELEASE);
    digitalWrite(AMBER_LED, HIGH);
    drivingState = TURNING_RIGHT;
  }
}
void turnLeftReversing() {
  if (drivingState != TURNING_LEFT_REVERSING) {
    leftMotor->run(BACKWARD);
    rightMotor->run(RELEASE);
    digitalWrite(AMBER_LED, HIGH);
    drivingState = TURNING_LEFT_REVERSING;
  }
}
void turnRightReversing() {
  if (drivingState != TURNING_RIGHT_REVERSING) {
    leftMotor->run(RELEASE);
    rightMotor->run(BACKWARD);
    digitalWrite(AMBER_LED, HIGH);
  drivingState = TURNING_RIGHT_REVERSING;
  }
}
void setLineFollowerPinout() {
  pinMode(LINE_FOLLOWER_LEFT, INPUT);
  pinMode(LINE_FOLLOWER_RIGHT, INPUT);
  pinMode(TURN_DETECTOR_LEFT, INPUT);
  pinMode(TURN_DETECTOR_RIGHT, INPUT);
}
void getLineFollowerValues() {
    leftLineValue = digitalRead(LINE_FOLLOWER_LEFT);
    rightLineValue = digitalRead(LINE_FOLLOWER_RIGHT);
    leftTurnValue = digitalRead(TURN_DETECTOR_LEFT);
    rightTurnValue = digitalRead(TURN_DETECTOR_RIGHT);
}
void followLine() {
  if (leftLineValue == 1 && rightLineValue == 1) {
    setMotorSpeeds(runSpeed);
    driveForward();
  }
  else if (leftLineValue == 1 && rightLineValue == 0) {
    turnLeft();
  }
  else if (leftLineValue == 0 && rightLineValue == 1) {
    turnRight();
  }
  else if (leftLineValue == 0 && rightLineValue == 0) {
    //errorRecoverySequence();
    turnRight();
  }

  //check for the presence of turns
  if(overallState != END_SEQUENCE){
    checkTurns();
  }
  
}

void checkTurns(){
  bool turnDetected = rightTurnValue;
  if(atJunction == false && turnDetected == true){//check if the robot has driven onto a turn
    atJunction = true;//set flag to true
    turnNo = (turnNo+1)%2;
    Serial.print("Turn number: ");
    Serial.println(turnNo);
    if(turnNo == 1 && overallState != END_SEQUENCE){
      overallState = BLOCK_COLLECTION;
    }
    else if(overallState != END_SEQUENCE){
      overallState = BLOCK_PLACEMENT;
    }
  }

  if(atJunction == true && turnDetected == false){//robot has gone off a line 
    atJunction = false;//set flag to false
  }

}



void errorRecoverySequence() {
  /*
  drive forward for x seconds (long enough to theoretically clear the ramp)
  keep checking line sensors regularly, if one returns then break out of delay and start line following again as normal
  after x seconds, if line following sensors still return 0, assume we are off the line
  keep driving and checking turn detectors, when one returns a 1 we know which way we went wrong
  */
  /*driveForward();
  for (int i = 0; i < 300; i++) {
    getLineFollowerValues();
    if (leftLineValue == 1 || rightLineValue == 1) {
      return; // break out of function and start following line again
    }
    delay(10);
  }
  if (flag == false) {
  // line sensors still return 0, assume we are off the line
  releaseMotors();
  flag = true;
  overallState = ERROR; // TODO - FIX
  }*/
}

void startSequence() {
  Serial.println("in end function");
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
  rightMotor->setSpeed(160);
  leftMotor->setSpeed(80);
  while (leftLineValue == 0) {
    // driveForward() doesn't need to be called again
    getLineFollowerValues();
  }
  setMotorSpeeds(120);
  // now the robot has reached the second white line - time to start line following
  // only checking for leftLineValue == 0 so that line following does not try a right turn when left sensor hits line first

  // start sequence finished, begin line following
  overallState = LINE_FOLLOWING;
}

void startBlockCollection(){
  //hardcoded function to collect the block
  overallState = BLOCK_COLLECTION;

  setMotorSpeeds(255); //decrease motor speed for greater control
  
  //move forward to the position where the robot will turn
  driveForward();
  delay(1650);//adapt this in future version
  releaseMotors();
  delay(stepDelay);

  //rotate 90 degrees
  turnRightReversing();
  delay(rotationDelay);
  releaseMotors();
  delay(stepDelay);

  //move forward towards the block
  driveForward();
  delay(1200);
  releaseMotors();
  delay(stepDelay);
}
void finishBlockCollection() {
  //reverse back to the line
  driveBackward();
  delay(1200);
  releaseMotors();
  delay(stepDelay);

  //rotate 90 degrees
  turnRight();
  delay(rotationDelay);
  releaseMotors();
  delay(stepDelay);

  setMotorSpeeds(runSpeed);
  //block collection finished, return to line following
  overallState = LINE_FOLLOWING;
}

void startBlockPlacement(){
  overallState = BLOCK_PLACEMENT;
  setMotorSpeeds(255);
  //drive forward to align wheel with line
  driveForward();
  delay(1650);
  releaseMotors();
  delay(stepDelay);

  //turn 90 degrees
  turnRightReversing();
  delay(rotationDelay);
  releaseMotors();
  delay(stepDelay);

  //move forward
  driveForward();
  delay(1500);
  releaseMotors();
  delay(stepDelay);
}
void finishBlockPlacement() {
  //drive backward
  driveBackward();
  delay(1500);
  releaseMotors();
  delay(stepDelay);

  noBlocksDelivered += 1;

  //continue
  setMotorSpeeds(runSpeed);
  
  if(noBlocksDelivered == 0){//if the final block is delivered, go into the end sequence
    turnLeft();
    delay(rotationDelay + 300);
    getLineFollowerValues();
    overallState = END_SEQUENCE;
  }
  else{//else continue collecting blocks
    //rotate 90 degrees
    turnRight();
    delay(rotationDelay - 300);
    releaseMotors();
    delay(stepDelay);
    overallState = LINE_FOLLOWING;        
  }
}

void endSequence(){
  
  do{ //follow the line while a turn is not detected
    followLine();
    getLineFollowerValues();
  }while(rightTurnValue == 0);
  
  driveForward();
  delay(1650);//move forward to align the wheels with the turn 
  releaseMotors();
  delay(stepDelay);
  turnRightReversing();
  delay(rotationDelay);
  releaseMotors();
  delay(stepDelay);
  driveForward();
  delay(2500);//delay to get to the final position
  releaseMotors();
  overallState = IDLE;
}