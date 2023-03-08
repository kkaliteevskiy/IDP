#include "IDP_header.h"

// initialise enums
OverallState overallState = IDLE;
DrivingState drivingState = NOT_MOVING;
BlockCollectionState blockCollectionState = DISENGAGED;
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
      //hardcode the robot to align with the block and TRY to return to the line 
      startBlockCollection();
      captureBlock(); // close the capture mechanism
      delay(1000);
      finishBlockCollection();
      break;
    case BLOCK_PLACEMENT:
      startBlockPlacement();
      releaseBlock(); // open the capture mechanism
      delay(1000);
      finishBlockPlacement();
      break;
    case ERROR:
      // flash error signal
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      delay(500);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
      break;
    default:
      // error?
      break;
  }
}

void onButtonPress() {
  overallState = START_SEQUENCE;
}