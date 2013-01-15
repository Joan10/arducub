#include "nokia.h"
#include <Arduino.h>

int main(){

	int i,j;

	LcdInitialise();
	LcdClear();
	LcdString("Hola");

	for (i=0; i<84;i++)
		for (j=0; j<48;j++)
			LcdPintaPixel(i,j);

}
