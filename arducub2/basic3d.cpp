#include "basic3d.h"
void Objecte3d::Crea(t_vertex *l_vertexs, t_aresta *l_aresta, int v, int a){
	int i	;
	nv = v; na = a;//número de vèrtexs
	c.x=0; c.y = 0; c.z= 0;
	for (i=0; i<v;i++){
		cjt_vertex[i].x = l_vertexs[i].x;
		cjt_vertex[i].y = l_vertexs[i].y;
		cjt_vertex[i].z = l_vertexs[i].z;
		cjt_vertex_o[i].x = l_vertexs[i].x;
		cjt_vertex_o[i].y = l_vertexs[i].y;
		cjt_vertex_o[i].z = l_vertexs[i].z;

		c.x = c.x + cjt_vertex[i].x;
		c.y = c.y + cjt_vertex[i].y;
		c.z = c.z + cjt_vertex[i].z;
	}
	c.x=c.x/v; //Calculem el centre de l'objecte. cx = sum vx / numvertex  
	c.y=c.y/v;
	c.z=c.z/v;
	for (i=0; i<a;i++){
		cjt_aresta[i].t1 = l_aresta[i].t1;
		cjt_aresta[i].t2 = l_aresta[i].t2;
	}

}
void Objecte3d::Pinta(int color){
	//Primer només pintarem en 2d...
	int i;
	int dx,dx2; //Dif. entre Punts projectats i reals.
	
	/*
		LcdPintaLinia(10,10,40,30);
		LcdPintaLinia(10,10,40,40);
		LcdPintaLinia(60,40,17,3);
*//*
	for (i=0; i<nv; i++){

		dx = sqrt(fabs(cjt_vertex[i].z)); if (cjt_vertex[i].z < 0) dx = -1*dx;//Si la z és negativa hem d'agafar l'arrel negativa.		
		PintaPixel(cjt_vertex[i].x + dx, cjt_vertex[i].y + dx,color);
		//LcdPintaLinia((cjt_aresta[i].t1)->x,(cjt_aresta[i].t1)->y,(cjt_aresta[i].t2)->x,(cjt_aresta[i].t2)->y);
	}
*/
	for (i=0; i<na; i++){

		dx = (int) sqrt(fabs(cjt_vertex[cjt_aresta[i].t1].z )); if (cjt_vertex[cjt_aresta[i].t1].z < 0) dx = -1*dx;
		dx2 = (int) sqrt(fabs(cjt_vertex[cjt_aresta[i].t2].z )); if (cjt_vertex[cjt_aresta[i].t2].z < 0) dx2 = -1*dx2;


		PintaLinia(cjt_vertex[cjt_aresta[i].t1].x + dx,cjt_vertex[cjt_aresta[i].t1].y +dx ,cjt_vertex[cjt_aresta[i].t2].x+dx2,cjt_vertex[cjt_aresta[i].t2].y + dx2, color);
		//LcdPintaLinia((cjt_aresta[i].t1)->x,(cjt_aresta[i].t1)->y,(cjt_aresta[i].t2)->x,(cjt_aresta[i].t2)->y);
	}
//	PintaPixel(c.x,c.y,color);
	

}

void Objecte3d::Mou(int x, int y, int z){

	t_vector d; // vector distància de la nova posició a la vella.
	int i;
	d.x = x - c.x; d.y =  y - c.y; d.z = z -  c.z; 
		
	for (i=0; i<nv; i++){
		cjt_vertex[i].x = cjt_vertex[i].x + d.x;
		cjt_vertex[i].y = cjt_vertex[i].y + d.y;
		cjt_vertex[i].z = cjt_vertex[i].z + d.z;
		cjt_vertex_o[i].x = cjt_vertex_o[i].x + d.x;
		cjt_vertex_o[i].y = cjt_vertex_o[i].y + d.y;
		cjt_vertex_o[i].z = cjt_vertex_o[i].z + d.z;
	}

	c.x = x; c.y = y; c.z = z;
	
}

void Objecte3d::Rota(int ax, int ay, int az){
//passem en graus i convertim a radians.
	t_vertex d; // vèrtexs a l'origen. Els rotarem des de l'origen i després els sumarem.
	int i;
	float vcos, vsin, vx, vy;

	vcos = cos((float)ax*M_PI/180);
	vsin = sin((float)ax*M_PI/180);


	for (i=0; i<nv; i++){

		d.x = cjt_vertex_o[i].x - c.x; d.y =  cjt_vertex_o[i].y - c.y; d.z = cjt_vertex_o[i].z -  c.z; 
		// Per evitar acumular error farem els càlculs sobre les coordenades originals sense rotar.

		vx = (float)d.x*vcos + d.y*vsin; vy = (float) d.x*-1*vsin + d.y*vcos;

		cjt_vertex[i].x = c.x + vx ;
		cjt_vertex[i].y = c.y + vy ;
		cjt_vertex[i].z = c.z + d.z;
	}

/*
proves		
		d.x = 10; d.y =  10; 
		vx = (float)d.x*(vcos + vsin); vy = (float) d.y*(-1*vsin + vcos);

		sprintf(a, "c:%i s:%i", (int)(1000*vcos), (int)(1000*vsin));
		//LcdString(a);
		
		Lcdpixelxy(0,0);
		sprintf(a, "%i %i %i %i    ", cjt_vertex[0].x, cjt_vertex[0].y,cjt_vertex[1].x, cjt_vertex[1].y);
		sprintf(a, "%i %i %i %i    ", d.x, d.y,(int)(vsin*1000), (int)(vcos*1000));		
		LcdString(a);
		PintaPixel( cjt_vertex[i-1].x,  cjt_vertex[i-1].y, 0);
*/	

}

void Objecte3d::treuPosicio(int *x, int *y, int *z){

	*x = c.x; *y = c.y; *z = c.z;

}
			
