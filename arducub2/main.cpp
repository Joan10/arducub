#include "lcd/tft.h"
#include <Arduino.h>
#include "basic3d.h"



#define V_CUB {{0,0,0},{20,0,0},{20,20,0},{0,20,0},{0,0,40},{20,0,40},{20,20,40},{0,20,40}}
t_vertex v_cub[8] = V_CUB;
t_aresta a_cub[12] = {   
			{0,1} ,
			{1,2} , 
			{2,3} ,
			{3,0} ,
			
			{4,5} ,
			{5,6} , 
			{6,7} ,
			{7,4} ,

			{0,4} ,
			{1,5} , 
			{2,6} ,
			{3,7}
		    };

int i,j;	int x, y, z;
Objecte3d cub1; char byte_entrada;
void setup(){

	x = 50; y=50; z = 0;
 	Serial.begin(9600);//	while (!Serial);
	Inicialitza_LCD();
	EmplenaPantalla(0x0000);
	/*PintaPixel(20,20, 0xFFFF);


	PintaLinia(10, 200, 20, 200, 0xFFFF);
	PintaLinia(20, 200, 1, 10, 0xFFFF);

	Escriu("Hola", 20, 20, 1, 0xFFFF);

	PintaRectangle(100, 103, 68, 71, 0xFFFF);*/
	cub1.Objecte3d::Crea(v_cub, a_cub, sizeof(v_cub)/sizeof(t_vertex), sizeof(a_cub)/sizeof(t_aresta));
	cub1.Objecte3d::Mou(x,y,z);
}
void loop(){

		if (Serial.available() > 0){

			byte_entrada = Serial.read();
			if (byte_entrada == 'r'){
				cub1.Objecte3d::Pinta(0x0000);
				cub1.Objecte3d::Rota(i,0,0);
				cub1.Objecte3d::Pinta(0xFFFF);
				//delay(50);
				i=(i+5) % 360;
			}else if (byte_entrada == 'd'){
				x++;
				cub1.Objecte3d::Pinta(0x0000);
				cub1.Objecte3d::Mou(x,y,z);
				cub1.Objecte3d::Pinta(0xFFFF);

			}

			else if (byte_entrada == 'a'){
				x--;
				cub1.Objecte3d::Pinta(0x0000);
				cub1.Objecte3d::Mou(x,y,z);
				cub1.Objecte3d::Pinta(0xFFFF);

			}else if (byte_entrada == 'w'){
				y++;
				cub1.Objecte3d::Pinta(0x0000);
				cub1.Objecte3d::Mou(x,y,z);
				cub1.Objecte3d::Pinta(0xFFFF);

			}else if (byte_entrada == 's'){
				y--;
				cub1.Objecte3d::Pinta(0x0000);
				cub1.Objecte3d::Mou(x,y,z);
				cub1.Objecte3d::Pinta(0xFFFF);

			}
		}
}
