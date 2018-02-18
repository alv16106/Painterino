#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "video.h"
#include "mouse.h"
#include "formas.h"
#include "bitmap.h"

void main() {
	int x1, y1, b, g, s;
	modoVideo();
	get_mouse();
	canvas();
	mouse_limit();
	//loadbitmap();
	sprayNpray();
	getch();

	quit();
}
