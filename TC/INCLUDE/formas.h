#include <stdlib.h>

/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria grafica de figuras geometricas desarrollada en C
21/02/2017*/

#define Q 12
#define I 255
#define Z 3
#define Wpat 12
#define Hpat 16

int an,la,rx,ry,i;
static unsigned char p[Wpat*Hpat];
static unsigned char pat[Wpat * Hpat] =
{
  Q,Q,Q,Z,Z,Z,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,Z,Z,
  Q,Q,I,Q,Q,Z,Z,Z,Z,Z,Z,Z,
  Q,Q,I,I,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,I,I,I,Q,Q,Z,Z,Z,Z,Z,
  Q,Q,I,I,I,I,Q,Q,Z,Z,Z,Z,
  Q,Q,I,I,I,I,I,Q,Q,Z,Z,Z,
  Q,Q,I,I,I,I,I,I,Q,Q,Z,Z,
  Q,Q,I,I,I,I,I,I,I,Q,Q,Z,
  Q,Q,I,I,I,I,I,I,I,I,Q,Q,
  Q,Q,I,I,I,I,I,I,Q,Q,Q,Q,
  Q,Q,I,I,I,I,I,I,Q,Q,Z,Z,
  Q,Q,Q,Q,Q,Q,I,I,Q,Q,Z,Z,
  Q,Q,Q,Q,Q,Q,I,I,I,Q,Z,Z,
  Z,Z,Z,Z,Q,Q,Q,I,I,Q,Z,Z,
  Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Z,Z
};
static unsigned char pat2[Wpat * Hpat] =
{
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Q,Q,Q,Q,Q,Q,Z,Z,Z,Z,Z,Z,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
  Z,Z,Z,Z,Z,Z,Q,Q,Q,Q,Q,Q,
};
static unsigned char pat3[Wpat * Hpat] =
{
  Q,Q,Q,Q,Q,Z,Z,Q,Q,Q,Q,Q,
  Q,Q,Q,Q,Z,Z,Z,Z,Q,Q,Q,Q,
  Q,Q,Q,Z,Z,Z,Z,Z,Z,Q,Q,Q,
  Q,Q,Z,Z,Z,Z,Z,Z,Z,Z,Q,Q,
  Q,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Q,
  Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,
  Q,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Q,
  Q,Q,Z,Z,Z,Z,Z,Z,Z,Z,Q,Q,
  Q,Q,Q,Z,Z,Z,Z,Z,Z,Q,Q,Q,
  Q,Q,Q,Q,Z,Z,Z,Z,Q,Q,Q,Q,
  Q,Q,Q,Q,Q,Z,Z,Q,Q,Q,Q,Q,
  Q,Q,Q,Q,Q,Q,Q,Q,Q,Q,Q,O,
  I,I,I,I,I,I,I,I,I,I,I,I,
  I,I,I,I,I,I,I,I,I,I,I,I,
  I,I,I,I,I,I,I,I,I,I,I,I,
  I,I,I,I,I,I,I,I,I,I,I,I
};
int *portapapeles;
int Hbuff=0, Wbuff=0;

struct Nodo{
  int x;
  int y;
  struct Nodo* next;
};

//Llena una figura
void floodFill(int x, int y, int oldclr, int newclr,int patron)
{
  int nx,ny;
  struct Nodo* first, *last, *tmp;
    if (patron==1){
      for (i = 0; i < 192; i++) {
        p[i]=pat[i];
      }
    }
    if (patron==2){
      for (i = 0; i < 192; i++) {
        p[i]=pat2[i];
      }
    }
    if (patron==3){
      for (i = 0; i < 192; i++) {
        p[i]=pat3[i];
      }
    }

    first = (struct Nodo*) malloc (sizeof (struct Nodo));
    if (first == NULL)
    {
	     quit();
	     fprintf (stderr, "e: NO queda memoria.\n");
	     exit (2);
    }
    if (oldclr == newclr)
    {
      free (first);
      return;
    }

    first->x = x;
    first->y = y;
    first->next = NULL;
    last = first;

    while (first != NULL)
    {
      nx=x%12;
      ny=y%16;
      if(patron!=0){
        pixel(x,y,p[ny*12+nx]);
      }else{
        pixel (x, y, newclr);
      }

      if (getpixel (x, y-1) == oldclr)
      {
        if (patron!=0) {
          nx=x%12;
          ny=(y-1)%16;
          pixel(x,y-1,p[ny*12+nx]);
        }else{
          pixel (x, y-1, newclr);
        }
        insert (x, y-1, &last);
      }


      if (getpixel (x, y+1) == oldclr)
      {
        if (patron!=0) {
          nx=x%12;
          ny=(y+1)%16;
          pixel(x,y+1,p[ny*12+nx]);
        }else{
          pixel (x, y+1, newclr);
        }
        insert (x, y+1, &last);
      }

      if (getpixel (x-1, y) == oldclr)
      {
        if (patron!=0) {
          nx=(x-1)%12;
          ny=y%16;
          pixel(x-1,y,p[ny*12+nx]);
        }else{
          pixel (x-1, y, newclr);
        }
        insert (x-1, y, &last);
      }

      if (getpixel (x+1, y) == oldclr)
      {
        if (patron!=0) {
          nx=(x+1)%12;
          ny=y%16;
          pixel(x+1,y,p[ny*12+nx]);
        }else{
          pixel (x+1, y, newclr);
        }
        insert (x+1, y, &last);
      }

      tmp = first;
      first = first->next;
      x = first->x;
      y = first->y;
      free (tmp);
    }
}

int insert (int x, int y, struct Nodo** last)
{
    struct Nodo* p;
    p = (struct Nodo*) malloc (sizeof (struct Nodo));
    if (p == NULL) //Si no se puede alocar memoria
    {
      quit();
	    fprintf (stderr, "\n No queda memoria en el stack.\n");
	    return 0;
    }

    p->x = x;
    p->y = y;
    p->next = NULL;
    (*last)->next = p;
    *last = (*last)->next;
    return 1;
}

//Funcion que dibuja una linea
void line (int x0, int y0, int x1, int y1, char color,int g)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;){  /* loop */
    putPixel (x0,y0,g,color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

//Funcion que dibuja un rectangulo
void rectangulo(int x0, int y0, int x1, int y1, char color,int g){
  line(x0,y0,x0,y1,color,g);
  line(x0,y1,x1,y1,color,g);
  line(x1,y1,x1,y0,color,g);
  line(x1,y0,x0,y0,color,g);
}

//Dibuja los 8 puntos del circulo
void octavo(int xc, int yc, int x, int y, char color,int g)
{
    putPixel(xc+x, yc+y, g, color);
    putPixel(xc-x, yc+y, g, color);
    putPixel(xc+x, yc-y, g, color);
    putPixel(xc-x, yc-y, g, color);
    putPixel(xc+y, yc+x, g, color);
    putPixel(xc-y, yc+x, g, color);
    putPixel(xc+y, yc-x, g, color);
    putPixel(xc-y, yc-x, g, color);
}

//Funcion que dibuja un circulo
void circulo(int xc, int yc, int r, char color,int g)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        octavo(xc, yc, x, y, color,g);
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        octavo(xc, yc, x, y, color,g);
    }
}

//Elipse
void Elipse(int xc, int yc, int rx, int ry, char color,int g) {
  int x,y;
  float p1,p2;
  x=0;
	y=ry;
	cuarto(xc,x,yc,y,color,g);
	p1=(ry*ry)-(rx*rx*ry)+(rx*rx)/4;
	while((2.0*ry*ry*x)<=(2.0*rx*rx*y))
	{
		x++;
		if(p1<=0)
			p1=p1+(2.0*ry*ry*x)+(ry*ry);
		else
		{
			y--;
			p1=p1+(2.0*ry*ry*x)-(2.0*rx*rx*y)+(ry*ry);
		}
		cuarto(xc,x,yc,y,color,g);
		x=-x;
		cuarto(xc,x,yc,y,color,g);
		x=-x;
	}
	x=rx;
	y=0;
	cuarto(xc,x,yc,y,color,g);
	p2=(rx*rx)+2.0*(ry*ry*rx)+(ry*ry)/4;
	while((2.0*ry*ry*x)>(2.0*rx*rx*y))
	{
		y++;
		if(p2>0)
			p2=p2+(rx*rx)-(2.0*rx*rx*y);
		else
		{
			x--;
			p2=p2+(2.0*ry*ry*x)-(2.0*rx*rx*y)+(rx*rx);
		}
		cuarto(xc,x,yc,y,color,g);
		y=-y;
		cuarto(xc,x,yc,y,color,g);
		y=-y;
	}
}

int cuarto(int xc, int x, int yc, int y, char color,int g) {
  putPixel(xc+x,yc+y,g,color);
  putPixel(xc-x,yc+y,g,color);
  putPixel(xc+x,yc-y,g,color);
  putPixel(xc-x,yc-y,g,color);
  return 0;
}

void sprayNpray(unsigned char color, int x, int y, int d,int borrador){
  if(d==1){
    an=9;
    la=4;
  }else if (d==2) {
    an=17;
    la=8;
  }else if (d==3) {
    an=25;
    la=12;
  }
    ry = rand() % an;
    rx = rand() % an;
    if (x<700||y<450) {
        pixel(x+rx-la,y+ry-la,color);
    }
    if (!borrador){
      delay(2);
    }

}


//Hace poligonos
int poligono(int xi,int yi,char color,int g){
  int term=1, xf, yf, bf,iniciox,inicioy,x2,y2;
  iniciox=xi;
  inicioy=yi;
  while (term==1){
    repaintMouse(&xf,&yf,&bf,&x2,&y2);
    if (bf==1){
      while(bf==1){
        repaintMouse(&xf,&yf,&bf,&x2,&y2);
      }
      //
      line(xf,yf,xi,yi,color,g);
      xi=xf;
      yi=yf;
    }else if(bf==2){
      line(xi,yi,iniciox,inicioy, color,g);
      term=0;
    }
  }
  mouseHide(xi,yi);
  return 0;
}

//Cambia dos registros de variable
int swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    return 0;
}

void copy(int cut,int xo, int yo, int xf, int yf){
  int i,j,x,y,dx,dy;
  if(xo>700)xo=700;
  if(xf>700)xf=700;
  if(yo>450)yo=450;
  if(yf>450)yf=450;

  x=xo;
  y=yo;
  if (xo>xf)x=xf;
  if (yo>yf)y=yf;
  dx=abs(xf-xo);
  dy=abs(yf-yo);
  Hbuff=dy;
  Wbuff=dx;
  portapapeles= (int *)malloc(sizeof(int)*abs(xf-xo)*abs(yf-yo));
  if(portapapeles == NULL) {
    printf("malloc of size %d failed!\n", sizeof(int)*abs(xf-xo)*abs(yf-yo));
    exit(1);
  }

  for (i = 0; i < dx; i++) {
    for (j = 0; j < dy; j++) {
      portapapeles[j+i*dy]=getpixel(x+i,y+j);
      if (cut) pixel(x+i,y+j,15);
    }
  }
}

void paste(int x, int y){
  int i,j;
  for (i = 0; i < Wbuff; i++) {
    for (j = 0; j < Hbuff; j++) {
      pixelFig(x+i,j+y,portapapeles[j+i*Hbuff]);
    }
  }
  free(portapapeles);
}

void floodFill2(int x, int y, int oldclr, int newclr,int patron)
{
  int nx,ny;
  struct Nodo* first, *last, *tmp;
    if (patron==1){
      for (i = 0; i < 192; i++) {
        p[i]=pat[i];
      }
    }
    if (patron==2){
      for (i = 0; i < 192; i++) {
        p[i]=pat2[i];
      }
    }
    if (patron==3){
      for (i = 0; i < 192; i++) {
        p[i]=pat3[i];
      }
    }

    first = (struct Nodo*) malloc (sizeof (struct Nodo));
    if (first == NULL)
    {
	     quit();
	     fprintf (stderr, "e: NO queda memoria.\n");
	     exit (2);
    }
    if (oldclr == newclr)
    {
      free (first);
      return;
    }

    first->x = x;
    first->y = y;
    first->next = NULL;
    last = first;

    while (first != NULL)
    {
      nx=x%12;
      ny=y%16;
      if(patron!=0){
        pixel(x,y,p[ny*12+nx]);
      }else{
        pixel (x, y, newclr);
      }

      if (getpixel (x, y-1) == oldclr)
      {
        if (patron!=0) {
          nx=x%12;
          ny=(y-1)%16;
          pixel(x,y-1,p[ny*12+nx]);
        }else{
          pixel (x, y-1, newclr);
        }
        insert (x, y-1, &last);
      }


      if (getpixel (x, y+1) == oldclr)
      {
        if (patron!=0) {
          nx=x%12;
          ny=(y+1)%16;
          pixel(x,y+1,p[ny*12+nx]);
        }else{
          pixel (x, y+1, newclr);
        }
        insert (x, y+1, &last);
      }

      if (getpixel (x-1, y) == oldclr)
      {
        if (patron!=0) {
          nx=(x-1)%12;
          ny=y%16;
          pixel(x-1,y,p[ny*12+nx]);
        }else{
          pixel (x-1, y, newclr);
        }
        insert (x-1, y, &last);
      }

      if (getpixel (x+1, y) == oldclr)
      {
        if (patron!=0) {
          nx=(x+1)%12;
          ny=y%16;
          pixel(x+1,y,p[ny*12+nx]);
        }else{
          pixel (x+1, y, newclr);
        }
        insert (x+1, y, &last);
      }

      tmp = first;
      first = first->next;
      x = first->x;
      y = first->y;
      free (tmp);
    }
}
