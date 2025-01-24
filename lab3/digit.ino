const int dataPin=8;
const int clockPin=10;
const int latchPin=9;

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

int count = 0;

void setup() 
{
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    Serial.begin(9600);
}


void loop() 
{
    while (true) {
        if (count > 10) break; 
        for (int value = 0; value < 10; value++) {
            digitalWrite(latchPin, HIGH);
            shiftOut(dataPin, clockPin, MSBFIRST,  digit2segments[value]);
            digitalWrite(latchPin, LOW);
            Serial.println(value);
            delay(1000);
        }
        count++;
    }
}
