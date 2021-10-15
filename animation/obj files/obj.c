#include "obj.h"

matrix* transformation;
char* filename;
int focal;
int f_global;


int read_obj(char* obj_file, image* output, color* objcolor, matrix* transf, int focaltype, int f){
    image* ppm_out;
    color* c_figure;
    int i;
    focal = focaltype;
    f_global = f;

    filename = obj_file;
    ppm_out = output;
    c_figure = objcolor;
    transformation = transf;

    FILE *file;
    char buffer[255];
    int cara[5],lados = 0,j,tid;
    coordinate tmp,beg,end;
    
    file = fopen(filename, "r");

    while (fscanf(file, "%s", buffer) != EOF){
        if (strcmp(buffer, "c") == 0){
            lados = 0;
        }else if(strcmp(buffer, "f") == 0 && lados == 0){
            lados++;
        }else if (strcmp(buffer, "f") == 0){
            for (i = 0; i < lados-2; i++){
                find_vortex( (cara+i) ,&beg);
                find_vortex( (cara+i+1) ,&end);
                bre_getline(ppm_out,beg,end,c_figure);
            }

            find_vortex( (cara) ,&beg); 
            find_vortex( (cara+lados-2) ,&end);
            bre_getline(ppm_out,beg,end,c_figure);

            lados = 1;
        }else if (lados != 0){
            cara[lados - 1] = atof(buffer);
            lados++;
        }
        
    }
    for (i = 0; i < lados-2; i++){
        find_vortex( (cara+i) ,&beg);
        find_vortex( (cara+i+1) ,&end);
        bre_getline(ppm_out,beg,end,c_figure);
    }
    find_vortex( (cara) ,&beg); 
    find_vortex( (cara+lados-2) ,&end);
    bre_getline(ppm_out,beg,end,c_figure);

    fclose(file);
    
}

int find_vortex(int* vortex_num, coordinate* vort){
    char buffer[255];
    FILE *toread;
    matrix out,coor;
    toread = fopen(filename, "r");
    int i = 0;

    init_matrix(&coor,1,4);
    coor.values[3][0] = 1;
    while(fscanf(toread, "%s", buffer) != EOF && i != *vortex_num){
        if (strcmp(buffer, "v") == 0)
            i++;
        if (i == *vortex_num){
            fscanf(toread,"%s",buffer);
            coor.values[0][0] = atof(buffer);
            fscanf(toread,"%s",buffer);
            coor.values[1][0] = atof(buffer);
            fscanf(toread,"%s",buffer);
            coor.values[2][0] = atof(buffer);

            
            multiply_matrix(transformation, &coor, &out);
            matrix pers;
            switch (focal){
            case X_FOCUS:
                
                matrix_focal_X(f_global,&out,&pers);
                vort->x = pers.values[1][0];
                vort->y = pers.values[2][0];
                break;
            case Y_FOCUS:
                matrix_focal_Y(f_global,&out,&pers);
                vort->x = pers.values[0][0];
                vort->y = pers.values[2][0];
                break;
            case Z_FOCUS:
                matrix_focal_Z(f_global,&out,&pers);
                
                vort->x = pers.values[0][0];
                vort->y = pers.values[1][0];
                break;
            default:
                vort->x = out.values[0][0];
                vort->y = out.values[1][0];
                break;
            }
            
        }
        
    }
    fclose( toread );

}

