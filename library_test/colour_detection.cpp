#include "my_library.h"

// some constants
int colourDetectorValue = 0;

void getColourDetectorValue() {
  colourDetectorValue = digitalRead(COLOUR_DETECTOR);
}
bool colourIsBlue() {
  return colourDetectorValue == 1;
}
void lightLED(int LED) {
  digitalWrite(LED, HIGH);
}
void indicateColourDetected() {
  // stop robot from moving - ensure robot is not moving while relevant LED is lit
  // light correct led (green for blue block, red for brown block) - and ONLY light that correct led
  // wait 5 seconds
  // turn off led, resume normal motion
}
void indicateCorrectDropOffPoint() {
  // if colour is brown, block should be delivered to the red drop off square
  // if colour is blue, block should be delivered to the green drop off square.

}
void cycle_amber_led() {
  // The robot must display a flashing amber light (2Hz±10%) when and only when it is moving.
  // if (robot is moving) output HIGH to AMBER_LED (NE555P Precision Timer should handle oscillation / flashing)
  // if (robot not moving) stop output to AMBER_LED (digitalWrite LOW) until robot moves again

  /*
  TODO
    how to check if robot not moving?
      -> could check if motors are currently running RELEASE
      -> could set motor speed to zero when robot stops, and check motor speed
      -> could set some kind of boolean flag eg. bool robotIsMoving, bool robotHasStopped etc.
    how to handle led cycle?
      -> could initialise with HIGH so that led cycles indefinitely
      -> then either check if led is still moving eg. every cycle of loop(), with some if() statement
      -> or, attach some kind of interrupt eg. which triggers when detect that robot stops moving and a flag is set
    maybe functions will look something like
    void setAmberLEDCycle()
    void suspendAmberLEDCycle()
  */
}