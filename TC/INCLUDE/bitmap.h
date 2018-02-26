/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria de carga y guardado de bitmaps desarrollada en C
21/02/2017*/

int loadbitmap(int offX, int offY,char *archivo)
{
   FILE *ptr=NULL;                //file handle to open bitmap file
   int width,height;              //width and height of the bitmap
   unsigned long temp=0,i=0,j=0;  //some variables i need
   unsigned long ww;
   int ch,ch1,ch2;
   ptr=fopen(archivo,"rb");      //open the bitmap file
   if(!ptr){
     line(15,15,300,200,0,1);
     return 0;
   }             //if its not there return
   width=0;height=0;              //initialise wisth and height to zero
   fseek(ptr,18,SEEK_SET);        //got to offset 18 in file
   for(i=0x1;i<=0x10000;i*=0x100) //read the width
   {
           temp=fgetc(ptr);
           width+=(temp*i);
   }
   fseek(ptr,22,SEEK_SET);        //go to offset 22 in file
   for(i=0x1;i<=0x10000;i*=0x100) //read the height
   {
           temp=fgetc(ptr);
           height+=(temp*i);
   }

   ww=width;
   //ww is the number of reads to make for each horizontal line
   if(ww%2)
   //ww has to be half of width - since each pixel is only 4 bits of information
   ww++;ww/=2;
   //just getting the correct value
   if(ww%4)
   //now - ww is stored as sets of 4 pixels each
   ww=(ww/4)*4+4;
   //if width is less than ww*2 we ignore what we read

   fseek(ptr,119,SEEK_SET);
   //Ok! offset 119 - lets read the pixels -
   //remember the bitmap is stroed up - side - down
   for(i=0;i<height;i++)
   for(j=0;j<ww;j++)
   {
           ch=fgetc(ptr);
           //each character read is 2 pixels - yes 4 bits per pixel - so 16 colors
           ch1=ch;ch2=ch;
           //find those colors using bitwise ops
           ch1=ch1&(0xf0);
           // ~~
           ch2=ch2&(0x0f);
           // ~~
           if(j*2<width)
           //ok so put the first pixel read on screen
           pixel((j)*2+offX,(height-1-i)+offY,getcol(ch1));
           if(j*2+1<width)
           //put the second pixel read on screen
           pixel((j)*2+1+offX,(height-1-i)+offY,getcol(ch2));
   }
   fclose(ptr);
   //close the file handle
   return 1;
}



int getcol(int col)
{
   switch(col)
   {
      case 0: return 0;     //BLACK;
      case 1: return 4;     //RED;
      case 2: return 2;     //GREEN
      case 3: return 6;     //BROWN
      case 4: return 1;     //BLUE;
      case 5: return 5;     //MAGENTA;
      case 6: return 3;     //CYAN;
      case 7: return 7;     //LIGHTGRAY;
      case 8: return 8;     //DARKGRAY;
      case 9: return 12;    //LIGHTRED;
      case 10:return 10;    //LIGHTGREEN
      case 11:return 14;    //YELLOW;
      case 12:return 9;     //LIGHTBLUE;
      case 13:return 13;    //LIGHTMAGENTA
      case 14:return 11;    //LIGHTCYAN;
      case 15:return 15;    //WHITE;
   }
   return col;
}

void set_palette(char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1012
    mov bx, 0
    mov cx, 256
    int 0x10
  }
}


void guardar_imagen(int x, int y, int xmax, int height, char file[]){
  FILE * fileSave;
  int count, i, j, tempi;
  unsigned char pixel, ch;
  unsigned long headerBuf[13];
  long palette[256];
  char headerInfo[2] = "BM";
  //opens file
  fileSave = fopen(file, "wb");
  fwrite(headerInfo, sizeof(headerInfo[0]), 2, fileSave);
  x--; y--;                                   //improve file image at save
  headerBuf[0] = xmax * height + 1024 + 54;  //size
  headerBuf[1] = 0;                           // reserved
  headerBuf[2] = 1024 + 54;                   // offset
  headerBuf[3] = 40;                          // size header
  //ancho de la imagen
  headerBuf[4] = xmax;
  headerBuf[5] = height;                      // height
  headerBuf[6] = 0x80001;                     // planes
  headerBuf[7] = 0;                           // compression
  headerBuf[8] = xmax*height;                // actual size
  headerBuf[9] = 0;
  headerBuf[10] = 0;
  headerBuf[11] = 256;                          // colors
  headerBuf[12] = 256;                          // important colors
  fwrite(headerBuf, sizeof(headerBuf[0]), 13,  fileSave);
  set_palette(palette);
  palette[0] = 0;
  palette[1] = 0x8;
  palette[2] = 0x800;
  palette[3] = 0x808;
  palette[4] = 0x80000;
  palette[5] = 0x80008;
  palette[6] = 0x80400;
  palette[7] = 0xC0C0C;
  palette[8] = 0x80808;
  palette[9] = 0xFF;
  palette[10] = 0xFF00;
  palette[11] = 0xFFFF;
  palette[12] = 0xFF0000;
  palette[13] = 0xFF00FF;
  palette[14] = 0xFFFF00;
  palette[15] = 0xFFFFFF;
  fwrite(palette, sizeof(long), 255,  fileSave);

  for(j=(y+height); j>=y; j--){
    for(i=x; i<=(xmax+x)-1; i++){
     pixel=getpixel(i, j);
     fwrite(&pixel,1,1, fileSave);
    }
  }
  fclose( fileSave);
}
