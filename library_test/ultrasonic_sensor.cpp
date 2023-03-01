#include "my_library.h"

const int numberOfReadings = 25;
float ultrasonicDistanceList[numberOfReadings];
int listPointer = 0;

void setUltrasonicSensorPinout() {
  pinMode(ULTRASONIC_TRIGGER, OUTPUT); // Sets the trigger pin as an Output
  pinMode(ULTRASONIC_ECHO, INPUT); // Sets the echo pin as an Input
}
float takeUltrasonicDistanceReadingAndGetAverage() {
  getUltrasonicDistanceReading();
  return getAverageDistanceReading();
}
float getAverageDistanceReading() {
  float avgDistance = 0;
  for (int i = 0; i < numberOfReadings; i++) {
    avgDistance += ultrasonicDistanceList[i];
  }
  avgDistance = avgDistance / numberOfReadings;
  return avgDistance;
}
void getUltrasonicDistanceReading() {
  triggerUltrasonicPulse();
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH); // reads the echo pin, returns the sound wave travel time in microseconds
  if (duration < 5000) { // only include readings within a reasonable range - large duration is either anomalous or not relevant
    float distance = duration * SOUND_SPEED / 2;
    addDistanceToListAndIncrementPosition(distance);
  }
}
void triggerUltrasonicPulse() { 
  // Function to write an ultrasonic sound pulse to the trigger pin
  digitalWrite(ULTRASONIC_TRIGGER, LOW); // clears the trigPin
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIGGER, HIGH);  // sets the trigger pin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIGGER, LOW);
}
void addDistanceToListAndIncrementPosition(float dist) {
  ultrasonicDistanceList[listPointer] = dist;
  listPointer = (listPointer + 1) % 25; // increment pointer
}