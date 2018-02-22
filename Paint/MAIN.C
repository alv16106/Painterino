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
#include "formas.h"
#include "bitmap.h"

void main() {
	unsigned char color;
	int x, y, x1, y1, b, s=1, f=1, term, xtemp, ytemp,g=3;
	color = 0;
	modoVideo();
	get_mouse();
	canvas();
	mouse_limit();
	while (s){
		repaintMouse(&x,&y,&b,&x1,&y1);
		if(b==1){
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

			//Si esta en el canvas
			if (x<700&&y<450) {
				//Se evaluan los casos posibles de herramientas
				switch (f) {
					//Lapiz
					case 1:
					//putPixel(x,y,g,color);
					if (abs(x-xtemp)<10)line(xtemp,ytemp,x,y,color);
					xtemp=x;
					ytemp=y;
					break;
					//spray
					case 2:
					sprayNpray(&color, x, y, g);
					break;
					//rectangulo
					case 3:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					rectangulo(xtemp, ytemp,x,y,color);
					break;
					//rectangulo relleno
					case 4:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					rectangulo(xtemp, ytemp,x,y,color);
					floodFill((x+xtemp)/2,(y+ytemp)/2,getpixel((x+xtemp)/2,(y+ytemp)/2),color+1);
					break;
					//circulo
					case 5:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					circulo(xtemp, ytemp,(int)sqrt(abs(x-xtemp)*abs(x-xtemp)+abs(y-ytemp)*abs(y-ytemp)),color);
					break;
					//circulo relleno
					case 6:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					circulo(xtemp, ytemp,(int)sqrt(abs(x-xtemp)*abs(x-xtemp)+abs(y-ytemp)*abs(y-ytemp)),color);
					floodFill(xtemp, ytemp,getpixel(xtemp,ytemp),color);
					break;
					//Elipse
					case 7:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					Elipse(xtemp, ytemp,abs(x-xtemp),abs(y-ytemp),color);
					break;
					//Elipse llena
					case 8:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					Elipse(xtemp, ytemp,abs(x-xtemp),abs(y-ytemp),color);
					floodFill(xtemp, ytemp,getpixel(xtemp,ytemp),color);
					break;
					//Poligono
					case 9:
					//poligono(x,y,color);
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
					line(xtemp, ytemp,x,y,color);
					break;
					//Cut
					case 12:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					copy(xtemp,ytemp,x,y);
					break;
					//copy
					case 13:
					xtemp = x;
					ytemp = y;
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					copy(xtemp,ytemp,x,y);
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
					break;
					//Fill
					case 16:
					while (b==1) {
						repaintMouse(&x,&y,&b,&x1,&y1);
					}
					mouseHide(x,y);
					floodFill(x,y,getpixel(x,y),color);
					mouseShow(x,y);
					break;
					//Marcador
					case 17:
					break;
					//Abrir
					case 18:
					break;
					//Guardar
					case 19:
					break;
				}
			}
		}else if (b==2) {
			color=getpixel(x,y);
		}
	}
	quit();
}
