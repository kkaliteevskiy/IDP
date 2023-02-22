const int trigPin = 11;
const int echoPin = 12;
long duration;
float distance_list[25];
int i = 0;
float average_distance;
// defines variables
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Begin");
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  if(duration <5000){
  // Calculating the distance
    distance_list[i] = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: ");
    for(int j = 0; j <25; j++){
      average_distance += distance_list[j];
    } 

    average_distance = average_distance /25;

    Serial.println(average_distance);
    i = (i+1)%25;
  }
}