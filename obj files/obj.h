#ifndef OBJ
#define OBJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coordinates/coordinates.h"
#include "../line algorthms/lines_algorithms.h"

typedef struct{
    int a;
    int b;
} line_points;

#define PARALLEL 0
#define X_FOCUS 1
#define Y_FOCUS 2
#define Z_FOCUS 3

int read_obj(char*, image*, color*, matrix*, int, int );
int find_vortex(int*, coordinate*);
void *read100(void *);
#endif
