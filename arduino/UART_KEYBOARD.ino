// Application send by uart 8 - bit sequence after button push detection. How's sequence looks?
// First two bits are alway equals 10
// Next four bit are correct payload
// Last two bits are alway equals 01

// UART speed: 115200

// Current mapping:
// 10 00 01 01 - KEY_1
// 10 00 10 01 - KEY_2
// 10 00 11 01 - KEY_3
// 10 01 00 01 - KEY_4

#define BTN_NONE 0x81 // Empty sequence.
#define KEY_1 0x85 
#define KEY_2 0x89 
#define KEY_3 0x8D 
#define KEY_4 0x91 

void detect_key_change_event(uint8_t key);
void trigged_button_action(uint8_t key);
void releaseKey();

uint8_t pressed_key = BTN_NONE;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  Serial.println("UART Initialized.");
}

void loop() {
  int value = analogRead(A0);
  value = map(value, 0, 1023, 0, 255);

  uint8_t key;
  if (value >= 200 && value <= 210) {
    key = KEY_1;
  } else if (value >= 185 && value <= 195) {
    key = KEY_2;
  } else if (value >= 165 && value <= 175) {
    key = KEY_3;
  } else if (value >= 120 && value <= 130) {
    key = KEY_4;
  } else {
    key = BTN_NONE;
  }

  detect_key_change_event(key);
}

void detect_key_change_event(uint8_t key /*as second argument should be pointer to function*/) {
  if (key != pressed_key) {
    trigged_button_action(key);
    pressed_key = key;
  }
}

void trigged_button_action(uint8_t key) {
  if (key == BTN_NONE) {
    return;
  }
  

  Serial.print(key, BIN);
}
