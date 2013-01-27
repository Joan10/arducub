#include "tft.h"
#include "glcdfont.c"

volatile uint8_t *csPort    , *cdPort    , *wrPort    , *rdPort;
uint8_t           csPinSet  ,  cdPinSet  ,  wrPinSet  ,  rdPinSet  ,
                    csPinUnset,  cdPinUnset,  wrPinUnset,  rdPinUnset,
                   _reset;

//Valors d'inicialització de l'LCD.
static const uint16_t ILI932x_regValues[] PROGMEM = {
  ILI932X_START_OSC        , 0x0001, // Start oscillator
  TFTLCD_DELAY             , 50,     // 50 millisecond delay
  ILI932X_DRIV_OUT_CTRL    , 0x0100,
  ILI932X_DRIV_WAV_CTRL    , 0x0700,
  ILI932X_ENTRY_MOD        , 0x1030,
  ILI932X_RESIZE_CTRL      , 0x0000,
  ILI932X_DISP_CTRL2       , 0x0202,
  ILI932X_DISP_CTRL3       , 0x0000,
  ILI932X_DISP_CTRL4       , 0x0000,
  ILI932X_RGB_DISP_IF_CTRL1, 0x0,
  ILI932X_FRM_MARKER_POS   , 0x0,
  ILI932X_RGB_DISP_IF_CTRL2, 0x0,
  ILI932X_POW_CTRL1        , 0x0000,
  ILI932X_POW_CTRL2        , 0x0007,
  ILI932X_POW_CTRL3        , 0x0000,
  ILI932X_POW_CTRL4        , 0x0000,
  TFTLCD_DELAY             , 200,
  ILI932X_POW_CTRL1        , 0x1690,
  ILI932X_POW_CTRL2        , 0x0227,
  TFTLCD_DELAY             , 50,
  ILI932X_POW_CTRL3        , 0x001A,
  TFTLCD_DELAY             , 50,
  ILI932X_POW_CTRL4        , 0x1800,
  ILI932X_POW_CTRL7        , 0x002A,
  TFTLCD_DELAY             , 50,
  ILI932X_GAMMA_CTRL1      , 0x0000,
  ILI932X_GAMMA_CTRL2      , 0x0000,
  ILI932X_GAMMA_CTRL3      , 0x0000,
  ILI932X_GAMMA_CTRL4      , 0x0206,
  ILI932X_GAMMA_CTRL5      , 0x0808,
  ILI932X_GAMMA_CTRL6      , 0x0007,
  ILI932X_GAMMA_CTRL7      , 0x0201,
  ILI932X_GAMMA_CTRL8      , 0x0000,
  ILI932X_GAMMA_CTRL9      , 0x0000,
  ILI932X_GAMMA_CTRL10     , 0x0000,
  ILI932X_GRAM_HOR_AD      , 0x0000,
  ILI932X_GRAM_VER_AD      , 0x0000,
  ILI932X_HOR_START_AD     , 0x0000,
  ILI932X_HOR_END_AD       , 0x00EF,
  ILI932X_VER_START_AD     , 0X0000,
  ILI932X_VER_END_AD       , 0x013F,
  ILI932X_GATE_SCAN_CTRL1  , 0xA700, // Driver Output Control (R60h)
  ILI932X_GATE_SCAN_CTRL2  , 0x0003, // Driver Output Control (R61h)
  ILI932X_GATE_SCAN_CTRL3  , 0x0000, // Driver Output Control (R62h)
  ILI932X_PANEL_IF_CTRL1   , 0X0010, // Panel Interface Control 1 (R90h)
  ILI932X_PANEL_IF_CTRL2   , 0X0000,
  ILI932X_PANEL_IF_CTRL3   , 0X0003,
  ILI932X_PANEL_IF_CTRL4   , 0X1100,
  ILI932X_PANEL_IF_CTRL5   , 0X0000,
  ILI932X_PANEL_IF_CTRL6   , 0X0000,
  ILI932X_DISP_CTRL1       , 0x0133, // Main screen turn on
};

void Envia8(uint8_t d){
	uint8_t dr1 = (d) >> 1, dl1 = (d) << 1; 
	PORTE = (PORTE & B10111111) | (dr1 & B01000000); 
	PORTD = (PORTD & B01101100) | (dl1 & B10000000) | (((d) & B00001000)>>3) | (dr1 & B00000010) |  ((d) & B00010000); 
	PORTC = (PORTC & B10111111) | (dl1 & B01000000); 
	PORTB = (PORTB & B11001111) |(((d) & B00000011)<<4);
	WR_STROBE; 

}
void EscriuRegistre(uint16_t instr, uint16_t val){
	uint8_t hi, lo;
	hi = (instr) >> 8; lo = (instr); CD_COMMAND; Envia8(hi); Envia8(lo); 
	hi = (val) >> 8; lo = (val); CD_DATA   ; Envia8(hi); Envia8(lo); 
}

void ConfAdrecaFinestra(int x1, int y1, int x2, int y2) {
	int x,y;
	CS_ACTIVE;
	x  = x1;
	y  = y1;
	EscriuRegistre(0x0050, x1); // Set address window
	EscriuRegistre(0x0051, x2);
	EscriuRegistre(0x0052, y1);
	EscriuRegistre(0x0053, y2);
	EscriuRegistre(0x0020, x ); // Set address counter to top left
	EscriuRegistre(0x0021, y );
	CS_IDLE;
}

void Inicialitza_LCD(){


	uint8_t i = 0;
	uint16_t a, d;

	/********************************************************
	* Preparam les variables que fan referència als ports.
	*********************************************************/
	_reset     = LCD_RESET;
	csPort     = portOutputRegister(digitalPinToPort(LCD_CS));
	cdPort     = portOutputRegister(digitalPinToPort(LCD_CD));
	wrPort     = portOutputRegister(digitalPinToPort(LCD_WR));
	rdPort     = portOutputRegister(digitalPinToPort(LCD_RD));
	csPinSet   = digitalPinToBitMask(LCD_CS);
	cdPinSet   = digitalPinToBitMask(LCD_CD);
	wrPinSet   = digitalPinToBitMask(LCD_WR);
	rdPinSet   = digitalPinToBitMask(LCD_RD);
	csPinUnset = ~csPinSet;
	cdPinUnset = ~cdPinSet;
	wrPinUnset = ~wrPinSet;
	rdPinUnset = ~rdPinSet;
	*csPort   |=  csPinSet; // Set all control bits to HIGH (idle)
	*cdPort   |=  cdPinSet; // Signals are ACTIVE LOW
	*wrPort   |=  wrPinSet;
	*rdPort   |=  rdPinSet;
	pinMode(LCD_CS, OUTPUT);    // Enable outputs
	pinMode(LCD_CD, OUTPUT);
	pinMode(LCD_WR, OUTPUT);
	pinMode(LCD_RD, OUTPUT);

	if(LCD_RESET) {
		digitalWrite(LCD_RESET, HIGH);
		pinMode(LCD_RESET, OUTPUT);
	}


	//Configuració ports sortida.
	DDRE |=  B01000000; DDRD |=  B10010011;
	DDRC |=  B01000000; DDRB |=  B00110000;

/*
	rotation  = 0;
	cursor_y  = cursor_x = 0;
	_width    = TFTWIDTH;
	_height   = TFTHEIGHT;
*/
	/*
		Valors inicialització
	*/

	Reseteja_LCD();
	CS_ACTIVE;
	while(i < sizeof(ILI932x_regValues) / sizeof(uint16_t)) {
		a = pgm_read_word(&ILI932x_regValues[i++]);
		d = pgm_read_word(&ILI932x_regValues[i++]);
		if(a == TFTLCD_DELAY) delay(d);
		else                  EscriuRegistre(a, d);
	}
	ConfAdrecaFinestra(0, 0, TFTWIDTH-1, TFTHEIGHT-1);
}
void Reseteja_LCD(){
	CS_IDLE;
	CD_DATA;
	WR_IDLE;
	RD_IDLE;
	if(_reset) {
		digitalWrite(_reset, LOW);
		delay(2);
		digitalWrite(_reset, HIGH);
	}
	CS_ACTIVE;
	CD_DATA;
	Envia8(0x00);
	for(uint8_t i=0; i<7; i++) WR_STROBE;
	CS_IDLE;
	delay(100);
}



void Emplena(uint16_t color, uint32_t len) {

	uint16_t blocks;
	uint8_t  i, hi = color >> 8,
		  lo = color;

	CS_ACTIVE;
	CD_COMMAND;
	Envia8(0x00); // High byte of GRAM register...
	Envia8(0x22); // Write data to GRAM

	// Write first pixel normally, decrement counter by 1
	CD_DATA;
	Envia8(hi);
	Envia8(lo);
	len--;

	blocks = (uint16_t)(len / 64); // 64 pixels/block
	if(hi == lo) {
		// High and low bytes are identical.  Leave prior data
		// on the port(s) and just toggle the write strobe.
		while(blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2 bytes/pixel
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // x 4 pixels
			} while(--i);
		}
		// Fill any remaining pixels (1 to 64)
		for(i = (uint8_t)len & 63; i--; ) {
			WR_STROBE;
			WR_STROBE;
		}
	} else {
		while(blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				Envia8(hi); Envia8(lo); Envia8(hi); Envia8(lo);
				Envia8(hi); Envia8(lo); Envia8(hi); Envia8(lo);
			} while(--i);
		}
		for(i = (uint8_t)len & 63; i--; ) {
			Envia8(hi);
			Envia8(lo);
		}
	}
	CS_IDLE;
}

void Posicio(int x, int y){
	EscriuRegistre(0x0020, x);
	EscriuRegistre(0x0021, y);
}

void EmplenaPantalla(uint16_t color){
	
	CS_ACTIVE;
	Posicio(0,0);
	Emplena(color, (long)TFTWIDTH * (long)TFTHEIGHT);
	CS_IDLE;
}

char PintaPixel(int x, int y, int color){

	if (x<0 || x>(TFTWIDTH-1) || y<0 || y>(TFTHEIGHT-1)) return -1; //Si no podem pintar simplement retornam, {
	CS_ACTIVE;
	Posicio(x,y);
	EscriuRegistre(0x0022, color);
	CS_IDLE;
	return 1;

}

void PintaLinia(int x1, int y1, int x2, int y2, int color){

	int x0 = x1;
	int y0 = y1;

	int dx = fabs(x2-x0);
	int dy = fabs(y2-y0);
	int sx,sy,err,e2; char surt = 0;

	if (x0 < x2) sx = 1; else sx = -1;
	if (y0 < y2) sy = 1; else sy = -1;
	err = dx-dy;
	while (!surt) {
		PintaPixel(x0,y0,color);
		if (x0==x2 && y0==y2) surt = 1;
		e2 = 2*err;
		if (e2 > ((-1)*dy)){err = err - dy; x0 = x0 + sx;}
		if (e2 < dx){err = err + dx; y0 = y0 + sy;}	
	}
}
	
void PintaRectangle(int x1, int y1, int x2, int y2, int color){

	int xmin, ymin, xmax, ymax;
	if (x1 < x2){ xmax = x2; xmin = x1; }else {xmax = x1; xmin = x2;}
	if (y1 < y2){ ymax = y2; ymin = y1; }else {ymax = y1; ymin = y2;}

	ConfAdrecaFinestra(xmin, ymin, xmax, ymax);
	Emplena(color, (uint32_t)(ymax-ymin + 1)*(uint32_t)(xmax-xmin + 1) );
	ConfAdrecaFinestra(0, 0, TFTWIDTH-1, TFTHEIGHT-1);


}

void EscriuCaracter(char c, int x, int y, int mida, int color){
	
	int8_t i,j;
	uint8_t line;

	for (i=0; i<6; i++ ) {
		
		if (i == 5) 
			line = 0x0;
		else 
			line = pgm_read_byte(font+(c*5)+i);
		for (j=0; j<8; j++) {
			if (line & 0x1) {
				if (mida == 1) // default size
					PintaPixel(x+i, y+j, color);
		  		else {  // big size
		    			PintaRectangle(x+(i*mida), y+(j*mida), x+(i*mida) + mida -1 , y+(j*mida) + mida - 1 ,color);
		  			} 
			}
			line >>= 1;
		}
	}

}

void Escriu(char *text, int x, int y, int mida, int color){

	char c;
	int i = 0;
	c = text[i];
	while (c!='\0'){
		EscriuCaracter(c, x+i*mida*6, y, mida, color);
		i++;
		c = text[i];
	}

}
