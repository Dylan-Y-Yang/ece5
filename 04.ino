const int buttonPin = 3, LEDpin = 8;
int period, LEDstate, lastButton;
unsigned long lastToggle;

void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(buttonPin, INPUT);
  period = 500;
  LEDstate = LOW;
  digitalWrite(LEDpin, LEDstate);
  lastButton = digitalRead(buttonPin);
}

void loop() {
  int button = digitalRead (buttonPin);
  if (lastButton == LOW && button == HIGH) {
    if (LEDstate == LOW) {
      LEDstate = HIGH;
    }
    else {
      LEDstate = LOW;
    }
    digitalWrite (LEDpin, LEDstate);
    delay(100); 
  }
  lastButton = button;
  // if (millis() >= lastToggle + period) {
  //   if (LEDstate == LOW) {
  //     LEDstate = HIGH;
  //   }
  //   else {
  //     LEDstate = LOW;
  //   }
  //   digitalWrite(LEDpin, LEDstate);
  //   lastToggle = millis();
  // }
}