volatile byte state = LOW;
void setup()
{
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);//input pin 7 other terminal connected to GND
}
void loop()
{
  Serial.println(digitalRead(7));
  delay(10);
}
