#include "lines_algorithms.h"

#include <math.h>
#include <pthread.h>

int get_firstoctant(int* swap, int* mirror, coordinate* pointa, coordinate* pointb){
    float m = 99;
    if (pointb->x != pointa->x){
        m = SLOPE_COOR_POIN(pointa,pointb);
    }

    //we need switch points?
    if (pointa->x > pointb->x){
        coordinate tmp = *pointa;
        *pointa = *pointb;
        *pointb = tmp;
        m = SLOPE_COOR_POIN(pointa,pointb);
    }

    
    //we need mirroring?
    if (m < 0){
        pointb->y += (pointa->y - pointb->y) *2;
        *mirror = 1;
        m = SLOPE_COOR_POIN(pointa,pointb);
    }

    //we need to swap the axis?
    if (m > 1){
        int tmp;
        tmp = pointa->x;
        pointa->x = pointa->y;
        pointa->y = tmp;
            
        tmp = pointb->x;
        pointb->x = pointb->y;
        pointb->y = tmp;
        *swap = 1;
        m = SLOPE_COOR_POIN(pointa,pointb);
    }

    //we need switch points?
    if (pointa->x > pointb->x){
        coordinate tmp = *pointa;
        *pointa = *pointb;
        *pointb = tmp;
        m = SLOPE_COOR_POIN(pointa,pointb);
    }
}
int inv_firstoctant(int* swap, int* mirror, coordinate** line, int* size){
    int i;
    if (*swap){
        int tmp;
        for ( i = 0; i < *size; i++){
            tmp = (*line +i)->x;
            (*line +i)->x = (*line +i)->y;
            (*line +i)->y = tmp;
        }
    }
    if (*mirror){
        for ( i = 0; i < *size; i++){
            (*line + i)->y -= ((*line + i)->y - (*line)->y)*2;
        }
    }
}


//corrct naive method
void* nai_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){
    coordinate tmp;

    if (pointa.x-pointb.x == 0){
        if (pointa.y < pointb.y){
            //advance_slope_vertical(&pointa, &pointb, line, size);
            int i;
            for ( i = pointa.y; i < pointb.y+1; i++){
                tmp.x = pointa.x;
                tmp.y = i;
                add_point_to_face(output,linecolor,tmp);
            }
        }else{
            //advance_slope_vertical(&pointb, &pointa, line, size);
            int i;
            for ( i = pointb.y; i < pointa.y+1; i++){
                tmp.x = pointb.x;
                tmp.y = i;
                add_point_to_face(output,linecolor,tmp);
            }
        }
    }else{
        float m = ((float)pointb.y-(float)pointa.y)/((float)pointb.x-(float)pointa.x);
        
        if ( m > 1 || m < -1){
            if (pointa.y < pointb.y){
                //get_line_1toinf(&m, &pointa, &pointb, line, size);
                int i;
                for ( i = pointa.y; i < pointb.y +1; i++){
                    tmp.x = (int)((i - pointa.y)/(m) + pointa.x);
                    tmp.y = i;
                    add_point_to_face(output,linecolor,tmp);
                }
            }else{
                //get_line_1toinf(&m, &pointb, &pointa, line, size);
                int i;
                for ( i = pointb.y; i < pointa.y +1; i++){
                    tmp.x = (int)((i - pointb.y)/(m) + pointb.x);
                    tmp.y = i;
                    add_point_to_face(output,linecolor,tmp);
                }
            }
        }else{
            if (pointa.x < pointb.x){
                //get_line_0to1(&m, &pointa, &pointb, line, size);
                int i;
                for ( i = pointa.x; i < pointb.x +1; i++){
                    tmp.x = i;
                    tmp.y = (int)((m)*(float)(i - pointa.x) + (pointa.y));
                    add_point_to_face(output,linecolor,tmp);
                }
            }else{
                //get_line_0to1(&m, &pointb, &pointa, line, size);
                int i;
                for ( i = pointb.x; i < pointa.x +1; i++){
                    tmp.x = i;
                    tmp.y = (int)((m)*(float)(i - pointb.x) + (pointb.y));
                    add_point_to_face(output,linecolor,tmp);
                }
            }
        }
    }
}
void* dda_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){
    float m;
    int swap = 0, mirror = 0;
    int size;
    coordinate tmp;
    coordinate *line;

    get_firstoctant(&swap, &mirror, &pointa, &pointb);

    size = pointb.x - pointa.x +1;
    line = (coordinate*)calloc(size, sizeof(coordinate));

    int i;
    float y = (float)pointa.y;
    m = ((float)pointb.y-(float)pointa.y)/((float)pointb.x-(float)pointa.x);
    for ( i = 0; i < size; i++){
        tmp.x = pointa.x + i;
        tmp.y = (int)(y);
        *(line + i) = tmp;
        y += m;
    }

    inv_firstoctant(&swap, &mirror, &line, &size);
    for (i = 0; i < size; i++){
        add_point_to_face(output,linecolor,*(line + i));
    }
}
void* bre_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){
    int swap = 0, mirror = 0;
    int size;
    coordinate tmp;
    coordinate *line;

    get_firstoctant(&swap, &mirror, &pointa, &pointb);

    size = pointb.x - pointa.x +1;
    line = (coordinate*)calloc(size, sizeof(coordinate));

    int i, d;
    int dy = pointb.y - pointa.y;
    int dx = pointb.x - pointa.x;
    int dupd1 = 2*dy;
    int dupd2 = 2*(dy - dx);

    d = 2*dy - dx;
    tmp = pointa;
    for ( i = 0; i < size; i++){
        *(line + i) = tmp;
        if(d < 0){
            //horinzontal
            tmp.x++;
            d += dupd1;
        }else{
            //vertical
            tmp.y++;
            tmp.x++;
            d += dupd2;
        }
    }
    inv_firstoctant(&swap, &mirror, &line, &size);
    for (i = 0; i < size; i++){
        add_point_to_face(output,linecolor,*(line + i));
    }
    
}

void* nai_thread(void *arguments){
    struct args *my_arguments = (struct args *)arguments;
    //nai_getline(my_arguments->output, my_arguments->pointa, my_arguments->pointb, my_arguments->linecolor);
}

//creates threads
int par_nai_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){
    struct args my_args;
    coordinate tmp_beg;
    coordinate tmp_end;
    int i;
    //my_args.output = output;
    //my_args.pointa = pointa;
    //my_args.pointb = pointb;
    //my_args.linecolor = linecolor;
    
    pthread_t process;
    
    pthread_create(&process,NULL,nai_thread,&my_args);
    
    
    pthread_getspecific(process);
}
int par_dda_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){

}
int par_bre_getline(figure* output, coordinate pointa, coordinate pointb, color* linecolor){
    
}
