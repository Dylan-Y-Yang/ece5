const int buttonPin = 3, LEDpin = 8;
int t;
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  int button = digitalRead(buttonPin);
  if (button == HIGH) {
    digitalWrite(LEDpin, HIGH);
    delay(250);
    digitalWrite(LEDpin, LOW);
    delay(250);
  } else {
    digitalWrite(LEDpin, HIGH);
    delay(1000);
    digitalWrite(LEDpin, LOW);
    delay(1000);
  }
}

void setDelay(int delay) {
  t = delay;
}
