const int redPin = 5, bluePin = 9, greenPin = 7, buttonPin = 11, power = 3;
int buttonPressed, lastPress;
int period; // 7 colors per  
unsigned long lastToggle;

int colorState;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  buttonPressed = LOW;
  lastPress = LOW;
  period = 2000;
  digitalWrite(power, HIGH);
}

void loop() {
  buttonPressed = digitalRead(buttonPin);
  switch (colorState) {
    case 0:
      digitalWrite(redPin, HIGH);
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
  }
    
    
    delay(period);
    digitalWrite(greenPin, HIGH);
    delay(period);
    digitalWrite(redPin, LOW);
    delay(period);
    digitalWrite(bluePin, HIGH);
    delay(period);
    digitalWrite(greenPin, LOW);
    delay(period);
    digitalWrite(redPin, HIGH);
    delay(period);
    digitalWrite(bluePin, LOW);
    
  }
}






























// const int buttonPin = 3, LEDpin = 8;
// int period, LEDstate, lastButton;
// unsigned long lastToggle;

// void setup() {
//   Serial.begin(9600);
//   pinMode(LEDpin, OUTPUT);
//   pinMode(buttonPin, INPUT);
//   period = 500;
//   LEDstate = LOW;
//   digitalWrite(LEDpin, LEDstate);
//   lastButton = digitalRead(buttonPin);
// }

// void loop() {
//   int button = digitalRead (buttonPin);
//   if (lastButton == LOW && button == HIGH) {
//     if (LEDstate == LOW) {
//       LEDstate = HIGH;
//     }
//     else {
//       LEDstate = LOW;
//     }
//     digitalWrite (LEDpin, LEDstate);
//     delay(100); 
//   }
//   lastButton = button;
//   // if (millis() >= lastToggle + period) {
//   //   if (LEDstate == LOW) {
//   //     LEDstate = HIGH;
//   //   }
//   //   else {
//   //     LEDstate = LOW;
//   //   }
//   //   digitalWrite(LEDpin, LEDstate);
//   //   lastToggle = millis();
//   // }
// }