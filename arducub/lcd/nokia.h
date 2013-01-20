
#ifndef __LCD3310__
#define __LCD3310__
#include <Arduino.h>
#include "/opt/arduino-1.0.2/libraries/EEPROM/EEPROM.h"	
#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48
#define LCD_FILES LCD_Y/8




void LcdWrite(byte dc, byte data);
void LcdCharacter(char character);
void LcdClear(void);
void LcdInitialise(void);
void LcdString(char *characters);
void Lcdpixelxy(unsigned char x, unsigned char y);
char LcdPintaPixel(char x, char y, char esb);
char LcdPintaLinia(int x1, int y1, int x2, int y2, char esb);

#endif
