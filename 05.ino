const int redPin = 5, bluePin = 9, greenPin = 7, buttonPin = 11, power = 3;
int buttonPressed;
int period; // 7 colors per  

int colorState;


void setColor(int color) {
  colorState = color;
  switch (color) {
    case 0: // RED
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      break;
    case 1: // YELLOW 
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      break;
    case 2: // GREEN 
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      break;
    case 3: // AZURE
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      break;
    case 4: // BLUE
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
      break;
    case 5: // PURPLE
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH); 
      break;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(power, OUTPUT);
  buttonPressed = LOW;
  period = 500;
  digitalWrite(power, HIGH);
  colorState = 0;
  setColor(colorState);
}

void loop() {
  if (colorState >= 6) {
    colorState = 0;
  }
  Serial.println(colorState);
  while (digitalRead(buttonPin) == LOW) {
    Serial.println("RELEASED");
    if (digitalRead(buttonPin) == HIGH) {
      break;
    }
  }
  setColor(colorState);
  colorState++;
  delay(period); 
}


