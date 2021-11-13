#ifndef DDA_H
#define DDA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int x;
    int y;
} coordinate;

typedef struct {
  int R;
  int G;
  int B;
} color;

typedef struct{
    coordinate* position;
    color* color;
    int qpixel;
} figure;

typedef struct{
    color* img;
    int x;
    int y;
} raster;

typedef struct{
    float** values;
    int x;
    int y;
} matrix;

#define GET_POS_XY(X,Y,img) ( img->x*(img->y - Y -1) + (X) )


void add_point_to_face(figure* list, color* col_toadd, coordinate cor_toadd);
int add_point(raster*, coordinate, color*);
int add_matrix(matrix*, matrix*, matrix*);
int subtract_matrix(matrix*, matrix*, matrix*);
int multiply_matrix(matrix*, matrix*, matrix*);
int init_matrix(matrix*, int, int);
int matrix_rotation(float,float,float, matrix*, matrix*, matrix*);
int matrix_transform(matrix*, matrix*, matrix*, matrix*, matrix*, matrix*);
int matrix_expand(float, float, float, matrix*);
int matrix_translation(float, float, float, matrix*);
void print_matrix(matrix*);
int multiply_const_matrix(matrix* A, float B, matrix* out);
int matrix_focal_Z(int, matrix*, matrix*);
int matrix_focal_Y(int, matrix*, matrix*);
int matrix_focal_X(int, matrix*, matrix*);
#endif