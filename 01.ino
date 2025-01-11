const int LEDpin = 8;
void setup () {
  pinMode (LEDpin, OUTPUT);
}
void loop () {
  digitalWrite (LEDpin, HIGH);
  delay (250);
  digitalWrite (LEDpin, LOW);
  delay (250);
}