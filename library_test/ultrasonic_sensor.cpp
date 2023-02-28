#include "my_library.h"

void setUltrasonicSensorPinout() {
  pinMode(ULTRASONIC_TRIGGER, OUTPUT); // Sets the trigger pin as an Output
  pinMode(ULTRASONIC_ECHO, INPUT); // Sets the echo pin as an Input
}
void triggerUltrasonicPulse() { 
  // Function to write an ultrasonic sound pulse to the trigger pin
  digitalWrite(ULTRASONIC_TRIGGER, LOW); // clears the trigPin
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIGGER, HIGH);  // sets the trigger pin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIGGER, LOW);
}
float getUltrasonicDistanceReading() {
  triggerUltrasonicPulse();
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH); // reads the echo pin, returns the sound wave travel time in microseconds
  float distance = duration * 0.0343 / 2; // using 343 metres per second as the speed of sound
  return distance;
}
float getAverageDistanceReading() {
  float avgDistance = 0;
  int numberOfReadings = 25;
  for (int i = 0; i < numberOfReadings; i++) {
    float latestDistance = getUltrasonicDistanceReading();
    avgDistance += latestDistance;
  }
  avgDistance = avgDistance / 25;
  return avgDistance;
}
bool durationIsLessThan5000() {
  // why less than 5000?
}

/*void loop() {
  float ultrasonicDistance = getUltrasonicDistanceReading();
  
  if(ultrasonicDistance < 5000) {
    float averageDistance = getAverageDistanceReading();
  }
  
  Serial.println(averageDistance);
}*/