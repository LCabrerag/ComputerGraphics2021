#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    float x;
    float y;
    float z;
} vertex;

typedef struct{
    vertex begin;
    vertex end;
} edge;

typedef struct{
    edge one;
    edge two;
    edge three;
} face;

int obj_to_vlf(char*, char*, char*, char*);
int edge_exist(int, int, char*);
vertex get_vertex_vlf(int);
int get_edge_vlf_vetex(int, int);
edge get_edge_vlf(int);
face get_face_vlf(int);