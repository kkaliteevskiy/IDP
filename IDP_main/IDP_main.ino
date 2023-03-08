#include "IDP_header.h"

// initialise enums
OverallState overallState = IDLE;
DrivingState drivingState = NOT_MOVING;
BlockCollectionState blockCollectionState = DISENGAGED;
BlockColour blockColour = UNKNOWN;
int turnNo = 0;

void setup() {
  Serial.begin(9600); // set up Serial library

  //setup Motors
  lookForMotorShield();
  setMotorSpeeds(runSpeed);
  releaseMotors();
  
  // set other inputs/outputs
  setLineFollowerPinout();
  initialiseAllLEDs();
  setServos();
  //setUltrasonicSensorPinout();
  //initInfraredSensor();

  // set up push button which will start the robot in a controlled manner
  pinMode(PUSH_BUTTON_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_SWITCH), onButtonPress, CHANGE);
}

void loop() {
  switch (overallState) {
    case IDLE:
      // do nothing, wait for start sequence to be triggered by button
      break;
    case START_SEQUENCE:
      startSequence();
      break;
    case LINE_FOLLOWING:
      getLineFollowerValues();
      followLine();
      //if (isBlockPresent()) {
      //  overallState = BLOCK_COLLECTION;
      //}
      //else if (blockCollectionState = COLLECTED && deliveryZoneReached()) {
      //  overallState = BLOCK_PLACEMENT
      //}

      break;
    case BLOCK_COLLECTION:
      //hardcode the robot to align with the block and TRY to return to the line 
      Serial.println("block collection");
      collectBlockSequence();
      break;
    case BLOCK_PLACEMENT:
      placeBlockSequence();
      break;
    case ERROR:
      break;
    default:
      // error?
      break;
  }
}

void onButtonPress() {
  overallState = START_SEQUENCE;
}