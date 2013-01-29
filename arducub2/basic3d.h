

#ifndef __basic3d__
#define __basic3d__

#include <Arduino.h>
#include "lcd/tft.h"
#include <math.h>

//#define MAX_POLYGONS 20
#define MAX_VERTICES 20
#define MAX_ARESTA 20

typedef struct {
    int x,y,z;
} t_vertex, t_vector;

typedef struct {
    char t1, t2; //punters a dos vèrtexs del vector cjt_vertex
} t_aresta;

class Objecte3d {

	public:

		void Crea(t_vertex *l_vertexs, t_aresta *l_aresta, int v, int a); //llista de vèrtexs i número de vèrtexs
		void Pinta(int color);
		void Mou(int x, int y, int z); //dx,dy vectors directors. a magnitud
		void Rota(int ax, int ay, int az);
		void treuPosicio(int *x, int *y, int *z);
		void CanviaMida(int s); //s > 0 mes gran, s<0 mes petit
	private:
		t_vertex cjt_vertex[MAX_VERTICES];
		t_aresta cjt_aresta[MAX_ARESTA];
		t_vertex cjt_vertex_o[MAX_VERTICES]; //cjt de vèrtexs originals sense rotar, per evitar acumular molt d'error.
		int nv,na; //Número de vèrtexs, n arestes
		t_vertex c; //centre de l'objecte

};	
#endif
