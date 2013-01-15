

#ifndef __basic3d__

#include <Arduino.h>
#include "lcd/nokia.h"

#define MAX_POLYGONS 20
#define MAX_VERTICES 20

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

#endif
