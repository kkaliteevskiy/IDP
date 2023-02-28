#include "my_library.h"

int getInfraredAnalogReading() {
  // analog read of infrared sensor value (measures distance)
}
float getTenPointMovingAverage() {
  // get a ten point moving average of the sensor readings in order to smooth the readings and reduce effect of any sharp spikes/erroneous readings
}
float averageOfTenValues(int array[10]) {
  // calculate the average of an array containing ten values
  // will be called in the getTenPointMovingAverage() function in order to calculate the average sensor reading
}