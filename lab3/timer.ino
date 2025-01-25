//  Task 8 Minutes and seconds
//  Go back to counting up from zero, but regard the 4 digits as the display of a clock with 2 digits for
//  the minutes and 2 digits for the seconds. 
//  Modify your sketch so that your seconds do not go above 59. Specifically, when your counter
//  reaches 0059 it should proceed to 0100, when it reaches 0159 it should proceed to 0200, and so on

const int dataPin=8;
const int clockPin=10;
const int latchPin=9;
const int thousandsPin = 2, hundredsPin = 3, tensPin = 4, onesPin = 5; 
int tenMinutes, minutes, tenSeconds, seconds;
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
  t = millis()/1000;
  tenMinutes = t/600%10;
  minutes = t/60%10;
  tenSeconds = t/10%6;
  seconds = t%10;
  // if (t <= 6000) {
    writeDigit(tenMinutes, 0);
    writeDigit(minutes, 1);
    writeDigit(tenSeconds, 2);
    writeDigit(seconds , 3);
    delay(1);
  // }
}

