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
	int x, y, x1, y1, b, s=1, f=1, g=1, term=1, xtemp, ytemp;
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

			//Si esta en el canvas
			if (x<700&&y<450) {
				//Se evaluan los casos posibles de herramientas
				switch (f) {
					//Lapiz
					case 1:
					putPixel(x,y,g,color);
					break;
					//spray
					case 2:
					sprayNpray(&color, x, y);
					break;
					//rectangulo
					case 3:
					term=1;
					while (term) {
						repaintMouse(&x,&y,&b,&x1,&y1);
						if (b==0) {
							xtemp = x;
							ytemp = y;
							term=0;
						}
					}
					term=1;
					while (term) {
						repaintMouse(&x,&y,&b,&x1,&y1);
						if (b==1) {
							rectangulo(xtemp, ytemp,x,y,color);
							term=0;
						}
					}
					break;
					//rectangulo relleno
					case 4:
					break;
					//circulo
					case 5:
					term = 1;
					xtemp = x;
					ytemp = y;
					while (term) {
						repaintMouse(&x,&y,&b,&x1,&y1);
						if (b==1) {
							circulo(xtemp, ytemp,abs(xtemp-x),color);
							term=0;
						}
					}
					break;
					case 12:
					s=0;
					break;
				}
			}
		}else if (b==2) {
			color=getpixel(x,y);
		}
	}
	quit();
}
