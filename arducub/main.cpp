#include "basic3d.h"
#include <Arduino.h>
#define V_CUB {{0,0,0},{20,0,0},{20,20,0},{0,20,20}}
#define V_CUB_GIRAT {{0,20,0},{20,0,0},{40,20,0},{20,40,20}}
#define V_ESTRELLA {{20,0,0},{10,20,0},{30,20,0},{0,10,20},{40,10,20}}

#define V_LINIA {{30,30,0},{10,30,0}}
/*
t_vertex v_cub[8] = { {0,0,0} ,
		     {20,0,0},
		     {0,20,0},
		     {0,0,20},
		     {20,20,0},
		     {0,20,20},
		     {20,0,20},
		     {20,20,20} };
*/

t_vertex v_cub[8] = V_CUB;


t_vertex v_estrella[5] = V_ESTRELLA;


t_vertex v_linia[2] = V_LINIA;
t_aresta a_linia[1] = { {0,1} };

t_aresta a_cub[4] = {   {0,1} ,
			{1,2} , 
			{2,3} ,
			{3,0}
		    };

t_aresta a_estrella[5] = {   {0,1} ,
			{0,2} , 
			{1,4} ,
			{3,2} ,
			{3,4}
		    };

int i,j;
char byte_entrada;
Objecte3d cub1,linia,cub2,estrella;
void setup(){
	
	
 	Serial.begin(9600);


	LcdInitialise();
	LcdClear();

	//cub1.Objecte3d::Crea(v_cub, a_cub, sizeof(v_cub)/sizeof(t_vertex), sizeof(a_cub)/sizeof(t_aresta));
	//cub1.Objecte3d::Pinta();

	//cub2.Objecte3d::Crea(v_cub_girat, a_cub, sizeof(v_cub)/sizeof(t_vertex), sizeof(a_cub)/sizeof(t_aresta));
	//cub2.Objecte3d::Pinta();
	estrella.Objecte3d::Crea(v_estrella, a_estrella, sizeof(v_estrella)/sizeof(t_vertex), sizeof(a_estrella)/sizeof(t_aresta));
	estrella.Objecte3d::Pinta(0);

//	linia.Objecte3d::Crea(v_linia, a_linia, 2, 1);
//	linia.Objecte3d::Pinta(0);


	estrella.Objecte3d::Pinta(1);
	estrella.Objecte3d::Mou(30,25,0);
	estrella.Objecte3d::Pinta(0);

	i=0;j=0;


}
void loop(){

	//	if (digitalRead(12) == 0){
		if (Serial.available() > 0){

			byte_entrada = Serial.read();
			if (byte_entrada == 'r'){
				estrella.Objecte3d::Pinta(1);
				estrella.Objecte3d::Rota(i,0,0);
				estrella.Objecte3d::Pinta(0);
				delay(50);
				i=(i+10) % 360;
			}else if (byte_entrada == 'd'){

				estrella.Objecte3d::Pinta(1);
				estrella.Objecte3d::Mou(30+j,25,0);
				estrella.Objecte3d::Pinta(0);
				delay(50); j++;

			}

			else if (byte_entrada == 'a'){

				estrella.Objecte3d::Pinta(1);
				estrella.Objecte3d::Mou(30+j,25,0);
				estrella.Objecte3d::Pinta(0);
				delay(50);j--;

			}
		}
		
}
