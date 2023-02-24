#include "my_library.h"

void setup() {
  Serial.begin(9600); // set up Serial library

  lookForMotorShield();

  setMotorSpeeds(runSpeed);
  releaseMotors();
  
  // set line follower inputs
  pinMode(LINE_FOLLOWER_LEFT, INPUT);
  pinMode(LINE_FOLLOWER_RIGHT, INPUT);
  pinMode(TURN_DETECTOR_LEFT, INPUT);
  pinMode(TURN_DETECTOR_RIGHT, INPUT);
}

void loop() {
  getLineFollowerValues();
  followLine();
}