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
        b_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3)]/9;
        b_mean[0] = b_temp;

        b_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3)]/9;
        b_mean[1] = b_temp;

        b_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)]/9;
        b_mean[2] = b_temp;

        b_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3)]/9;
        b_mean[3] = b_temp;

        b_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3)]/9;
        b_mean[4] = b_temp;

        b_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)]/9;
        b_mean[5] = b_temp;

        b_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3)]/9;
        b_mean[6] = b_temp;

        b_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3)]/9;
        b_mean[7] = b_temp;

        b_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3)]/9;
        b_mean[8] = b_temp;

        





        g_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 1]/9;
        g_mean[0] = g_temp;

        g_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 1]/9;
        g_mean[1] = g_temp;

        g_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 1]/9;
        g_mean[2] = g_temp;

        b_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 1]/9;
        b_mean[3] = g_temp;

        g_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 1]/9;
        g_mean[4] = g_temp;

        g_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 1]/9;
        g_mean[5] = g_temp;

        g_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 1]/9;
        g_mean[6] = g_temp;

        g_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 1]/9;
        g_mean[7] = g_temp;

        g_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 1]/9;
        g_mean[8] = g_temp;








        r_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 2]/9;
        r_mean[0] = r_temp;

        r_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 2]/9;
        r_mean[1] = r_temp;

        r_temp = ptr[((i+mask%2-1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 2]/9;
        r_mean[2] = r_temp;

        r_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 2]/9;
        r_mean[3] = r_temp;

        r_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 2]/9;
        r_mean[4] = r_temp;

        r_temp = ptr[((i+mask%2+1)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 2]/9;
        r_mean[5] = r_temp;

        r_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2-1)*3) + 2]/9;
        r_mean[6] = r_temp;

        r_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2+1)*3) + 2]/9;
        r_mean[7] = r_temp;

        r_temp = ptr[((i+mask%2)*(ancho+(mask%2)*2)*3)+((j+mask%2)*3) + 2]/9;
        r_mean[8] = r_temp;

        b_temp = 0;
        g_temp = 0;
        r_temp = 0;

        for (int k = 0; k < 9; k++){
          b_temp += b_mean[k];
          g_temp += g_mean[k];
          r_temp += r_mean[k];
        }

        fputc(b_temp, outputImage);
        fputc(g_temp, outputImage);
        fputc(r_temp, outputImage);
      }
      fputc(p[0], outputImage);
      fputc(p[1], outputImage);
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);

    return 0;
}
