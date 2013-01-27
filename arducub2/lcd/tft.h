#include <Arduino.h> 
#ifndef __TFT__
#define __TFT__

#include "seq.h"
#include <math.h>
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define TFTWIDTH   240
#define TFTHEIGHT  320

// When using the TFT breakout board, control pins are configurable.
// És més rapid per ports!

#define RD_ACTIVE  *rdPort &=  rdPinUnset
#define RD_IDLE    *rdPort |=  rdPinSet
#define WR_ACTIVE  *wrPort &=  wrPinUnset
#define WR_IDLE    *wrPort |=  wrPinSet
#define CD_COMMAND *cdPort &=  cdPinUnset
#define CD_DATA    *cdPort |=  cdPinSet
#define CS_ACTIVE  *csPort &=  csPinUnset
#define CS_IDLE    *csPort |=  csPinSet
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }

#define NEGRE   0x0000
#define BLAU   0x001F
#define VERMELL     0xF800
#define VERD   0x07E0
#define GROC  0xFFE0
#define BLANC   0xFFFF

void Inicialitza_LCD();
void Reseteja_LCD();
void EmplenaPantalla(uint16_t color);
char PintaPixel(int x, int y, int color);
void PintaLinia(int x1, int y1, int x2, int y2, int color);
//void Escriu(char *text, int x, int y, int color);
void EscriuCaracter(char c, int x, int y, int mida, int color);
void PintaRectangle(int x1, int y1, int x2, int y2, int color);
void Escriu(char *text, int x, int y, int mida, int color);
#endif
