#ifndef PPM_CREATOR_H
#define PPM_CREATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coordinates/coordinates.h"

#define X_SIZE 1366
#define Y_SIZE 768

#define BACKG 0
#define LINE 1
#define BACKG_V "255 255 255 "
#define LINE_V "0 0 0 "

#define PPM_CONFIG "P3 \n"


int create_image(raster*, color*);
int export_ppm(raster*, char*);

#endif