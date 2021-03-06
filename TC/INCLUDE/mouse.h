#include <stdlib.h>

/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria para control del mouse desarrollada en C
21/02/2017*/

//Tama;o del mouse
#define WMouse 12
#define HMouse 16

//Colores del mouse
#define O 15
#define I 255

int** bufferMouse;
//buffer=(int**)malloc(WMouse * HMouse * sizeof(int *));

//Forma del mouse
static unsigned char mouse[WMouse * HMouse] =
{
  O,O,O,0,0,0,0,0,0,0,0,0,
  O,O,O,O,0,0,0,0,0,0,0,0,
  O,O,I,O,O,0,0,0,0,0,0,0,
  O,O,I,I,O,O,0,0,0,0,0,0,
  O,O,I,I,I,O,O,0,0,0,0,0,
  O,O,I,I,I,I,O,O,0,0,0,0,
  O,O,I,I,I,I,I,O,O,0,0,0,
  O,O,I,I,I,I,I,I,O,O,0,0,
  O,O,I,I,I,I,I,I,I,O,O,0,
  O,O,I,I,I,I,I,I,I,I,O,O,
  O,O,I,I,I,I,I,I,O,O,O,O,
  O,O,I,I,I,I,I,I,O,O,0,0,
  O,O,O,O,O,O,I,I,O,O,0,0,
  O,O,O,O,O,O,I,I,I,O,0,0,
  0,0,0,0,O,O,O,I,I,O,0,0,
  0,0,0,0,0,O,O,O,O,O,0,0
};

//Carga el driver del mouse
void get_mouse()
{
	asm{
		mov ax,0;
		int 0x33;
	}
}

//Esconde el puntero en modo VGA
void hide_mouse()
{
	asm{
		mov ax,2h;
		int 0x33;
	}
}

//Pone limites al movimiento del mouse
void mouse_limit(){
	asm{
		mov ax, 7;
		mov cx, 0;
		mov dx, 795;
		int 0x33;
		mov ax, 8;
		mov cx, 0;
		mov dx,600;
		int 0x33;

	}
}

//Toma la posicion y boton presionado del mouse
void GetMousePos( int *mbutton, int *mx, int *my )
{
	asm {
		MOV AX, 3h;
		INT 33h;
		MOV AX, BX;
		MOV BX, mbutton;
		MOV WORD PTR [BX], AX;
		MOV BX, mx;
		MOV WORD PTR [BX], CX;
		MOV BX, my;
		MOV WORD PTR [BX], DX;
	}
}

//Muestra el mouse en pantalla
void mouseShow(int x, int y) {
  int i,j;
  x=x+2;
  y=y+2;
  bufferMouse = malloc(sizeof(int) * WMouse);
  for (i= 0; i < WMouse; i++) {
    bufferMouse[i] = malloc(sizeof(int) * HMouse);
    for (j=0; j < HMouse; j++) {
      bufferMouse[i][j] = getpixel(x+i, y+j);
    }
  }

  for (i=0; i < HMouse; i++) {
    for (j=0; j < WMouse; j++) {
      if (mouse[WMouse*i+j]!=0){
        pixel(x + j, y + i, mouse[WMouse*i+j]);
      }
    }
  }
}

// Esconde el mouse de la pantalla
void mouseHide(int x, int y) {
  int i,j;
  x=x+2;
  y=y+2;
  for (i=0; i < WMouse; i++) {
    for (j=0; j < HMouse; j++) {
      pixel(x+i,y+j,bufferMouse[i][j]);
    }
    free(bufferMouse[i]);
  }
  free(bufferMouse);
}

//Si la posicion del mouse ha cambiado, se despinta de la posicion anterior y vuelve a pintarse en la nueva
void repaintMouse(int *x, int *y, int *clicked, int *xtemp, int *ytemp) {
  GetMousePos(clicked,x, y);
  if (*xtemp != *x || *ytemp != *y) {
    mouseHide(*xtemp, *ytemp);
    mouseShow(*x, *y);
    *xtemp = *x;
    *ytemp = *y;
  }
}
