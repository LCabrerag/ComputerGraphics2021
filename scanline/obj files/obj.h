#ifndef OBJ
#define OBJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coordinates/coordinates.h"
#include "../line algorthms/lines_algorithms.h"
#include "vlf.h"

typedef struct{
    int a;
    int b;
} line_points;

#define PARALLEL 0
#define X_FOCUS 1
#define Y_FOCUS 2
#define Z_FOCUS 3

int read_obj(char*, raster*, color*, color*, matrix*, int, int);
int draw_face(face to_draw, color* lines, color* face,raster* output);
int draw_edge(figure* list, color* line_color, edge to_add);
void init_figure(figure* toinit);
void scanline_figure(figure* destination, color* background,raster* output);

#endif
