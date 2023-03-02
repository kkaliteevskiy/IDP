#include "IDP_header.h"

// initialise enums
OverallState overallState = START_SEQUENCE;
DrivingState drivingState = NOT_MOVING;
BlockCollectionState blockCollectionState = DISENGAGED;
BlockColour blockColour = UNKNOWN;

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
  blockCollectionState = COLOUR_SENSING;
}

void loop() {
  /*if (maneuver == START_SEQUENCE) {
    startSequence();
    maneuver = NA; // set next maneuver to right turn after starting sequence has completed
  }
  else if (maneuver == NA) {
    followLine();
  }*/

  Serial.println("start");
  if (blockCollectionState == COLOUR_SENSING) {
    detectColour();
    indicateColourDetected();
  }
}