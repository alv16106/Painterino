/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Programa de dibujo libre desarrollado en C
21/02/2017*/

#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#include "video.h"
#include "mouse.h"
#include "bitmap.h"
#include "formas.h"

void main() {
	unsigned char color;
	BITMAP bm;
	int x, y, x1, y1, b, s=1, f=1, term=1, xtemp, ytemp,g=1,i,j,iniciox,inicioy,p=0;
	color = 0;
	//PREPARACIONES
	modoVideo();
	get_mouse();
	canvas();
	mouse_limit();
	for(i=755;i<790;i++){
		for (j=470;j<505;j++) {
			pixel(i,j,15);
		}
	}
	floodFill2((755+790)/2,(470+505)/2,15,16,0);
	//Cargar la imagen de la utima vez que se abrio el paint
	read(0,0,"C:/guard/ty.bmp",&bm);
	mouseShow(20,20);
	mouseHide(20,20);

	//PROGRAMA
	while (s){
		repaintMouse(&x,&y,&b,&x1,&y1);
		if(b==1){
			//Si esta dentro del menu, se elige una opcion
			if(x>710&&x<710+35&&y>20&&y<20+35)f=1;
			if(x>710+45&&x<710+80&&y>20&&y<20+35)f=2;
			//
			if(x>710&&x<710+35&&y>20+45&&y<20+80)f=3;
			if(x>710+45&&x<710+80&&y>20+45&&y<20+80)f=4;
			//
			if(x>710&&x<710+35&&y>20+90&&y<20+125)f=5;
			if(x>710+45&&x<710+80&&y>20+90&&y<20+125)f=6;
			//
			if(x>710&&x<710+35&&y>20+135&&y<20+170)f=7;
			if(x>710+45&&x<710+80&&y>20+135&&y<20+170)f=8;
			//
			if(x>710&&x<710+35&&y>20+180&&y<20+215)f=9;
			if(x>710+45&&x<710+80&&y>20+180&&y<20+215)f=10;
			//
			if(x>710&&x<710+35&&y>20+225&&y<20+260)f=11;
			if(x>710+45&&x<710+80&&y>20+225&&y<20+260)f=12;
			//
			if(x>710&&x<710+35&&y>20+225+45&&y<20+260+45)f=13;
			if(x>710+45&&x<710+80&&y>20+225+45&&y<20+260+45)f=14;
			//
			if(x>710&&x<710+35&&y>20+225+90&&y<20+260+90)f=15;
			if(x>710+45&&x<710+80&&y>20+225+90&&y<20+260+90)f=16;
			//
			if(x>710&&x<710+35&&y>20+225+135&&y<20+260+135)f=17;
			if(x>710+45&&x<710+80&&y>20+225+135&&y<20+260+135)s=0;
			//
			//GUARDADO DE BITMAPS
			if(x>710&&x<710+35&&y>20+225+135+45&&y<45+20+260+135){
				while (b==1) {
					repaintMouse(&x,&y,&b,&x1,&y1);
				}
				guardado(p);
			}
			if(x>710+45&&x<710+80&&y>20+225+135+45&&y<45+20+260+135)nuevo();
			//
			//Cambiar el grosor de la linea
			if(x>710&&x<710+35&&y>470&&y<505){
				while (b==1) {
					repaintMouse(&x,&y,&b,&x1,&y1);
				}
				g++;
				if(g>3) g=1;
			}
			//PATRONES
			if(x>710+45&&x<710+80&&y>470&&y<505){
				while (b==1) {
					repaintMouse(&x,&y,&b,&x1,&y1);
				}
				p++;
				if(p>3) p=0;
				mouseHide(x,y);
				for(i=755;i<790;i++){
					for (j=470;j<505;j++) {
						pixel(i,j,15);
					}
				}
				floodFill2((755+790)/2,(470+505)/2,15,16,p);
				mouseShow(x,y);
			}

			//Si esta en el canvas
			if (x<700&&y<450) {
				//Se evaluan los casos posibles de herramientas
				switch (f) {
					//Lapiz
					case 1:
					//putPixel(x,y,g,color);
					if (abs(x-xtemp)<15&&abs(y-ytemp)<15)line(xtemp,ytemp,x,y,color,g);
					xtemp=x;
					ytemp=y;
					break;
					//spray
					case 2:
					sprayNpray(color, x, y, g,0);
					break;
					//rectangulo
					case 3:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					rectangulo(xtemp, ytemp,x,y,color,g);
					mouseShow(x,y);
					break;
					//rectangulo relleno
					case 4:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					rectangulo(xtemp, ytemp,x,y,color,g);
					floodFill((x+xtemp)/2,(y+ytemp)/2,getpixel((x+xtemp)/2,(y+ytemp)/2),color,p);
					mouseShow(x,y);
					break;
					//circulo
					case 5:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					circulo(xtemp, ytemp,(int)sqrt(abs(x-xtemp)*abs(x-xtemp)+abs(y-ytemp)*abs(y-ytemp)),color,g);
					mouseShow(x,y);
					break;
					//circulo relleno
					case 6:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					circulo(xtemp, ytemp,(int)sqrt(abs(x-xtemp)*abs(x-xtemp)+abs(y-ytemp)*abs(y-ytemp)),color,g);
					floodFill(xtemp, ytemp,getpixel(xtemp,ytemp),color,p);
					mouseShow(x,y);
					break;
					//Elipse
					case 7:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					Elipse(xtemp, ytemp,abs(x-xtemp),abs(y-ytemp),color,g);
					mouseShow(x,y);
					break;
					//Elipse llena
					case 8:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					Elipse(xtemp, ytemp,abs(x-xtemp),abs(y-ytemp),color,g);
					floodFill(xtemp, ytemp,getpixel(xtemp,ytemp),color,p);
					mouseShow(x,y);
					break;
					//Poligono
					case 9:
					term=1;
					iniciox=x;
				  inicioy=y;
					xtemp = x;
					ytemp = y;
					while (term==1){
						repaintMouse(&x,&y,&b,&x1,&y1);
						if (b==1){
							if (x>700||y>450) {
								mouseHide(x,y);
								line(xtemp,ytemp,iniciox,inicioy, color,g);
								mouseShow(x,y);
								term=0;
							}else{
								while(b==1){
									repaintMouse(&x,&y,&b,&x1,&y1);
								}
								//
								mouseHide(x,y);
								line(x,y,xtemp,ytemp,color,g);
								mouseShow(x,y);
								xtemp=x;
								ytemp=y;
							}
						}else if(b==2){
							while (b==2) {
								repaintMouse(&x,&y,&b,&x1,&y1);
							}
							mouseHide(x,y);
							line(xtemp,ytemp,iniciox,inicioy, color,g);
							mouseShow(x,y);
							term=0;
						}
					}
					break;
					//Poligono lleno
					case 10:
					break;
					//linea
					case 11:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					line(xtemp, ytemp,x,y,color,g);
					break;
					//Cut
					case 12:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					copy(1,xtemp,ytemp,x,y);
					mouseShow(x,y);
					break;
					//copy
					case 13:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					copy(0,xtemp,ytemp,x,y);
					mouseShow(x,y);
					break;
					//paste
					case 14:
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					paste(x,y);
					mouseShow(x,y);
					break;
					//borrador
					case 15:
					sprayNpray(15, x, y,g,1);
					break;
					//Fill
					case 16:
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					floodFill(x,y,getpixel(x,y),color,p);
					mouseShow(x,y);
					break;
					//Marcador
					case 17:
					sprayNpray(color, x, y,g,1);
					break;
					//Guardar
					case 18:
					break;
					//Nuevo
					case 19:
					break;
					//Abrir
					case 20:
					break;
					//Patrones
					case 21:
					break;
				}
			}
		}else if (b==2) {
			//Tomar color
			color=getpixel(x,y);
			//Pintar color elegido en un cuadro
			for (i=710;i<790;i++){
				for(j=520;j<580;j++){
					pixel(i,j,color);
				}
			}
		}
	}
	//Se guarda la imagen de lo ultimo que hubo en pantalla para que pueda ser cargado una vez vuelva a abrir el paitn
	guardar_imagen(0, 0, 700, 450, "C:/guard/ty.bmp");
	quit();
}
