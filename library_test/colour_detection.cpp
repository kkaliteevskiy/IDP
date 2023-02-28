#include "my_library.h"

// some constants
int colourDetectorValue = 0;

void getColourDetectorValue() {
  colourDetectorValue = digitalRead(COLOUR_DETECTOR);
}
bool colourIsBlue() {
  return colourDetectorValue == 1;
}