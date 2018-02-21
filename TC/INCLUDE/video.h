

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

int putPixel(int x, int y, int grosor, unsigned char color){
	int i;
	for (i = 0; i < grosor; i++) {
		pixel(x+i,y+i,color);
	}
	return 0;
}

int pixel(int x, int y, unsigned char color){
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
return 0;
}

int pixelFig(int x, int y, unsigned char color){
	if (x>700||y>450) {
		return 0;
	}
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
return 0;
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

void canvas(){
	int i,j,color,h;
	color=0;
	for (i=0;i<700;i++){
		for(j=0;j<450;j++){
			pixel(i,j,15);
		}
	}
	for (i=700;i<800;i++){
		for(j=0;j<600;j++){
			pixel(i,j,8);
		}
	}

	//COlores
	for (i=0;i<700;i+=5){
		for(j=450;j<600;j++){
			pixel(i,j,color);
			pixel(i+1,j,color);
			pixel(i+2,j,color);
			pixel(i+3,j,color);
			pixel(i+4,j,color);
		}
		color++;
	}
	loadbitmap(710,20,"C:/Bitmaps/lapiz.bmp");
	loadbitmap(710+45,20,"C:/Bitmaps/spray.bmp");
	loadbitmap(710,20+45,"C:/Bitmaps/rect.bmp");
	loadbitmap(710+45,20+45,"C:/Bitmaps/rectFill.bmp");
	loadbitmap(710,20+90,"C:/Bitmaps/circulo.bmp");
	loadbitmap(710+45,20+90,"C:/Bitmaps/circulo.bmp");
	loadbitmap(710,20+135,"C:/Bitmaps/elip.bmp");
	loadbitmap(710+45,20+135,"C:/Bitmaps/elipFill.bmp");
	loadbitmap(710,20+180,"C:/Bitmaps/poli.bmp");
	loadbitmap(710+45,20+180,"C:/Bitmaps/poliFill.bmp");
	loadbitmap(710,20+225,"C:/Bitmaps/line.bmp");
	loadbitmap(710+45,20+225,"C:/Bitmaps/quit.bmp");
	loadbitmap(710,20+270,"C:/Bitmaps/cut.bmp");
	loadbitmap(710+45,20+270,"C:/Bitmaps/copy.bmp");
	loadbitmap(710,20+315,"C:/Bitmaps/paste.bmp");
	loadbitmap(710+45,20+315,"C:/Bitmaps/borrador.bmp");
}
