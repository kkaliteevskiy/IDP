#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <Arduino.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// set working pinout - pin locations for inputs/outputs
#define LINE_FOLLOWER_LEFT 1
#define LINE_FOLLOWER_RIGHT 2
#define TURN_DETECTOR_LEFT 3
#define TURN_DETECTOR_RIGHT 4

// some constants - intitialised in *.cpp file
extern int runSpeed;
extern int leftTurnValue;
extern int leftLineValue;
extern int rightLineValue;
extern int rightTurnValue;

// Function Prototypes
void lookForMotorShield();
void setMotorSpeeds(int speed);
void releaseMotors();
void driveForward();
void turnLeft();
void turnRight();
void getLineFollowerValues();
void setLineFollowerValueArray();
void followLine();

#endif