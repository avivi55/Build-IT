#include "setup.h"

static PCD8544 display = PCD8544(SCREEN_CLK, SCREEN_DATA, SCREEN_DC, SCREEN_RST, SCREEN_CLK_ENABLE);

void setup() {
  // pinMode(LED_RED, OUTPUT);
  // pinMode(LED_GREEN, OUTPUT);
  // pinMode(BUTTON_UP, INPUT_PULLUP);
  // pinMode(BUTTON_DOWN, INPUT_PULLUP);
  // pinMode(BUTTON_LEFT, INPUT_PULLUP);
  // pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  // pinMode(BUTTON_AUX, INPUT_PULLUP);

  display.init();

  display.drawRectangle(0,0, 10,10);
  display.drawRectangle(30,15, 60,40);

  display.drawFromBuffer();
}

void loop() {

}
