#include <stdlib.h>

/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria grafica de figuras geometricas desarrollada en C
21/02/2017*/

int *portapapeles;
int Hbuff=0, Wbuff=0;

struct Nodo{
  int x;
  int y;
  struct Nodo* next;
};

//Llena una figura
void floodFill(int x, int y, int oldclr, int newclr)
{
    struct Nodo* first, *last, *tmp;

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
      pixel (x, y, newclr);

      if (getpixel (x, y-1) == oldclr)
      {
        pixel (x, y-1, newclr);
        insert (x, y-1, &last);
      }


      if (getpixel (x, y+1) == oldclr)
      {
        pixel (x, y+1, newclr);
        insert (x, y+1, &last);
      }

      if (getpixel (x-1, y) == oldclr)
      {
        pixel (x-1, y, newclr);
        insert (x-1, y, &last);
      }

      if (getpixel (x+1, y) == oldclr)
      {
        pixel (x+1, y, newclr);
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
void line (int x0, int y0, int x1, int y1, char color)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;){  /* loop */
    pixelFig (x0,y0,color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

//Funcion que dibuja un rectangulo
void rectangulo(int x0, int y0, int x1, int y1, char color){
  line(x0,y0,x0,y1,color);
  line(x0,y1,x1,y1,color);
  line(x1,y1,x1,y0,color);
  line(x1,y0,x0,y0,color);
}

//Dibuja los 8 puntos del circulo
void octavo(int xc, int yc, int x, int y, char color)
{
    pixelFig(xc+x, yc+y, color);
    pixelFig(xc-x, yc+y, color);
    pixelFig(xc+x, yc-y, color);
    pixelFig(xc-x, yc-y, color);
    pixelFig(xc+y, yc+x, color);
    pixelFig(xc-y, yc+x, color);
    pixelFig(xc+y, yc-x, color);
    pixelFig(xc-y, yc-x, color);
}

//Funcion que dibuja un circulo
void circulo(int xc, int yc, int r, char color)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        octavo(xc, yc, x, y, color);
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        octavo(xc, yc, x, y, color);
    }
}

//Elipse
void Elipse(int xc, int yc, int rx, int ry, char color) {
  int x,y;
  float p1,p2;
  x=0;
	y=ry;
	cuarto(xc,x,yc,y,color);
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
		cuarto(xc,x,yc,y,color);
		x=-x;
		cuarto(xc,x,yc,y,color);
		x=-x;
	}
	x=rx;
	y=0;
	cuarto(xc,x,yc,y,color);
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
		cuarto(xc,x,yc,y,color);
		y=-y;
		cuarto(xc,x,yc,y,color);
		y=-y;
	}
}

int cuarto(int xc, int x, int yc, int y, char color) {
  pixel(xc+x,yc+y,color);
  pixel(xc-x,yc+y,color);
  pixel(xc+x,yc-y,color);
  pixel(xc-x,yc-y,color);
  return 0;
}

void sprayNpray(unsigned char *color, int x, int y, int d){
    int ry = rand() % 17;
    int rx = rand() % 17;
    if (x<700||y<450) {
        pixel(x+rx-8,y+ry-8,*color);
    }
    delay(4-d);
}


//Hace poligonos
int poligono(int xi,int yi,char color){
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
      line(xf,yf,xi,yi,color);
      xi=xf;
      yi=yf;
    }else if(bf==2){
      line(xi,yi,iniciox,inicioy, color);
      term=0;
    }
  }
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

void copy(int xo, int yo, int xf, int yf){
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
