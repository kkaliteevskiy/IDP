#include "IDP_header.h"

// initialise enums
OverallState overallState = IDLE;
DrivingState drivingState = NOT_MOVING;
BlockColour blockColour = UNKNOWN;

bool firstBlock = true;

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
      if (firstBlock) {
        detectColour();
        indicateColourDetected();
        firstBlock = false;
      }
      else {
        blockColour = BLUE;
        delay(500); // allow grabbing mechanism time to close
      }
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
    case ERROR:
      // flash error signal
      if (leftLineValue == 1 || rightLineValue == 1) {
        overallState = LINE_FOLLOWING; // resume as normal
      }
      break;
    default:
      // error?
      break;
  }
}

void onButtonPress() {
  overallState = START_SEQUENCE;
}