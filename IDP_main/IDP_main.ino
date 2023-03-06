#include "IDP_header.h"

// initialise enums
OverallState overallState = START_SEQUENCE;
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
  setUltrasonicSensorPinout();
  initialiseAllLEDs();
  initInfraredSensor();
  
  blockCollectionState = DISENGAGED;

  /*
  if button is to be used to start the program, logic could be: with void onButtonPress() as below
  pinMode(PUSH_BUTTON_SWITCH, INPUT);
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_SWITCH), onButtonPress, HIGH);*/
}

/*void onButtonPress {
  overallState = START_SEQUENCE // (have enums inc. overallState set to NULL originally so the program starts only when the button is pressed?)
}*/

void loop() {
  switch (overallState) {
    case START_SEQUENCE:
      //startSequence();
      Serial.println("start sequence");
      digitalWrite(AMBER_LED, HIGH);
      driveForward();
      delay(1000);
      overallState = BLOCK_COLLECTION;
      digitalWrite(AMBER_LED, LOW);
      break;
    case IDLE:
      break;
    case LINE_FOLLOWING:
      //followLine();
      digitalWrite(RED_LED, HIGH);
      Serial.println("line following");
      releaseMotors();
      delay(100);
      break;
    case BLOCK_COLLECTION:
      //hardcode the robot to align with the block and TRY to return to the line 
      digitalWrite(GREEN_LED, HIGH);
      Serial.println("block collection");
      collectBlockSequence();
      digitalWrite(GREEN_LED, LOW);
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