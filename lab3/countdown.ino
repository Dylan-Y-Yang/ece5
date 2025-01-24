// Task 7 Countdown
//  Modify your sketch so that your counter counts down from 100 seconds and stops at 0. This and the
//  remaining task should be solved without making any changes to the hardware circuit that you have
//  already built.


const int dataPin=8;
const int clockPin=10;
const int latchPin=9;
const int thousandsPin = 2, hundredsPin = 3, tensPin = 4, onesPin = 5; 
int t;


int digit2segments[]=
{
 0b11000000, // digit 0
 0b11111001, // digit 1
 0b10100100, // digit 2
 0b10110000, // digit 3
 0b10011001, // digit 4
 0b10010010, // digit 5
 0b10000010, // digit 6
 0b11111000, // digit 7
 0b10000000, // digit 8
 0b10010000 // digit 9
};

void setup() 
{
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(thousandsPin, OUTPUT);
  pinMode(hundredsPin, OUTPUT);
  pinMode(tensPin, OUTPUT);
  pinMode(onesPin, OUTPUT);
  Serial.begin(9600);
  t = 100000; 
}

int getThousands(int num) {
    return num % 10000 / 1000;
}

int getHundreds(int num) {
    return num % 1000 / 100;
}

int getTens(int num) {
    return num % 100 / 10;
}

int getOnes(int num) {
    return num % 10;
}

void writeDigit(int value, int digit) {
  digitalWrite(thousandsPin, HIGH);
  digitalWrite(hundredsPin, HIGH);
  digitalWrite(tensPin, HIGH);
  digitalWrite(onesPin, HIGH);
  
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST,  ~digit2segments[value]);
  digitalWrite(latchPin, LOW);

  digitalWrite(thousandsPin,(digit==0)?LOW:HIGH);
  digitalWrite(hundredsPin,(digit==1)?LOW:HIGH);
  digitalWrite(tensPin,(digit==2)?LOW:HIGH);
  digitalWrite(onesPin,(digit==3)?LOW:HIGH);
  delay(1);
}


void loop() 
{
  t = (t - millis())/1000;
  if (t >= 0) {
  Serial.println(t);
    writeDigit(getThousands(t), 0);
    writeDigit(getHundreds(t), 1);
    writeDigit(getTens(t), 2);
    writeDigit(getOnes(t), 3);
    delay(1000); 
  }
}
