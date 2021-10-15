#include "ppm_creator.h"
#include "line algorthms/lines_algorithms.h"
#include "obj files/obj.h"


int main(int argc, char** argv){
    if (argc > 2){
        printf("Too many arguments\n");
    }else if(argc < 2){
        printf("Not enogh arguments\n");
    }else{
        char buffer[255];
        FILE *toread;
        image output;
        color line;
        color background;
        int X_translation;
        int Y_translation;
        int Z_translation;
        float X_rotation;
        float Y_rotation;
        float Z_rotation;
        int X_expand;
        int Y_expand;
        int Z_expand;
        matrix expand;
        matrix tanslation;
        matrix rotationX;
        matrix rotationY;
        matrix rotationZ;
        matrix transformation;
        int focus;
        int f;
        int i;
        int images;


        toread = fopen(argv[1], "r");
        fscanf(toread, "%s", buffer);
        images = strtol(buffer, NULL, 10);
        for (i = 0; i < images; i++){
            fscanf(toread, "%s", buffer);
            output.x = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            output.y = strtol(buffer, NULL, 10);

            fscanf(toread, "%s", buffer);
            line.R = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            line.G = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            line.B = strtol(buffer, NULL, 10);

            fscanf(toread, "%s", buffer);
            background.R = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            background.G = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            background.B = strtol(buffer, NULL, 10);
            
            fscanf(toread, "%s", buffer);
            X_translation = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            Y_translation = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            Z_translation = strtol(buffer, NULL, 10);


            fscanf(toread, "%s", buffer);
            X_rotation = atof(buffer);
            fscanf(toread, "%s", buffer);
            Y_rotation = atof(buffer);
            fscanf(toread, "%s", buffer);
            Z_rotation = atof(buffer);


            fscanf(toread, "%s", buffer);
            X_expand = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            Y_expand = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            Z_expand = strtol(buffer, NULL, 10);

            create_image(&output,&background);

            fscanf(toread, "%s", buffer);
            focus = strtol(buffer, NULL, 10);
            fscanf(toread, "%s", buffer);
            f = strtol(buffer, NULL, 10);

            matrix_rotation(X_rotation,Y_rotation,Z_rotation,&rotationX,&rotationY,&rotationZ);
            matrix_translation(X_translation, Y_translation, Z_translation, &tanslation);
            matrix_expand(X_expand,Y_expand,Z_expand, &expand);
            matrix_transform(&tanslation, &rotationX, &rotationY, &rotationZ, &expand, &transformation);

            fscanf(toread, "%s", buffer);
            read_obj(buffer, &output, &line, &transformation, focus, f);
            fscanf(toread, "%s", buffer);
            export_ppm(&output, buffer);
        }
        fclose(toread);
    }
}
