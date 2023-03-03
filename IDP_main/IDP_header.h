#ifndef IDP_HEADER_H
#define IDP_HEADER_H

#include <Arduino.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// set working pinout - pin locations for inputs/outputs
#define LINE_FOLLOWER_LEFT 1
#define LINE_FOLLOWER_RIGHT 2
#define TURN_DETECTOR_LEFT 3
#define TURN_DETECTOR_RIGHT 4
#define AMBER_LED 5
#define GREEN_LED 6
#define RED_LED 7
#define COLOUR_DETECTOR 8
#define SERVO_LEFT 9
#define SERVO_RIGHT 10
#define ULTRASONIC_TRIGGER 11
#define ULTRASONIC_ECHO 12
#define INFRARED_ANALOG_INPUT A0

#define SOUND_SPEED 0.0343

// some constants - intitialised in *.cpp file
extern int runSpeed;
extern int leftTurnValue;
extern int leftLineValue;
extern int rightLineValue;
extern int rightTurnValue;

//enumerate robot states
enum OverallState {ERROR, IDLE, START_SEQUENCE, LINE_FOLLOWING, BLOCK_COLLECTION, BLOCK_PLACEMENT};
extern OverallState overallState;
enum DrivingState {MOVING_FORWARD, TURNING_RIGHT, TURNING_LEFT, MOVING_BACKWARD, NOT_MOVING};
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
void getLineFollowerValues();
void setLineFollowerValueArray();
void followLine();
void startSequence();
void collectBlockSequence();
//colour detection
void getColourDetectorValue();
bool colourIsBlue();
void detectColour();
void indicateColourDetected();
void indicateCorrectDropOffPoint();
void cycle_amber_led();
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
void captureBlock();
void releaseBlock();
void writeServos(int angle);

#endif