#include <Arduino.h>

#ifndef __LCD3310__

void LcdWrite(byte dc, byte data);
void LcdCharacter(char character);
void LcdClear(void);
void LcdInitialise(void);
void LcdString(char *characters);
void Lcdpixelxy(unsigned char x, unsigned char y);
void LcdPintaPixel(int x, int y);


#endif
