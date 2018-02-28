/*Universidad del Valle de Guatemala
Rodrigo Alvarado - 16106
Libreria de carga y guardado de bitmaps desarrollada en C
21/02/2017*/
typedef unsigned int WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
//STRUCT DE UN BMP
typedef struct bmp {
  int width;
  int height;
  char palette[256*3];
  char *data;
} BITMAP;

//Struct de un header de bmp
typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

//Struct de header de bmp
typedef struct tagBITMAPINFOHEADER{
	DWORD  biSize;
	DWORD  biWidth;
	DWORD  biHeight;
	WORD   biPlanes;
	WORD   biBitCount;
	DWORD  biCompression;
	DWORD  biSizeImage;
	DWORD  biXPelsPerMeter;
	DWORD  biYPelsPerMeter;
	DWORD  biClrUsed;
	DWORD  biClrImportant;
} BITMAPINFOHEADER;

//carga un bitmap de 16 colores, para los botones
int loadbitmap(int offX, int offY,char *archivo)
{
  //archivo
   FILE *ptr=NULL;
   int width,height;              //alto y ancho
   unsigned long temp=0,i=0,j=0;
   unsigned long ww;
   int ch,ch1,ch2;
   ptr=fopen(archivo,"rb");      //Abir en modo read
   //Regresar si no existe
   if(!ptr){
     return 0;
   }
   width=0;height=0;
   fseek(ptr,18,SEEK_SET);
   for(i=0x1;i<=0x10000;i*=0x100)
   {
           temp=fgetc(ptr);
           width+=(temp*i);
   }
   fseek(ptr,22,SEEK_SET);
   for(i=0x1;i<=0x10000;i*=0x100)
   {
           temp=fgetc(ptr);
           height+=(temp*i);
   }

   ww=width;
   if(ww%2)ww++;ww/=2;
   if(ww%4)ww=(ww/4)*4+4;
   fseek(ptr,119,SEEK_SET);
   for(i=0;i<height;i++)
   for(j=0;j<ww;j++)
   {
           ch=fgetc(ptr);
           ch1=ch;ch2=ch;
           ch1=ch1&(0xf0);
           ch2=ch2&(0x0f);
           if(j*2<width)pixel((j)*2+offX,(height-1-i)+offY,getcol(ch1));
           if(j*2+1<width)pixel((j)*2+1+offX,(height-1-i)+offY,getcol(ch2));
   }
   //cerrar el archivo
   fclose(ptr);
   return 1;
}


//Paleta de colores de 16 colores
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

//Pone la paleta a ser usada, dx recibe un array de colores
void set_palette(char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1012
    mov bx, 0
    mov cx, 256
    int 0x10
  }
}

//Guarda una imagen bmp
void guardar_imagen(int x, int y, int xmax, int height, char file[]){
  FILE * fileSave;
  int count, i, j, tempi;
  unsigned char pixel, ch;
  unsigned long Header[13];
  long palette[256];
  char headerInfo[2] = "BM";
  //abrir arvhivo
  fileSave = fopen(file, "wb");
  fwrite(headerInfo, sizeof(headerInfo[0]), 2, fileSave);
  x--; y--;
  //HEADERS
  //Tamano
  Header[0] = xmax * height + 1024 + 54;
  //?????? ni idea pero esta en los headers requeridos
  Header[1] = 0;
  //offset
  Header[2] = 1024 + 54;
  Header[3] = 40;
  //ancho y alto de la imagen
  Header[4] = xmax;
  Header[5] = height;
  Header[6] = 0x80001;
  Header[7] = 0;
  Header[8] = xmax*height;
  Header[9] = 0;
  Header[10] = 0;
  //cantidad de colores
  Header[11] = 256;
  Header[12] = 256;
  fwrite(Header, sizeof(Header[0]), 13,  fileSave);
  set_palette(palette);
    //PALETA, NO COMPLETA PERO PALETA
    palette[0] = 000000;
  	palette[1] = 0x800000;
  	palette[2] = 0x008000;
    palette[3] = 0x808000;
   	palette[4] = 0x000080;
  	palette[5] = 0x800080;
  	palette[6] = 0x008080;
    palette[7] = 0xc0c0c0;
    palette[8] = 0x808080;
    palette[9] = 0xFF0000;
   	palette[10] = 0x00FF00;
  	palette[11] = 0xFFFF00;
   	palette[12] = 0x0000FF;
   	palette[13] = 0xFF00FF;
   	palette[14] = 0x00FFFF;
   	palette[15] = 0xFFFFFF;
   	palette[16] = 0x000000;
  	palette[17] = 0x00005F;
    palette[18] = 0x000087;
  	palette[19] = 0x0000AF;
   	palette[20] = 0x0000D7;
  	palette[21] = 0x0000FF;
  	palette[22] = 0x005f00;
  	palette[23] = 0x005f5f;
  	palette[24] = 0x005f87;
  	palette[25] = 0x005faf;
   	palette[26] = 0x005fd7;
    palette[27] = 0x005fff;
   	palette[28] = 0x008700;
   	palette[29] = 0x00875f;
   	palette[30] = 0x008787;
   	palette[31] = 0x0087af;
   	palette[32] = 0x0087d7;
  	palette[33] = 0x0087ff;
    palette[34] = 0x00af00;
  	palette[35] = 0x00af5f;
   	palette[36] = 0x00af87;
  	palette[37] = 0x00afaf;
    palette[38] = 0x00afd7;
  	palette[39] = 0x00afff;
  	palette[40] = 0x00d700;
    palette[41] = 0x00d75f;
   	palette[42] = 0x00d787;
  	palette[43] = 0x00d7af;
   	palette[44] = 0x00d7d7;
   	palette[45] = 0x00d7ff;
   	palette[46] = 0x00ff00;
   	palette[47] = 0x00ff5f;
   	palette[48] = 0x00ff87;
  	palette[49] = 0x00ffaf;
  	palette[50] = 0x00ffd7;
    palette[51] = 0x00ffff;
   	palette[52] = 0x5f0000;
    palette[53] = 0x5f005f;
    palette[54] = 0x5f0087;
    palette[55] = 0x5f00af;
    palette[56] = 0x5f00d7;
    palette[57] = 0x5f00ff;
   	palette[58] = 0x5f5f00;
    palette[59] = 0x5f5f5f;
   	palette[60] = 0x5f5f87;
   	palette[61] = 0x5f5faf;
   	palette[62] = 0x5f5fd7;
   	palette[63] = 0x5f5fff;
  fwrite(palette, sizeof(long), 255,  fileSave);

  //Tomar los pixeles e ingresarlos al archivo
  for(j=(y+height); j>=y; j--){
    for(i=x; i<=(xmax+x)-1; i++){
     pixel=getpixel(i, j);
     fwrite(&pixel,1,1, fileSave);
    }
  }
  //cerrrar archivo
  fclose( fileSave);
}

//Cargar bitmaps
int read(int x, int y, char *file, BITMAP *bmpFile) {
  FILE *fileC;
  int idx;
  int cantColors;
  int i, j;
  unsigned char ti, t;
  //Abrir el arvhivo en modo leer
  if ((fileC = fopen(file, "rb")) == NULL) {
    return 1;
  }
  if(fgetc(fileC) != 'B' || fgetc(fileC) != 'M'){
    fclose(fileC);
    return 1;
  }
  ignoreLine(fileC,16);
  fread(&bmpFile->width, 2, 1, fileC);
  ignoreLine(fileC,2);
  fread(&bmpFile->height, 2, 1, fileC);
  ignoreLine(fileC,22);
  fread(&cantColors, 2, 1, fileC);
  ignoreLine(fileC, 6);
  if (cantColors == 0) {
    cantColors = 256;
  }
  for (idx = 0; idx < cantColors; idx++){
    bmpFile->palette[idx*3+2] = fgetc(fileC) / 4;
    bmpFile->palette[idx*3+1] = fgetc(fileC) / 4;
    bmpFile->palette[idx*3] = fgetc(fileC) / 4;
    fgetc(fileC);
  }
  //Mientras se encuentre entre el ancho y el alto, se pinta el pixel en pantalla
  for(j = (bmpFile->height); j > 0; j--){
    for(i = 0; i < bmpFile->width ; i++){
      ti = fgetc(fileC);
      if (ti > 250){
        ti = 15;
      }
      pixel(i+x, j+y, ti);
    }
  }
  //cerrar el archivo
  fclose(fileC);

  return 0;
}


//Igunora una linea en el bmp para saltar a otros pedazos del header, cortesia de Javier Ramos
int ignoreLine(FILE *file, int cantBytes){
   int i;
   for (i = 0; i < cantBytes; i++) {
      fgetc(file);
   }
   return 0;
}
