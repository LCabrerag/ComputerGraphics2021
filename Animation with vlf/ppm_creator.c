#include "ppm_creator.h"
#define NUM(x) ((x)>9)?(((x)>99)?(3):(2)):(1) 

int create_image(image* output,color* bkg){
    output->img = (color*)calloc(output->x*output->y,sizeof(color));
    int i,j;
    for (i = 0; i < output->y; i++){
        for (j = 0; j < output->x; j++){
            *(output->img + GET_POS_XY(j,i,output)) = *bkg;
        }
    }
}

int export_ppm(image* output, char* filename){
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
        tmp = (char*)calloc(3 + NUM((output->img + i)->R) + NUM((output->img + i)->G) + NUM((output->img + i)->B),sizeof(char));
        sprintf(tmp," %d %d %d", (output->img + i)->R, (output->img + i)->G, (output->img + i)->B);
        fputs(tmp,file);
    }
}
