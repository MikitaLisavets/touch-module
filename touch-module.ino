#include "Wire.h"
#include "Adafruit_MPR121.h"
#include "keys_module.h"
//#include "MIDIUSB.h"


#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 capLeft = Adafruit_MPR121();
Adafruit_MPR121 capRight = Adafruit_MPR121();

const int START_NOTE = 36;
const int SHIFT = 12;
const int BRIGHTNESS = 50;

const int R = 4;
const int LED_POWER = 5;
const int G = 6;
const int B = 7;

uint16_t currtouchedLeft = 0;
uint16_t currtouchedRight = 0;
uint16_t lasttouchedLeft = 0;
uint16_t lasttouchedRight = 0;

void setup() {
  moduleInit();

  pinMode(LED_POWER, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  lightOn(255, 255, 0);

  if (!capLeft.begin(0x5A)) { while (1); }
  if (!capRight.begin(0x5C)) { while (1); }

  lightOff();
}

void loop() {
  checkTouchLeft();
  checkTouchRight();
}

//void noteOn(byte channel, byte pitch, byte velocity) {
//  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
//  MidiUSB.sendMIDI(noteOn);
//}
//
//void noteOff(byte channel, byte pitch, byte velocity) {
//  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
//  MidiUSB.sendMIDI(noteOff);
//}

void doAction(bool isLeft, uint16_t currtouched, uint16_t lasttouched) {
  int index;
  for (uint8_t i=0; i<12; i++) {
    index = isLeft ? i + SHIFT : i;
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
//      noteOn(0, index + START_NOTE, 127);


      onPress(index);
      lightOn(index < 8 ? HIGH : LOW, index >= 8 && index < 16 ? HIGH : LOW, index >= 16 ? HIGH : LOW);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//      noteOff(0, index + START_NOTE, 127);
      onRelease(index);
      lightOff();
    }
//    MidiUSB.flush();
  }
}

void checkTouchLeft() {
  currtouchedLeft = capLeft.touched();
  doAction(true, currtouchedLeft, lasttouchedLeft);
  lasttouchedLeft = currtouchedLeft;
}

void checkTouchRight() {
  currtouchedRight = capRight.touched();
  doAction(false, currtouchedRight, lasttouchedRight);
  lasttouchedRight = currtouchedRight;
}

void lightOn(bool rValue, bool gValue, bool bValue) {
  digitalWrite(R, !rValue);
  digitalWrite(G, !gValue);
  digitalWrite(B, !bValue);
  analogWrite(LED_POWER, BRIGHTNESS);
}

void lightOff() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(LED_POWER, LOW);
}
