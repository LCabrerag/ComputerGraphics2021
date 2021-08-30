#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define X_SIZE 1366
#define Y_SIZE 768
#define WHITE "255 255 255 "
#define BLACK "0 0 0 "
#define PPM_CONFIG "P3 \n1366 768\n255 \n "

struct vector{
    double x;
    double y;
};



int main(){
    //declare variables
    FILE *image;
    int i,j,isline, input;
    struct vector point1,point2,unit;
    double count;

    //calculate the unitary vector
    printf("introduce x1: \n");
    scanf("%d", &input);
    point1.x = (double)input;


    printf("introduce y1: \n");
    scanf("%d", &input);
    point1.y = (double)input;

    printf("introduce x2: \n");
    scanf("%d", &input);
    point2.x = (double)input;

    printf("introduce y2: \n");
    scanf("%d", &input);
    point2.y = (double)input;

    
    if (point1.x == point2.x && point1.y == point2.y){
        unit.x = 0;
        unit.y = 0;
    }else{
        unit.x = (point2.x - point1.x)/sqrt(pow(point2.x - point1.x,2)+pow(point2.y - point1.y,2));
        unit.y = (point2.y - point1.y)/sqrt(pow(point2.x - point1.x,2)+pow(point2.y - point1.y,2));
    }
    

    //open image and write the header of ppm
    image = fopen("test.ppm", "w+");
    fputs(PPM_CONFIG,image);

    
    //analice every pixel
    //x => j
    //y => i
    for (i = 0; i < Y_SIZE; i++){
        for (j = 0; j < X_SIZE; j++){
            isline = 0;
            count = 0;
            
            //if the unit vector pass throgh the pixel
            //we add a black pixel
            //line is used as a boolean
            do{

                count += 1;
                // point1 + (c)unit = actual_pixel
                if (round(point1.x + (unit.x*count)) == j &&
                 round(point1.y + (unit.y*count)) == i){
                    isline = 1;
                }
                
            }while((round(point1.x + (unit.x*count)) != point2.x ||
                 round(point1.y + (unit.y*count)) != point2.y));
            
            
            if (isline){
                fputs(BLACK, image);
            }else{
                fputs(WHITE, image);
            }

        }
    }
    
    printf("Done!\n");
    fclose(image);

    return 0;
}