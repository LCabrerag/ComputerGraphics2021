#include <stdio.h>

int main(){
    int x1 = 2;
    int y1 = 6;

    int x2 = 12;
    int y2 = 2;

    double xtmp = x1;
    double ytmp = y1;
    
    int xend = x1;
    int yend = y1;

    // formula de la recta y - y1 = m ( x - x1 )
    double m = ((double)y2 - (double)y1)/((double)x2 - (double)x1);
    
    printf("X Y\n");
    printf("%d %d\n", x1, y1);
    
    while ((int)xend != x2 && (int)yend != y2){
        if (x1 < x2){
            xtmp += .1;
            ytmp = m*(xtmp - (double)x1) + (double)y1;
        }
        if (x1 == x2){
            ytmp++;
        }
        if (x1 > x2){
            xtmp -= .1;
            ytmp = m*(xtmp - (double)x1) + (double)y1;
            
        }
        printf("%d %d\n", (int)xtmp, (int)ytmp);
        
        if ((int)xtmp != xend && (int)ytmp != yend){
            xend = (int)xtmp;
            yend = (int)ytmp;
            printf("%d %d\n", xend, yend);
        }
    
    }
    

    return 0;
}
