#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("sample.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_E.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    int mask = 3;
    
    unsigned char r, g, b, p[2];               //Pixel
    unsigned char r_temp, g_temp, b_temp;               //Pixel
    unsigned char r_mean[mask*mask], g_mean[mask*mask], b_mean[mask*mask];
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;


    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("ancho img %li\n",ancho);
    printf("largo img %li\n",alto);

    ptr = (unsigned char*)malloc((alto+(mask%2)*2)*(ancho+(mask%2)*2)*3*sizeof(unsigned char));

    for (int i = 0; i < mask%2; i++){
      for (int j = 0; j < (ancho+(mask%2)*2)*3; j+=3){
        ptr[j] = 0;
        ptr[j + 1] = 0;
        ptr[j + 2] = 0;
      }
    }
    
    cuenta += (ancho+(mask%2)*2)*3*(mask%2);
    
    while(!feof(image)){
      for (int i = cuenta; i < cuenta + (mask%2)*3; i+=3){
        ptr[i] = 0;
        ptr[i + 1] = 0;
        ptr[i + 2] = 0;
      }

      cuenta += (mask%2)*3;

      for (int i = 0; i < ancho*3 && !feof(image); i+=3){
        b = fgetc(image);
        g = fgetc(image);
        r = fgetc(image);

        ptr[cuenta] = b; //b
        ptr[cuenta + 1] = g; //g
        ptr[cuenta + 2] = r; //r
        cuenta += 3;
      }

      if (!feof(image)){
        p[0] = fgetc(image);
        p[1] = fgetc(image);
      }
      
      for (int i = cuenta; i < cuenta + (mask%2)*3; i+=3){
        ptr[i] = 0;
        ptr[i + 1] = 0;
        ptr[i + 2] = 0;
      }

      cuenta += (mask%2)*3;
    }                                       //Grises

    for (int i = 0; i < mask%2; i++){
      for (int j = cuenta; j < cuenta + (ancho+(mask%2)*2)*3; j+=3){
        ptr[j] = 0;
        ptr[j + 1] = 0;
        ptr[j + 2] = 0;
      }
    }

    cuenta += (ancho+(mask%2)*2)*3*(mask%2);

    for (int i = 0; i < alto; i++) {
      for (int j = 0; j < ancho*3; j+=3) {
        b_temp = ptr[((i+mask%2-1)*(ancho+(mask%2-1)*2)*3)+((j+mask%2)*3)];
        b_mean[0] = b_temp;

        
        b_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)];
        g_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)]; 
        r_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)]; 
        fputc(ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)], outputImage);
        fputc(ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)+1], outputImage);
        fputc(ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)+2], outputImage);
      }
      fputc(p[0], outputImage);
      fputc(p[1], outputImage);
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);

    return 0;
}
