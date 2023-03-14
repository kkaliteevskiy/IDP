/*
Module containing functions relating LED control and colour detection
nb. control of flashing amber LED is handled in motor functions as this is the easiest way to enable the led cycle iff the robot is moving 
*/
#include "IDP_header.h"

// some constants
int colourDetectorValue = 0;

void setColourDetectorPinout() {
  pinMode(COLOUR_DETECTOR_READING, INPUT);
  pinMode(COLOUR_DETECTOR_POWER, OUTPUT);
}
void initialiseAllLEDs() {
  pinMode(AMBER_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(AMBER_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}
void getColourDetectorValue() {
  colourDetectorValue = digitalRead(COLOUR_DETECTOR_READING);
}
bool colourIsBlue() {
  return colourDetectorValue == 1;
}
void detectColour() {
  // this function assumes the block is within sensing range of the robot
  // keep reading colour detector up to a limited number of times - if no positive output is detected, assume block colour was brown
  digitalWrite(COLOUR_DETECTOR_POWER, HIGH); // power the colour detection circuit
  delay(500);
  blockColour = BROWN;
  for (int i = 0; i < 500; i++) {
    getColourDetectorValue();
    delay(5); // sets overall limit to 2.5 seconds
    if (colourIsBlue()) {
      blockColour = BLUE;
      break;
    }
  }  
  digitalWrite(COLOUR_DETECTOR_POWER, LOW); // stop powering the colour detection circuit
}
void indicateColourDetected() {
  // stop robot from moving - ensure robot is not moving while relevant LED is lit
  // light correct led (green for blue block, red for brown block) - and ONLY light that correct led
  // wait 5 seconds
  // turn off led, resume normal motion
  int correctLED;
  if (blockColour == BROWN) {
    correctLED = RED_LED;
  }
  else {correctLED = GREEN_LED;}
  digitalWrite(correctLED, HIGH);
  delay(5000);
  digitalWrite(correctLED, LOW);
}