/*
Test for line following sensors
*/

// CHANGE VALUE OF THIS CONSTANT TO CHANGE HOW OFTEN LINE SENSOR VALUES ARE PRINTED
int delayTime = 200;

// initialise IR sensor pin locations for line following
int lineFollowerLeft = 4;
int lineFollowerRight = 5;
int turnDetectorLeft = 3;
int turnDetectorRight = 6;
int lineFollowerValues[4];

void setup() {
  Serial.begin(9600); // set up Serial library

  // set line follower inputs
  pinMode(lineFollowerLeft, INPUT);
  pinMode(lineFollowerRight, INPUT);
  pinMode(turnDetectorLeft, INPUT);
  pinMode(turnDetectorRight, INPUT);

  Serial.println("Values are printed from left to right, in the form:");
  Serial.println("[leftTurnValue  leftLineValue  rightLineValue  rightTurnValue]");
  delay(500);
  Serial.println("Starting test for line following sensors...");
}

void loop() {
  int leftLineValue = digitalRead(lineFollowerLeft);
  int rightLineValue = digitalRead(lineFollowerRight);
  int leftTurnValue = digitalRead(turnDetectorLeft);
  int rightTurnValue = digitalRead(turnDetectorRight);
  lineFollowerValues[0] = leftTurnValue;
  lineFollowerValues[1] = leftLineValue;
  lineFollowerValues[2] = rightLineValue;
  lineFollowerValues[3] = rightTurnValue;
  for (int i = 0; i < 4; i++) {
    Serial.print(lineFollowerValues[i]);
  }
  Serial.println("");

  delay(delayTime);
}