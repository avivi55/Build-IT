#ifndef Setup_h
#define Setup_h

#include <Arduino.h>
#include "LCD_Functions.h"
#include <avr/pgmspace.h>

#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48

#define LED_RED 2
#define LED_GREEN 8

#define BUTTON_UP 11
#define BUTTON_DOWN 9
#define BUTTON_LEFT 10
#define BUTTON_RIGHT 12

#define BUTTON_AUX 13

#define toucheHaut() (LOW == digitalRead(BUTTON_UP))
#define toucheBas() (LOW == digitalRead(BUTTON_DOWN))
#define toucheGauche() (LOW == digitalRead(BUTTON_LEFT))
#define toucheDroite() (LOW == digitalRead(BUTTON_RIGHT))
#define toucheAux() (LOW == digitalRead(BUTTON_AUX))

#define touche() (toucheHaut() || toucheBas() || toucheDroite() || toucheGauche() || toucheAux()) 


#define SCREEN_CLK 7
#define SCREEN_DATA 6
#define SCREEN_DC 5
#define SCREEN_CLK_ENABLE 4
#define SCREEN_RST 3



#endif