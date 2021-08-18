#include <stdio.h>
#include <math.h>

int main(){
    int x1 = 2;
    int y1 = 6;

    int x2 = 12;
    int y2 = 6;

    double xtmp = x1;
    double ytmp = y1;
    
    int xend = x1;
    int yend = y1;
    
    double m = 0;

    
    
    
    printf("X Y\n");
    printf("%d %d\n", x1, y1);
    
    if(y2 != y1){
        // Slope m  = (y2 - y1)/(x2 - x1) 
        m = ((double)y2 - (double)y1)/((double)x2 - (double)x1);
        while (xend != x2 || yend != y2){
            if (x1 < x2){
                xtmp += .1;
                // formula de la recta y = m ( x - x1 ) + y1
                ytmp = m*(xtmp - (double)x1) + (double)y1;
            }
            if (m == 0){
                ytmp++;
            }
            if (x1 > x2){
                xtmp -= .1;
                // formula de la recta y = m ( x - x1 ) + y1
                ytmp = m*(xtmp - (double)x1) + (double)y1;
                
            }
            if ( round(xtmp) != xend || round(ytmp) != yend){
                xend = round(xtmp);
                yend = round(ytmp);
                printf("%d %d\n", xend, yend);
            }
        
        }
    }else{
        while (xend != x2){
            xend += 1.0;
            printf("%d %d\n", xend, yend);
        }
        
    }
    

    return 0;
}
    
