#include "setup.h"

static PCD8544 display = PCD8544(SCREEN_CLK, SCREEN_DATA, SCREEN_DC, SCREEN_RST, SCREEN_CLK_ENABLE);

//#include "U8glib.h"
//
//U8GLIB_PCD8544 u8g = U8GLIB_PCD8544(SCREEN_CLK, SCREEN_DATA, SCREEN_CLK_ENABLE, SCREEN_DC, SCREEN_RST);

void setup() {
  Serial.begin(9600);
  // pinMode(LED_RED, OUTPUT);
  // pinMode(LED_GREEN, OUTPUT);
  // pinMode(BUTTON_UP, INPUT_PULLUP);
  // pinMode(BUTTON_DOWN, INPUT_PULLUP);
  // pinMode(BUTTON_LEFT, INPUT_PULLUP);
  // pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  // pinMode(BUTTON_AUX, INPUT_PULLUP);

  display.init();

  // display.clearScreen();

//  display.drawPixel(0, 3);
//  display.drawPixel(0, 2);
//  display.drawPixel(0, 1);

  display.drawFromBuffer();
}

void loop() {

}

//void draw(void) {
//  u8g.drawBitmapP(0, 0, 6, 48, logo);
//}
//
//void setup(void) {
//  u8g.firstPage();
//  do {
//    draw();
//  } while( u8g.nextPage());
//}
//
//void loop(void) {
///*  u8g.firstPage();
//  do {
//    draw();
//  } while( u8g.nextPage());*/
//
//  // rebuild the picture after some delay
//  delay(100);
//}
