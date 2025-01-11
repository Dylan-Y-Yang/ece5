const int buttonPin = 3;

void setup() {
Serial.begin(9600);
pinMode(buttonPin, INPUT); 
}

void loop() {
  int button;
  button = digitalRead(buttonPin);
  if (button == HIGH) {
    Serial.println("PRESSED");
  }
  else {
    Serial.println("RELEASED");
  }
  delay(100);
}
