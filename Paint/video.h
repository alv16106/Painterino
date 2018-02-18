

void modoVideo()
{
	asm{
		mov ax,0x04f02; // svga.
		mov bx,0x0103; // 800x600 y 256 colores.
		int 0x10; // Interrupcion
	}
}

void quit()
{
	asm{
		mov ah,0x00; // MOdo texto
		mov al,0x03;
		int 0x10; // Interrupcion
	}
}

void flip( int banco )
{
	asm {
		mov dx,banco; // Banco a dx
		mov bx,0;
		mov ax,0x04f05; // svga.
		int 0x10; //Interrupcion
  }
}

void pixel(int x, int y, unsigned char color){

  asm {
    mov bx, 800
    mov ax, y
    mul bx
    add ax, x
    adc dx, 0
    push ax

    mov ax, 04f05h
    mov bx, 0
    int 010h

    pop di

    mov ax,0a000h
    mov es,ax

    mov al, [color]
    mov [es:di], al
  }
}

char getpixel(int x, int y){
	char color;
  asm {
		mov bx, 800
      mov ax, y
      mul bx
      add ax, x
      adc dx, 0
      push ax

      mov ax, 04f05h
      mov bx, 0
      int 010h

      pop di

      mov ax,0a000h
      mov es,ax

      mov al, [es:di]
      mov [color], al
  }
	return color;
}
