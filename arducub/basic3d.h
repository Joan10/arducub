
#define MAX_POLYGONS 2000
#define MAX_VERTICES 2000

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


t_poligon poligon[MAX_POLYGONS]; //array de polígons
t_vertex vertex[MAX_VERTICES];	// array de vèrtexs
