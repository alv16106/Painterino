
//Tama;o del cursor
#define WMouse 12
#define HMouse 16

//Colores del cursor
#define O 15
#define I 255

static unsigned char cursor[WMouse * HMouse] =
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

void get_mouse()
{
	asm{
		mov ax,0;
		int 0x33;
	}
}

void show_mouse()
{
	asm{
		mov ax,1h;
		int 0x33;
	}
}

void hide_mouse()
{
	asm{
		mov ax,2h;
		int 0x33;
	}
}

void mouse_limit(){
	asm{
		mov ax, 7;
		mov cx, 0;
		mov dx, 600;
		int 0x33;
		mov ax, 8;
		mov cx, 0;
		mov dx,800;
		int 0x33;

	}
}

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
