#include "Keyboard.h"

const int PIN_COUNT = 24;
const int VALUES[PIN_COUNT] = {
  'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j', 'k', 'o', 'l', 'p', ';', 'z', 'x', ' ', KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW
};


void moduleInit() {
  Keyboard.begin();
}

void onPress(int index) {
  Keyboard.press(VALUES[index]);
}

void onRelease(int index) {
  Keyboard.release(VALUES[index]);
}
