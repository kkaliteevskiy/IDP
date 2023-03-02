#include "IDP_header.h"

int analog_reading[25];
int threshold_analog_reading = 200;

void initInfraredSensor(){
  pinMode(INFRARED_ANALOG_INPUT, INPUT);
}

float getInfraredAnalogReading() {//function return the 25 point average analog reading of the IR sesnor
  for(int i = 0; i < 25; i++){//take readings
      analog_reading[i] = analogRead(INFRARED_ANALOG_INPUT);
  }

  float mean = 0.0;//calculate mean
  for(int i  = 0; i < 25; i++){
    mean += analog_reading[i];
  }
  mean = mean/25;

  return mean;
}

bool isBlockPresent(){
  return (getInfraredAnalogReading() > threshold_analog_reading);
}
