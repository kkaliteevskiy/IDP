int GREEN_LED = 7;
int RED_LED = 8;
int COLOUR_DETECTOR_POWER = 12;
int COLOUR_DETECTOR_READING = 13;
int colourDetectorValue = 0;
enum BlockColour {BROWN, BLUE, UNKNOWN};
BlockColour blockColour = UNKNOWN;



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
  for (int i = 0; i < 1000; i++) {
    getColourDetectorValue();
    delay(5); // sets overall limit to 5 seconds
    if (colourIsBlue()) {
      blockColour = BLUE;
      break;
    }
  }  
  digitalWrite(COLOUR_DETECTOR_POWER, LOW); // stop powering the colour detection circuit
}
void indicateColourDetected() {
  int correctLED;
  if (blockColour == BROWN) {
    correctLED = RED_LED;
  } else correctLED = GREEN_LED;
  digitalWrite(correctLED, HIGH); // light correct led (green for blue block, red for brown block) - and ONLY light that correct led
  delay(5000); // wait 5 seconds
  digitalWrite(correctLED, LOW); // turn off led
}

void setup() {
  Serial.begin(9600); // set up Serial library

  pinMode(COLOUR_DETECTOR_READING, INPUT);
  pinMode(COLOUR_DETECTOR_POWER, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  Serial.println("START: Detecting colour...");
  detectColour();
  Serial.print("detectColour() finished. Colour detected was: ");
  Serial.println(blockColour);
  Serial.println("(blue=1, brown=0)");
  Serial.println("indicateColourDetected() will run now for 5 seconds...");
  indicateColourDetected();
  Serial.println("finished indicating the correct colour. Loop will restart after 5 seconds");
  delay(5000);
}