#include "MIDIUSB.h"  // USB MIDI library

const byte MIDI_CHANNEL = 1;
const int buttonCount = 25;
const int DATAPIN = 2;
const int CLOCKPIN = 3;
const int LATCHPIN = 4;

union button_t
{
uint32_t all;
uint8_t bytes[4];
};

button_t state, last_state, debounce_state;



void setup()
{
Serial.begin(9600);
pinMode(DATAPIN, INPUT) ; 
pinMode(CLOCKPIN, OUTPUT);
pinMode(LATCHPIN, OUTPUT);
}


void loop()
{
digitalWrite(LATCHPIN, LOW);
delay(10);
digitalWrite(LATCHPIN, HIGH);


cli(); // no interrupt
for (int i = 3; i >= 0; --i)
{
  state.bytes[i] = ~shiftIn(DATAPIN, CLOCKPIN, MSBFIRST);
 }
sei(); // no interrupt


uint32_t pressed = state.all & ~last_state.all;
uint32_t released = ~state.all & last_state.all;


for (size_t button = 0; button <= buttonCount; ++button)
{
  if (pressed & (1UL << button))
  {
    noteOn(MIDI_CHANNEL, 59 + button, 100);
    Serial.print("Note ON: ");
    Serial.println(59 + button);
  }

  if (released & (1UL << button))
  {
    noteOff(MIDI_CHANNEL, 59 + button, 0);
    Serial.print("Note OFF: ");
    Serial.println(59 + button);
  }
}

readEncoder(ENCODER1_CLK, ENCODER1_DT, lastEncoder1StateCLK, 21); 
readEncoder(ENCODER2_CLK, ENCODER2_DT, lastEncoder2StateCLK, 22);
MidiUSB.flush(); 
last_state = state;
}

void readEncoder(int clkPin, int dtPin, int &lastStateCLK, int midiCC) {
 int currentStateCLK = digitalRead(clkPin);
 if (currentStateCLK != lastStateCLK) {
   int dtState = digitalRead(dtPin);

   static int midiValue = 64; 


   if (dtState != currentStateCLK) {
     midiValue += 5;  // Increase (CW)
   } else {
     midiValue -= 5;  // Decrease (CCW)
   }

   midiValue = constrain(midiValue, 0, 127);
  
   sendMIDIControlChange(midiCC, midiValue);
   Serial.print("MIDI CC ");
   Serial.print(midiCC);
   Serial.print(": ");
   Serial.println(midiValue);


   lastStateCLK = currentStateCLK;
 }
}



void sendMIDIControlChange(byte control, byte value) {
 midiEventPacket_t event = {0x0B, 0xB0 | MIDI_CHANNEL, control, value};
 MidiUSB.sendMIDI(event);
}

void noteOn(byte channel, byte pitch, byte velocity)
{
midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
MidiUSB.sendMIDI(noteOff);
}
