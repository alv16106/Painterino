#include stdlib.h // For the ldiv();
#include stdio.h// For the getch();


// Initialize svga in resolution of 800x600 and 256 colors.
// This is the first procedure to be called.
void init_800_600()
{
asm mov ax,0x04f02; // svga.
asm mov bx,0x0103; // 800x600 and 256 colors.
asm int 0x10; // Do it.
}


// This procedure is called int the end. It sets the video-mode
// to text.
void quit()
{
asm mov ah,0x00; // Set video-mode.
asm mov al,0x03; // Back to normal.
asm int 0x10; // Do it.
}


// We can't use all the memory at the same time because
// of the 64 k limit. This procedure flips the page.
void flip_page(short page)
{
asm mov dx,page; // Move the page-number to dx.
asm mov bx,0; // bx is now 0.
asm mov ax,0x04f05; // svga.
asm int 0x10; // Do it.
}


// Draws a pixel.
// Calculation of the page and pixel's location in memory
// takes probably too much time and should be done
// some other manner?
void pixel(long x, long y, unsigned char color)
{
long location = ( y * 800L + x ); // Calculate the place in memory.

ldiv_t page = ldiv(location,65536L); // We cannot use all the memory at the
flip_page(page.quot); // same time because of the 64 k limit.
// Calculate the page.

// Calculate the new location in the page.
unsigned int new_location = location-(page.quot*65536);

// Plot a pixel.
asm mov ax,0x0A000;
asm mov es,ax;
asm mov al,color;
asm mov di, new_location;
asm mov es:[di], al;
}


int main(void)
{
init_800_600(); // Initialize the svga in 800x600
// and 256 colors.

// Fill the screen.
for ( unsigned int y = 0; y < 600; y++ )
for ( unsigned int x = 0; x < 800; x++ )
pixel(x,y,10);

getch(); // Wait for a key.
quit(); // Set video-mode to normal.
return 0; // All OK :)
}
