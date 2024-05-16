/**
 * @file PCD8544.h
 * @author Jacques Soghomonyan
 * @brief A simple yet extensive interface for the PCD8544 48×84 pixels matrix LCD controller/driver, intended for Arduino.
 * @version 0.1
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024 Jacques Soghomonyan <jsoghomonyan164@gmail.com>
 *
 * Warnings:
 *      It has been made for a school project, for the Nokia 5110 screen.
 *      It uses the Arduino library, as the project uses an atmega328p.
 *
 * It isn't as fully fledge as the ADAFRUIT library.
 * But it offers a lightweight alternative.
 *
 * It is heavily based on Carlos Rodrigues's library. <3
 *
 * I tried to add some easy to use graphical primitives.
*/

#ifndef PCD8544_H_CUSTOM
#define PCD8544_H_CUSTOM

#include <Arduino.h>
#include <avr/pgmspace.h>

#define CMD_NOP 0b00000000

#define CMD_FCT_SET 0b00100000
#define FCT_POWER_DOWN 0b100
#define FCT_VERTICAL_ADDRESSING 0b010
#define FCT_EXTENDED_INSTRUCTIONS 0b001

#define CMD_DISPLAY 0b00001000
#define DISPLAY_BLANK 0b000
#define DISPLAY_NORMAL 0b100
#define DISPLAY_ALL_SEGMENTS_ON 0b001
#define DISPLAY_INVERSE 0b101

#define CMD_SET_X 0b10000000
#define CMD_SET_Y 0b01000000

// EXTENDED INTRUCTION SET
#define CMD_SET_VOP 0b10000000
#define CMD_SET_BIAS 0b00001000
#define CMD_SET_TEMP_CTRL 0b00000100


#define WIDTH 84
#define HEIGHT 48

#define BUF_W 11 // 84/8 + 1
#define BUF_H HEIGHT
#define BUF_SIZE 528 // 48*11

#define bitsToByte(b1, b2, b3, b4, b5, b6, b7, b8) \
(b8 << 7) | (b7 << 6) | (b6 << 5) | (b5 << 4) | (b4 << 3) | (b3 << 2) | (b2 << 1) | b1

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class PCD8544
{
public:
  PCD8544(uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t reset, uint8_t sce);
  ~PCD8544();

  void init();

  void sendCommand(uint8_t cmd);
  void sendData(uint8_t data);
  void setPower(bool on);
  // void setVop(uint8_t level);

  void clearScreen();
  void clearLine();
  void clearColumn();
  void zeroRAM();

  bool getPixel(uint8_t x, uint8_t y);
  void setPixel(uint8_t x, uint8_t y, bool data);

  void drawVerticalLine(uint8_t x, uint8_t y0, uint8_t y1);
  void drawHorizontalLine(uint8_t y, uint8_t x0, uint8_t x1);

  void drawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void drawFilledRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void drawBitmap(const uint8_t *map, uint8_t nColumns, uint8_t nLines);
  void drawFromBuffer();

  void setCursor(uint8_t x, uint8_t y);

private:
  uint8_t pin_sclk;
  uint8_t pin_sdin;
  uint8_t pin_dc;
  uint8_t pin_reset;
  uint8_t pin_sce;
  uint8_t *pixelsBuffer;
  uint8_t cursorX;
  uint8_t cursorY;
};

// const PROGMEM char charlist[55] = {
//   ' ', '!', '#', '%', '*', '+', ',', '.', ':', 
//   '/', '-', '\\', '|', '(', ')', '[', ']', '{', '}', 
//   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
//   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
//   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
//   'U', 'V', 'W', 'X', 'Y', 'Z'
// };

// 3*5 chars based on https://fontstruct.com/fontstructions/show/1371235/3x5-dot-matrix-1
// const PROGMEM unsigned char charset[][5] = {
//   {
//     0b000,
//     0b000,
//     0b000,
//     0b000,
//     0b000
//   }, // space
//   {
//     0b010,
//     0b010,
//     0b010,
//     0b000,
//     0b010
//   }, // !
//   {
//     0b101,
//     0b111,
//     0b101,
//     0b111,
//     0b101
//   }, // #
//   {
//     0b101,
//     0b001,
//     0b010,
//     0b100,
//     0b101
//   }, // %
//   {
//     0b010,
//     0b000,
//     0b000,
//     0b000,
//     0b000
//   }, // *
//   {
//     0b000,
//     0b010,
//     0b111,
//     0b010,
//     0b000
//   }, // +
//   {
//     0b000,
//     0b000,
//     0b000,
//     0b110,
//     0b010
//   }, // ,
//   {
//     0b000,
//     0b000,
//     0b000,
//     0b000,
//     0b010
//   }, // .
//   {
//     0b000,
//     0b010,
//     0b000,
//     0b010,
//     0b000
//   }, // :
//   {
//     0b001,
//     0b001,
//     0b010,
//     0b100,
//     0b100
//   }, // /
//   {
//     0b000,
//     0b000,
//     0b111,
//     0b000,
//     0b000
//   }, // -
//   {
//     0b100,
//     0b100,
//     0b010,
//     0b001,
//     0b001
//   }, // backslash
//   {
//     0b010,
//     0b010,
//     0b010,
//     0b010,
//     0b010
//   }, // |
//   {
//     0b011,
//     0b100,
//     0b100,
//     0b100,
//     0b011
//   }, // (
//   {
//     0b110,
//     0b001,
//     0b001,
//     0b001,
//     0b110
//   }, // )
//   {
//     0b011,
//     0b010,
//     0b010,
//     0b010,
//     0b011
//   }, // [
//   {
//     0b110,
//     0b010,
//     0b010,
//     0b010,
//     0b110
//   }, // ]
//   {
//     0b011,
//     0b010,
//     0b110,
//     0b010,
//     0b011
//   }, // {
//   {
//     0b110,
//     0b010,
//     0b011,
//     0b010,
//     0b110
//   }, // }
//   {
//     0b111,
//     0b101,
//     0b101,
//     0b101,
//     0b111
//   }, // 0
//   {
//     0b110,
//     0b010,
//     0b010,
//     0b010,
//     0b111
//   }, // 1
//   {
//     0b111,
//     0b001,
//     0b111,
//     0b100,
//     0b111
//   }, // 2
//   {
//     0b111,
//     0b001,
//     0b111,
//     0b001,
//     0b111
//   }, // 3
//   {
//     0b001,
//     0b011,
//     0b101,
//     0b111,
//     0b001
//   }, // 4
//   {
//     0b111,
//     0b100,
//     0b111,
//     0b001,
//     0b111
//   }, // 5
//   {
//     0b010,
//     0b100,
//     0b111,
//     0b101,
//     0b111
//   }, // 6
//   {
//     0b111,
//     0b001,
//     0b010,
//     0b100,
//     0b100
//   }, // 7
//   {
//     0b111,
//     0b101,
//     0b111,
//     0b101,
//     0b111
//   }, // 8
//   {
//     0b111,
//     0b101,
//     0b111,
//     0b001,
//     0b010
//   }, // 9
//   {
//     0b111,
//     0b101,
//     0b111,
//     0b101,
//     0b101
//   }, // A
//   {
//     0b110,
//     0b101,
//     0b110,
//     0b101,
//     0b110
//   }, // B
//   {
//     0b111,
//     0b100,
//     0b100,
//     0b100,
//     0b111
//   }, // C
//   {
//     0b110,
//     0b101,
//     0b101,
//     0b101,
//     0b110
//   }, // D
//   {
//     0b111,
//     0b100,
//     0b111,
//     0b100,
//     0b111
//   }, // E
//   {
//     0b111,
//     0b100,
//     0b111,
//     0b100,
//     0b100
//   }, // F
//   {
//     0b111,
//     0b100,
//     0b101,
//     0b101,
//     0b111
//   }, // G
//   {
//     0b101,
//     0b101,
//     0b111,
//     0b101,
//     0b101
//   }, // H
//   {
//     0b111,
//     0b010,
//     0b010,
//     0b010,
//     0b111
//   }, // I
//   {
//     0b001,
//     0b001,
//     0b001,
//     0b101,
//     0b111
//   }, // J
//   {
//     0b101,
//     0b101,
//     0b110,
//     0b101,
//     0b101
//   }, // K
//   {
//     0b100,
//     0b100,
//     0b100,
//     0b100,
//     0b111
//   }, // L
//   {
//     0b101,
//     0b111,
//     0b111,
//     0b101,
//     0b101
//   }, // M
//   {
//     0b111,
//     0b101,
//     0b101,
//     0b101,
//     0b101
//   }, // N
//   {
//     0b111,
//     0b101,
//     0b101,
//     0b101,
//     0b111
//   }, // O
//   {
//     0b111,
//     0b101,
//     0b111,
//     0b100,
//     0b100
//   }, // P
//   {
//     0b111,
//     0b101,
//     0b111,
//     0b001,
//     0b001
//   }, // Q
//   {
//     0b111,
//     0b101,
//     0b110,
//     0b101,
//     0b101
//   }, // R
//   {
//     0b011,
//     0b100,
//     0b010,
//     0b001,
//     0b110
//   }, // S
//   {
//     0b111,
//     0b010,
//     0b010,
//     0b010,
//     0b010
//   }, // T
//   {
//     0b101,
//     0b101,
//     0b101,
//     0b101,
//     0b111
//   }, // U
//   {
//     0b101,
//     0b101,
//     0b101,
//     0b110,
//     0b100
//   }, // V
//   {
//     0b101,
//     0b101,
//     0b111,
//     0b111,
//     0b101
//   }, // W
//   {
//     0b101,
//     0b101,
//     0b010,
//     0b101,
//     0b101
//   }, // X
//   {
//     0b101,
//     0b101,
//     0b111,
//     0b001,
//     0b111
//   }, // Y
//   {
//     0b111,
//     0b001,
//     0b010,
//     0b100,
//     0b111
//   }, // Z
// };

#endif