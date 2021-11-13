#include "obj.h"

matrix* transformation;
char* filename;
int focal;
int f_global;

int read_obj(char* obj_file, image* output, color* objcolor, matrix* transf, int focaltype, int f){
    focal = focaltype;
    f_global = f;
    transformation = transf;

    obj_to_vlf(obj_file,"vertex.txt","edges.txt","faces.txt");
    face to_draw;

    int i;
    for ( i = 0; i < face_numer; i++){
        to_draw = get_face_vlf(i+1);
        draw_face(to_draw,objcolor,output);
    }
}

int draw_face(face to_draw, color* lines,image* output){
    int i;
    draw_edge(output, lines, to_draw.one);
    draw_edge(output, lines, to_draw.two);
    draw_edge(output, lines, to_draw.three);

}

int draw_edge(image* output, color* line_color, edge to_add){
    matrix pointa;
    matrix pointb;
    matrix pointa_transformed;
    matrix pointb_transformed;
    coordinate bline;
    coordinate eline;

    init_matrix(&pointa,1,4);
    init_matrix(&pointb,1,4);

    pointa.values[0][0] = to_add.begin.x;
    pointa.values[1][0] = to_add.begin.y;
    pointa.values[2][0] = to_add.begin.z;
    pointa.values[3][0] = 1;
    pointb.values[0][0] = to_add.end.x;
    pointb.values[1][0] = to_add.end.y;
    pointb.values[2][0] = to_add.end.z;
    pointb.values[3][0] = 1;
    multiply_matrix(transformation, &pointa, &pointa_transformed);
    multiply_matrix(transformation, &pointb, &pointb_transformed);
    switch (focal){
        case X_FOCUS:        
            matrix_focal_X(f_global,&pointa_transformed,&pointa);
            bline.x = pointa.values[1][0];
            bline.y = pointa.values[2][0];
            matrix_focal_X(f_global,&pointb_transformed,&pointb);
            eline.x = pointb.values[1][0];
            eline.y = pointb.values[2][0];
            break;
        case Y_FOCUS:
            matrix_focal_Y(f_global,&pointa_transformed,&pointa);
            bline.x = pointa.values[0][0];
            bline.y = pointa.values[2][0];
            matrix_focal_Y(f_global,&pointb_transformed,&pointb);
            eline.x = pointb.values[0][0];
            eline.y = pointb.values[2][0];
            break;
        case Z_FOCUS:
            matrix_focal_Z(f_global,&pointa_transformed,&pointa);
            bline.x = pointa.values[0][0];
            bline.y = pointa.values[1][0];
            matrix_focal_Z(f_global,&pointb_transformed,&pointb);
            eline.x = pointb.values[0][0];
            eline.y = pointb.values[1][0];
            break;
        default:
            bline.x = pointa_transformed.values[0][0];
            bline.y = pointa_transformed.values[1][0];
            eline.x = pointb_transformed.values[0][0];
            eline.y = pointb_transformed.values[1][0];
            break;
    }
    bre_getline(output, bline, eline, line_color);
    
}

