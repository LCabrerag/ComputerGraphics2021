#include "coordinates.h"

int add_point(image* output, coordinate pos, color* newcol){
    if (pos.x > 0 && pos.y > 0 && pos.x < output->x && pos.y < output->y){
        *(output->img + GET_POS_XY(pos.x,pos.y,output)) = *newcol;
    }

}

int add_matrix(matrix* A, matrix* B, matrix* C){
    int i,j;
    if (A->x == B->x && A->y == B->y){
        for (i = 0; i < A->y; i++){
            for (j = 0; j < A->x; j++){
                C->values[i][j] = A->values[i][j] + B->values[i][j];
            }
        }
        
    }
    
}

int subtract_matrix(matrix* A, matrix* B, matrix* C){
    int i,j;
    if (A->x == B->x && A->y == B->y){
        for (i = 0; i < A->y; i++){
            for (j = 0; j < A->x; j++){
                C->values[i][j] = A->values[i][j] - B->values[i][j];
            }
        }
        
    }
}

int multiply_matrix(matrix* A, matrix* B, matrix* C){
    int i,j,k;
    
    if (A->x == B->y){
        init_matrix(C,B->x,A->y);
        for (i = 0; i < A->y; i++){
            for (j = 0; j < B->x; j++){
                C->values[i][j] = 0;
                for (k = 0; k < A->x; k++){
                    C->values[i][j] += A->values[i][k]*B->values[k][j];
                }                
            }
        }
    }
    
}

int matrix_rotation(float angx,float angy,float angz, matrix* rotX, matrix* rotY, matrix* rotZ){
    init_matrix(rotX,4,4);
    init_matrix(rotY,4,4);
    init_matrix(rotZ,4,4);
    rotX->values[3][3] = 1;
    rotY->values[3][3] = 1;
    rotZ->values[3][3] = 1;

    rotX->values[1][1] = cos(angx);
    rotX->values[1][2] = -sin(angx);
    rotX->values[2][1] = sin(angx);
    rotX->values[2][2] = cos(angx);
    rotX->values[0][0] = 1;


    rotY->values[0][0] = cos(angy);
    rotY->values[0][2] = -sin(angy);
    rotY->values[2][0] = sin(angy);
    rotY->values[2][2] = cos(angy);
    rotY->values[1][1] = 1;


    rotZ->values[0][0] = cos(angz);
    rotZ->values[0][1] = -sin(angz);
    rotZ->values[1][0] = sin(angz);
    rotZ->values[1][1] = cos(angz);
    rotZ->values[2][2] = 1;
}

int matrix_translation(float x, float y, float z, matrix* out){
    init_matrix(out,4,4);
    out->values[0][0] = 1;
    out->values[1][1] = 1;
    out->values[2][2] = 1;
    out->values[3][3] = 1;

    out->values[0][3] = x;
    out->values[1][3] = y;
    out->values[2][3] = z;
}

int matrix_expand(float x, float y, float z, matrix* out){
    init_matrix(out,4,4);
    out->values[0][0] = x;
    out->values[1][1] = y;
    out->values[2][2] = z;
    out->values[3][3] = 1;
}

int matrix_transform(matrix* translation, matrix* rotX, matrix* rotY, matrix* rotZ, matrix* expand, matrix* output){
    matrix mult[3];

    multiply_matrix(translation,rotX,&mult[0]);
    multiply_matrix(&mult[0],rotY,&mult[1]);
    multiply_matrix(&mult[1],rotZ,&mult[2]);

    multiply_matrix(&mult[2],expand,output);
}

int matrix_focal_X(int f, matrix* coor, matrix* out){
    matrix perspective;
    matrix mult;
    init_matrix(&perspective,4,4);
    perspective.values[0][0] = 1;
    perspective.values[1][1] = f;
    perspective.values[2][2] = f;
    perspective.values[3][0] = 1;
    
    multiply_matrix(&perspective, coor,&mult);
    multiply_const_matrix(&mult,1/coor->values[0][0],out);
}

int matrix_focal_Y(int f, matrix* coor, matrix* out){
    matrix perspective;
    matrix mult;
    init_matrix(&perspective,4,4);
    perspective.values[0][0] = f;
    perspective.values[1][1] = 1;
    perspective.values[2][2] = f;
    perspective.values[3][1] = 1;
    
    multiply_matrix(&perspective, coor,&mult);
    multiply_const_matrix(&mult,1/coor->values[1][0],out);
}

int matrix_focal_Z(int f, matrix* coor, matrix* out){
    matrix perspective;
    matrix mult;
    init_matrix(&perspective,4,4);
    perspective.values[0][0] = f;
    perspective.values[1][1] = f;
    perspective.values[2][2] = 1;
    perspective.values[3][2] = 1;
    multiply_matrix(&perspective, coor,&mult);
    multiply_const_matrix(&mult,1/coor->values[2][0],out);
}

int multiply_const_matrix(matrix* A, float B, matrix* out){
    int i,j;
    init_matrix(out,A->x,A->y);
    for (i = 0; i < A->y; i++){
        for (j = 0; j < A->x; j++){
            out->values[i][j] = A->values[i][j] * B;
        }
    }
    
}

void print_matrix(matrix* toprint){
    int i,j;
    printf("---------------------------\n");
    for (i = 0; i < toprint->y; i++){
        for (j = 0; j < toprint->x; j++){
            printf("%f ", toprint->values[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");
    
}

int init_matrix(matrix* A, int X, int Y){
    int i,j;
    
    A->x = X;
    A->y = Y;

    A->values = (float**)calloc(Y,sizeof(float*));
    for (i = 0; i < Y; i++){
        A->values[i] = (float*)calloc(X,sizeof(float));
        for (j = 0; j < X; j++){
            A->values[i][j] = 0;
        }
    }
    
}