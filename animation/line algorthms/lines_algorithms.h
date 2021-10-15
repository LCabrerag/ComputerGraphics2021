#ifndef LINES_ALGORITHMS
#define LINES_ALGORITHMS


#include "../coordinates/coordinates.h" //import coordinates struct and methods
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>


//MACROS
struct args{
    image* output;
    coordinate pointa;
    coordinate pointb;
    color* linecolor;
};

//slope form uses two coordinates
#define SLOPE_COOR(poina,poinb) ((float)poinb.y-(float)poina.y)/((float)poinb.x-(float)poina.x)
#define SLOPE_COOR_POIN(poina,poinb) ((float)poinb->y-(float)poina->y)/((float)poinb->x-(float)poina->x)

//methods to get the line on the 1st octant
int mirroring(coordinate*, coordinate*);    //invert de y axis
int swap_axis(coordinate*, coordinate*);    //swap the axis
int swap_points(coordinate*, coordinate*);  //switch points A -> B and B -> A 

//methods to translate 1st octant line to other octants
int inv_mirroring(coordinate**,int*);    //invert de y axis
int inv_swap_axis(coordinate**,int*);    //swap the axis

int get_firstoctant(int*, int*, coordinate*, coordinate*);
int inv_firstoctant(int*, int*, coordinate**, int*);

//methods to get a line
void* nai_getline(image*, coordinate, coordinate, color*); //naive algorithm
void* dda_getline(image*, coordinate, coordinate, color*); //dda algorithm
void* bre_getline(image*, coordinate, coordinate, color*); //bresenham algorithm

//parallel
int par_nai_getline(image*, coordinate, coordinate, color*);
int par_dda_getline(image*, coordinate, coordinate, color*);
int par_bre_getline(image*, coordinate, coordinate, color*);


#endif
