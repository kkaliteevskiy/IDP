#ifndef IDP_HEADER_H
#define IDP_HEADER_H

#include <Arduino.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// set working pinout - pin locations for inputs/outputs
#define PUSH_BUTTON_SWITCH 2
#define TURN_DETECTOR_RIGHT 3
#define TURN_DETECTOR_LEFT 4
#define LINE_FOLLOWER_LEFT 5
#define LINE_FOLLOWER_RIGHT 6
#define GREEN_LED 7
#define RED_LED 8
#define SERVO_LEFT 9
#define SERVO_RIGHT 10
#define AMBER_LED 11
#define COLOUR_DETECTOR_POWER 12
#define COLOUR_DETECTOR_READING 13
#define ULTRASONIC_TRIGGER 15
#define ULTRASONIC_ECHO 16
#define INFRARED_ANALOG_INPUT A0

#define SOUND_SPEED 0.0343

// some constants - intitialised in *.cpp file
extern int runSpeed;
extern int leftTurnValue;
extern int leftLineValue;
extern int rightLineValue;
extern int rightTurnValue;
extern int turnNo;
extern int currentSpeed;

//enumerate robot states
enum OverallState {ERROR, IDLE, START_SEQUENCE, LINE_FOLLOWING, BLOCK_COLLECTION, BLOCK_PLACEMENT};
extern OverallState overallState;
enum DrivingState {MOVING_FORWARD, TURNING_RIGHT, TURNING_LEFT, MOVING_BACKWARD, NOT_MOVING, TURNING_LEFT_REVERSING, TURNING_RIGHT_REVERSING};
extern DrivingState drivingState;
enum BlockCollectionState {ALIGN_BLOCK, COLOUR_SENSING, GRABBING_BLOCK, DISENGAGED};
extern BlockCollectionState blockCollectionState;
enum BlockColour {BROWN, BLUE, UNKNOWN};
extern BlockColour blockColour;

// Function Prototypes
//motors and line following
void lookForMotorShield();
void setMotorSpeeds(int speed);
void releaseMotors();
void driveForward();
void driveBackward();
void turnLeft();
void turnRight();
void turnLeftReversing();
void turnRightReversing();
void setLineFollowerPinout();
void getLineFollowerValues();
void followLine();
void checkTurns();
void errorRecoverySequence();
void startSequence();
void startBlockCollection();
void finishBlockCollection();
void startBlockPlacement();
void finishBlockPlacement();
//colour detection
void setColourDetectorPinout();
void initialiseAllLEDs();
void getColourDetectorValue();
bool colourIsBlue();
void detectColour();
void indicateColourDetected();
//ultrasonic sensor
void setUltrasonicSensorPinout();
float takeUltrasonicDistanceReadingAndGetAverage();
float getAverageDistanceReading();
void getUltrasonicDistanceReading();
void triggerUltrasonicPulse();
void addDistanceToListAndIncrementPosition(float);
//infrared sensor
void initInfraredSensor();
float getInfraredAnalogReading();
bool isBlockPresent();
//servo
void setServos();
void writeServos(int angle);
void captureBlock();
void releaseBlock();

#endif