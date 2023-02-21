//Test to see the operation of the range sensor

int inputPin = A0;
int val[10];
int i = 0;

void setup(){
  Serial.begin(9600);
  Serial.println('Testing range sensor');
  pinMode(inputPin, INPUT);
}

void loop(){
  float sum = 0.0;

  //Read 10 point moving average

  val[i] = analogRead(inputPin);
  for(int j = 0; j <10; j++){
    sum += val[j];
  }
  sum = sum/10;

  //output to Serial

  Serial.println(sum);
  delay(50);
  i = (i + 1)%10;
}