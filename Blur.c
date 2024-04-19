#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("sample.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_E.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    
    unsigned char r, g, b, p[2];               //Pixel
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    printf(" byte_1: %x\nbyte_2: %x\n byte_3: %x\n byte_4: %x\n", xx[18], xx[19], xx[20], xx[21]);

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("ancho img %li\n",ancho);
    printf("largo img %li\n",alto);

    ptr = (unsigned char*)malloc(alto*ancho*3*sizeof(unsigned char));

    while(!feof(image)){
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

        ptr[cuenta] = p[0];
        ptr[cuenta+1] = p[1];

        cuenta += 2;
      }
    }                                        //Grises
    printf("%d\n",cuenta);

    for (int i = 0; i < alto*ancho*3; i+=3) {
      fputc(ptr[i], outputImage);
      fputc(ptr[i+1], outputImage);
      fputc(ptr[i+2], outputImage);
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);

    return 0;
}
