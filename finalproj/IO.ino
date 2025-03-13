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
MidiUSB.flush(); 
last_state = state;
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
