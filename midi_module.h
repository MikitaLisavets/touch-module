#include "MIDIUSB.h"

const byte START_NOTE = 36;
const byte CHANNEL = 0;
const byte VELOCITY = 127;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void moduleInit() {}

void onPress(int index) {
  noteOn(CHANNEL, (byte)index + START_NOTE, VELOCITY);
}

void onRelease(int index) {
  noteOff(CHANNEL, (byte)index + START_NOTE, VELOCITY);
}

void loopCallback() {
  MidiUSB.flush();
}
