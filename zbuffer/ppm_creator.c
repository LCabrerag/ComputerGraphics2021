#include "ppm_creator.h"
#define NUM(x) ((x)>9)?(((x)>99)?(3):(2)):(1) 

int create_image(raster* output,color* bkg){
    output->img = (pixel_inf*)calloc(output->x*output->y,sizeof(pixel_inf));
    int i,j;
    for (i = 0; i < output->y; i++){
        for (j = 0; j < output->x; j++){
            (output->img + GET_POS_XY(j,i,output))->pixel_color = *bkg;
            (output->img + GET_POS_XY(j,i,output))->z_buffer = 0.0;
        }
    }
}

int export_ppm(raster* output, char* filename){
    FILE *file;
    file = fopen(filename, "w+");

    fputs(PPM_CONFIG,file);
    char* tmp;
    tmp = (char*)calloc(30,sizeof(char));
    sprintf(tmp,"%d %d \n",output->x,output->y);
    fputs(tmp ,file);

    fputs("255 \n",file);
    free(tmp);
    int i,j;
    for (i = 0; i < output->x*output->y; i++){
        tmp = (char*)calloc(3 + NUM(output->img[i].pixel_color.R) + NUM(output->img[i].pixel_color.G) + NUM(output->img[i].pixel_color.B),sizeof(char));
        sprintf(tmp," %d %d %d", (output->img + i)->pixel_color.R, (output->img + i)->pixel_color.G, (output->img + i)->pixel_color.B);
        
        fputs(tmp,file);
    }
    
}
