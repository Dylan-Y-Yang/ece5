#include "MIDIUSB.h"

const int buttonCount = 25;
const int DATAPIN = 1;
const int CLOCKPIN = 2;
const int LATCHPIN = 3;

const byte channels[4] = {0, 1, 10, 11};
void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    Serial.begin(9600);
}

union button_t
{
    uint32_t all;
    uint8_t bytes[4];
};

int main(int argc, char *argv[])
{
    button_t state, last_state;

    while (1)
    {
        digitalWrite(LATCHPIN, LOW);
        digitalWrite(LATCHPIN, HIGH);
        for (size_t i = 0; i < 4; ++i)
        {
            state.bytes[i] = shiftIn(DATAPIN, CLOCKPIN, MSBFIRST);
        }

        uint32_t pressed = state.all & ~last_state.all;
        uint32_t released = ~state.all & last_state.all;

        for (size_t button = 0; button < 25; ++button)
        {
            if (pressed & (1 << button))
            {
                noteOn(channels[0], 60 + button, 100);
                Serial.println("hi gang" + button);
            }
        }

        last_state = state;
    }
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

void controlChange(byte channel, byte control, byte value)
{
    midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
}
