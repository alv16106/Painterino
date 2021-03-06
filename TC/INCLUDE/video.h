/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria grafica desarrollada en C
21/02/2017*/

int i,j;
//Empieza el modo de video
void modoVideo()
{
	asm{
		mov ax,0x04f02; // svga.
		mov bx,0x0103; // 800x600 y 256 colores.
		int 0x10; // Interrupcion
	}
}

//Sale al modo texto
void quit()
{
	asm{
		mov ah,0x00; // MOdo texto
		mov al,0x03;
		int 0x10; // Interrupcion
	}
}

//Cambia de banco
void flip( int banco )
{
	asm {
		mov dx,banco; // Banco a dx
		mov bx,0;
		mov ax,0x04f05; // svga.
		int 0x10; //Interrupcion
  }
}

//Pone un pixel de un grosor determinado
int putPixel(int x, int y, int grosor, unsigned char color){
	int i;
	for (i = 0; i < grosor; i++) {
		pixelFig(x,y+i,color);
		pixelFig(x+i,y,color);
		pixelFig(x,y-i,color);
		pixelFig(x-i,y,color);
	}
	return 0;
}

//Pone un pixel grosor 1
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

//Pone un pixel que no sale del canvas
int pixelFig(int x, int y, unsigned char color){
	//Esta en el canvas?
	if (x>700||y>450||x<0||y<0) {
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

//Recibe cordenadas x y y
//Devuelve el color del canvas en esas coordenadas
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

//Pinta el canvas y carga los bitmaps
void canvas(){
	int i,j,color,h;
	color=0;
	//CONTORNOS
	for (i=0;i<700;i++){
		for(j=0;j<450;j++){
			pixel(i,j,15);
		}
	}
	for (i=700;i<800;i++){
		for(j=0;j<600;j++){
			pixel(i,j,18);
		}
	}
	for (i=0;i<800;i++){
		for(j=450;j<600;j++){
			pixel(i,j,18);
		}
	}

	//PALETA DE COLORES
	for (i=0;i<700;i+=15){
		for(j=467;j<517;j++){
			pixel(i,j,color);
			pixel(i+1,j,color);
			pixel(i+2,j,color);
			pixel(i+3,j,color);
			pixel(i+4,j,color);
			pixel(i+5,j,color);
			pixel(i+6,j,color);
			pixel(i+7,j,color);
			pixel(i+8,j,color);
			pixel(i+9,j,color);
			pixel(i+10,j,color);
			pixel(i+11,j,color);
			pixel(i+12,j,color);
			pixel(i+13,j,color);
		}
		color++;
	}

	for (i=0;i<700;i+=15){
		for(j=533;j<583;j++){
			pixel(i,j,color);
			pixel(i+1,j,color);
			pixel(i+2,j,color);
			pixel(i+3,j,color);
			pixel(i+4,j,color);
			pixel(i+5,j,color);
			pixel(i+6,j,color);
			pixel(i+7,j,color);
			pixel(i+8,j,color);
			pixel(i+9,j,color);
			pixel(i+10,j,color);
			pixel(i+11,j,color);
			pixel(i+12,j,color);
			pixel(i+13,j,color);
		}
		color++;
	}
	//BOTONES DEL MENU
	loadbitmap(710,20,"C:/Bitmaps/lapiz.bmp");
	loadbitmap(710+45,20,"C:/Bitmaps/spray.bmp");
	loadbitmap(710,20+45,"C:/Bitmaps/rect.bmp");
	loadbitmap(710+45,20+45,"C:/Bitmaps/rectFill.bmp");
	loadbitmap(710,20+90,"C:/Bitmaps/circulo.bmp");
	loadbitmap(710+45,20+90,"C:/Bitmaps/circF.bmp");
	loadbitmap(710,20+135,"C:/Bitmaps/elip.bmp");
	loadbitmap(710+45,20+135,"C:/Bitmaps/elipFill.bmp");
	loadbitmap(710,20+180,"C:/Bitmaps/poli.bmp");
	loadbitmap(710+45,20+180,"C:/Bitmaps/poliFill.bmp");
	loadbitmap(710,20+225,"C:/Bitmaps/line.bmp");
	loadbitmap(710+45,20+225,"C:/Bitmaps/cut.bmp");
	loadbitmap(710,20+270,"C:/Bitmaps/copy.bmp");
	loadbitmap(710+45,20+270,"C:/Bitmaps/paste.bmp");
	loadbitmap(710,20+315,"C:/Bitmaps/borrador.bmp");
	loadbitmap(710+45,20+315,"C:/Bitmaps/bucket.bmp");
	loadbitmap(710,20+360,"C:/Bitmaps/marcador.bmp");
	loadbitmap(710+45,20+360,"C:/Bitmaps/quit.bmp");
	loadbitmap(710,20+45+360,"C:/Bitmaps/save.bmp");
	loadbitmap(710+45,20+45+360,"C:/Bitmaps/new.bmp");
	loadbitmap(710,20+45+45+360,"C:/Bitmaps/grosor.bmp");

}

//Limpia el canvas
void nuevo() {
	int i,j;
	for (i=0;i<700;i++){
		for(j=0;j<450;j++){
			pixel(i,j,15);
		}
	}
}
