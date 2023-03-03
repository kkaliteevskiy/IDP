#include "IDP_header.h"

// initialise enums
OverallState overallState = START_SEQUENCE;
DrivingState drivingState = NOT_MOVING;
BlockCollectionState blockCollectionState = DISENGAGED;
BlockColour blockColour = UNKNOWN;

void setup() {
  Serial.begin(9600); // set up Serial library

  //setup Motors
  lookForMotorShield();
  setMotorSpeeds(runSpeed);
  releaseMotors();
  
  // set line follower inputs
  pinMode(LINE_FOLLOWER_LEFT, INPUT);
  pinMode(LINE_FOLLOWER_RIGHT, INPUT);
  pinMode(TURN_DETECTOR_LEFT, INPUT);
  pinMode(TURN_DETECTOR_RIGHT, INPUT);
  
  // set other inputs/outputs
  setUltrasonicSensorPinout();
  pinMode(AMBER_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(COLOUR_DETECTOR, INPUT);
  //pinMode(INFRARED_ANALOG_INPUT, INPUT);
  initInfraredSensor();

  digitalWrite(AMBER_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  blockCollectionState = DISENGAGED;
}

void loop() {
  if(overallState == START_SEQUENCE) {
    //startSequence();
  }
  //follow line until block is detected
  // while(!isBlockPresent()) {
  //   followLine();
  // }

  //hardcode the robot to align with the block and TRY to return to the line 
  collectBlockSequence();

  //try to find the line if it is not aligned

  //continue line following

  //release block

  //placeholder to stop the robot from moving
  while(true){
    ;;
  } 




}