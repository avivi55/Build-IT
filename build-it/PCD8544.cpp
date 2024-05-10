#include "PCD8544.h"
#define GET_BIT(p, n) ((((unsigned char *)p)[n/8] >> (n%8)) & 0x01)
PCD8544::PCD8544(uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t reset, uint8_t sce):
  pin_sclk(sclk),
  pin_sdin(sdin),
  pin_dc(dc),
  pin_reset(reset),
  pin_sce(sce)
{
  pixelsBuffer = (uint8_t*)calloc((WIDTH * HEIGHT)/8, 1);
  cursorX = 0;
  cursorY = 0;
}

PCD8544::~PCD8544()
{
  free(pixelsBuffer);
}

void PCD8544::init()
{
  pinMode(pin_sclk, OUTPUT);
  pinMode(pin_sdin, OUTPUT);
  pinMode(pin_dc, OUTPUT);
  pinMode(pin_reset, OUTPUT);
  pinMode(pin_sce, OUTPUT);

  digitalWrite(pin_reset, HIGH);
  digitalWrite(pin_sce, HIGH);

  digitalWrite(pin_reset, LOW);
  delay(100);
  digitalWrite(pin_reset, HIGH);

  sendCommand(CMD_FCT_SET | FCT_EXTENDED_INSTRUCTIONS);
  sendCommand(CMD_SET_BIAS | 0b011); // 1 : 48

  // We want Vlcd to be 6V or 7V
  // Vlcd = a + Vop * b, as per the PCD8544 a=3.06 and b=0.06
  // => 6V = 3.06 + Vop * 0.06
  // => Vop = (6 - 3.06)/0.06 = 49
  sendCommand(CMD_SET_VOP | 49);

  sendCommand(CMD_FCT_SET | 0); // disabling the extention set
  sendCommand(CMD_DISPLAY | DISPLAY_ALL_SEGMENTS_ON);
  sendCommand(CMD_NOP);
  sendCommand(CMD_DISPLAY | DISPLAY_NORMAL);
  
  // set cursor at 0, 0
  sendCommand(CMD_SET_X | 0);
  sendCommand(CMD_SET_Y | 0);

  zeroRAM();

  sendCommand(CMD_SET_X | 0);
  sendCommand(CMD_SET_Y | 0);
}

void PCD8544::sendCommand(uint8_t cmd)
{
  digitalWrite(pin_dc, LOW);

  digitalWrite(pin_sce, LOW);
  shiftOut(pin_sdin, pin_sclk, MSBFIRST, cmd);
  digitalWrite(pin_sce, HIGH);
}

void PCD8544::sendData(uint8_t data)
{
  digitalWrite(pin_dc, HIGH);

  digitalWrite(pin_sce, LOW);
  shiftOut(pin_sdin, pin_sclk, MSBFIRST, data);
  digitalWrite(pin_sce, HIGH);
}

void PCD8544::setPower(bool on)
{
  if (on) {
    sendCommand(CMD_FCT_SET | 0); // on
    return;
  }

  sendCommand(CMD_FCT_SET | FCT_POWER_DOWN);
}


void PCD8544::zeroRAM()
{
  for (uint8_t j=0; j<=5; j++) {
    sendCommand(CMD_SET_Y | j);
    for (uint8_t i = 0; i < WIDTH; i++) {
      sendData(0x00);
    }
  }
  setCursor(0, 0);
}

void PCD8544::clearLine();
void PCD8544::clearColumn();

void PCD8544::drawPixel(uint8_t x, uint8_t y)
{
  setCursor(x, (uint8_t)(y/8));
  sendData(1 << (y%8));
}

void PCD8544::drawFromBuffer()
{
  for (int y = 0; y < (HEIGHT * WIDTH) / 8; ++y) {
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(pixelsBuffer[y] & (1<<i));
    }
    Serial.println();
  }
}

void PCD8544::drawVerticalLine(uint8_t x, uint8_t y0, uint8_t y1);
void PCD8544::drawHorizontalLine(uint8_t y, uint8_t x0, uint8_t x1);

void PCD8544::drawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void PCD8544::drawFilledRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void PCD8544::drawBitmap(const uint8_t *map, uint8_t nColumns, uint8_t nLines);

void PCD8544::setCursor(uint8_t x, uint8_t y)
{
  cursorX = x % 84;
  cursorY = y % 6;
  sendCommand(CMD_FCT_SET | 0);
  sendCommand(CMD_SET_X | cursorX);
  sendCommand(CMD_SET_Y | cursorY);
}
// size_t PCD8544::write(uint8_t chr);