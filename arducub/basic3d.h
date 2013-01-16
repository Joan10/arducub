

#ifndef __basic3d__
#define __basic3d__

#include <Arduino.h>
#include "lcd/nokia.h"

//#define MAX_POLYGONS 20
#define MAX_VERTICES 20
/*
typedef struct {
    float x,y,z;
} t_vertex;

typedef struct {
    int a,b,c;
} t_poligon; //Els polígons són 3 enters que apunten a un element del vector de vèrtexs

typedef struct {
    t_vertex vertex[MAX_VERTICES];
    t_poligon polygon[MAX_POLYGONS];
} t_obj,*t_obj_ptr;
*/



typedef struct {
    int x,y,z;
} t_vertex;

typedef struct {
    t_vertex *t1, *t2; //punters a dos vèrtexs
} t_aresta;

class Objecte3d {

	public:

		void Crea(t_vertex *l_vertexs, t_aresta *l_aresta, int v, int a); //llista de vèrtexs i número de vèrtexs
		void Pinta();
		//void Mou(int dx, int dy, int a); //dx,dy vectors directors. a magnitud
	private:
		t_vertex *cjt_vertex;//cjt_vertex[MAX_VERTICES];
		t_aresta *cjt_aresta;//cjt_vertex[MAX_VERTICES];
		int nv,na; //Número de vèrtexs, n arestes
};	
#endif
