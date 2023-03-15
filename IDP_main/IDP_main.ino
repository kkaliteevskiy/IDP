#include "IDP_header.h"

// initialise enums
OverallState overallState = IDLE;
DrivingState drivingState = NOT_MOVING;
BlockColour blockColour = UNKNOWN;

void setup() {
  Serial.begin(9600); // set up Serial library

  //setup Motors
  lookForMotorShield();
  setMotorSpeeds(runSpeed);
  releaseMotors();
  
  // set other inputs/outputs
  setServos();
  setLineFollowerPinout();
  setColourDetectorPinout();
  initialiseAllLEDs();
  
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
      break;
    case BLOCK_COLLECTION:
      startBlockCollection();
      captureBlock(); // close the capture mechanism
      if (noBlocksDelivered == 2) { // third (and final) block is currently being collected
        blockColour = BLUE;
      }
      else {
        detectColour();
      }
      indicateColourDetected();
      finishBlockCollection();
      break;
    case BLOCK_PLACEMENT:
      startBlockPlacement();
      releaseBlock(); // open the capture mechanism
      delay(500);
      finishBlockPlacement();
      break;
    case END_SEQUENCE:
      endSequence();
      break;
    default:
      // error?
      if (leftLineValue == 1 || rightLineValue == 1) {
        overallState = LINE_FOLLOWING; // resume as normal
      }
      break;
  }
}

void onButtonPress() {
  overallState = START_SEQUENCE;
}