/*
Program to turn on an LED if the distance sensor detects an object within a threshold distance.
Designed with GP2Y0A21YK Infrared Distance Sensor
*/

int ledPin = 13;   // LED connected to digital pin 13
int analogInputPin = A0; // analog input for distance sensor

int arrayPosition = 0;
bool distanceFlag = false;
int thresholdDistanceReading = 200;
int distanceSensorReadings[10];

// function declarations
float averageOfTenValues(int);


float getTenPointMovingAverage() {
  distanceSensorReadings[arrayPosition] = analogRead(analogInputPin); // read latest value and record in array
  float average = averageOfTenValues(distanceSensorReadings);
  arrayPosition = (arrayPosition + 1) % 10; // increment position in array
  return average;
}
float averageOfTenValues(int array[10]) {
  float result = 0.0;
  for(int i=0; i < 10; i++) {
    result += array[i];
  }
  result = result / 10;
  return result;
}

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(analogInputPin, INPUT);
}

void loop(){

  float averagedDistanceSensorReading = getTenPointMovingAverage();
  Serial.println(averagedDistanceSensorReading);
  delay(50);

  distanceFlag = (averagedDistanceSensorReading >= thresholdDistanceReading);
  digitalWrite(ledPin, distanceFlag);    // turn on LED if distance is within a certain range
}