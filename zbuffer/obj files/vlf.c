#include "vlf.h"

char* vlf_vertex;
char* vlf_edge;
char* vlf_face;
int face_numer=0;


int obj_to_vlf(char* obj_name, char* vertex_file, char* edge_file, char* face_file){
    // v {x y z w}
    // vp {u v w}
    // vn {i j k}
    // vt {u v w}
    // f {v/vt/vn v/vt/vn v/vt/vn}

    FILE* obj;
    FILE* vlf;
    vlf_vertex = vertex_file;
    vlf_edge = edge_file;
    vlf_face = face_file;


    int cara[5],lados=0,position=0;
    int positionedge = 0;
    int positionface = 0;
    char buffer[255];
    char type = 'd';
    int i;
    obj = fopen(obj_name, "r");
    vlf = fopen(vlf_vertex, "w");

    //vertex
    while (fscanf(obj, "%s", buffer) != EOF){
        if(strcmp(buffer, "v") == 0){
            type = 'v';
            fputs("\nv ",vlf);
        }else if(strcmp(buffer, "f") == 0){
            type = 'f';
        }else if(type == 'v'){
            fputs(buffer,vlf);
            fputs(" ",vlf);
        }
    }

    fclose(vlf);
    vlf = fopen(vlf_edge, "w");
    rewind(obj);
    type = 'd';

    //edges
    while (fscanf(obj, "%s", buffer) != EOF){
        if(strcmp(buffer, "v") == 0){
            if (type == 'f'){
                for (i = 0; i < lados-1; i++){
                    if (edge_exist(cara[i],cara[i+1],obj_name) == position){
                        sprintf(buffer, "\nE %d %d",cara[i],cara[i+1]);
                        fputs(buffer,vlf);
                    }
                }
                for (i = 2; i < lados-1; i++){
                    if (edge_exist(cara[0],cara[i],obj_name) == position){
                        sprintf(buffer, "\nE %d %d",cara[0],cara[i]);
                        fputs(buffer,vlf);
                    }
                }
                if (edge_exist(cara[0],cara[lados-1],obj_name) == position){
                    sprintf(buffer, "\nE %d %d",cara[0],cara[lados-1]);
                    fputs(buffer,vlf);
                }
            }
            type = 'v';
        }else if(strcmp(buffer, "f") == 0){
            if (type == 'f'){
                for (i = 0; i < lados-1; i++){
                    if (edge_exist(cara[i],cara[i+1],obj_name) == position){
                        sprintf(buffer, "\nE %d %d",cara[i],cara[i+1]);
                        fputs(buffer,vlf);
                    }
                }
                for (i = 2; i < lados-1; i++){
                    if (edge_exist(cara[0],cara[i],obj_name) == position){
                        sprintf(buffer, "\nE %d %d",cara[0],cara[i]);
                        fputs(buffer,vlf);
                    }
                }
                if (edge_exist(cara[0],cara[lados-1],obj_name) == position){
                    sprintf(buffer, "\nE %d %d",cara[0],cara[lados-1]);
                    fputs(buffer,vlf);
                }
            }
                
            position++; 
            type = 'f';
            lados = 0;
            
        }else if(type == 'f'){
            cara[lados] = atof(buffer);
            lados++;
        }
    }
    if (type == 'f'){
        for (i = 0; i < lados-1; i++){
            if (edge_exist(cara[i],cara[i+1],obj_name) == position){
                sprintf(buffer, "\nE %d %d",cara[i],cara[i+1]);
                fputs(buffer,vlf);
            }
        }
        for (i = 2; i < lados-1; i++){
            if (edge_exist(cara[0],cara[i],obj_name) == position){
                sprintf(buffer, "\nE %d %d",cara[0],cara[i]);
                fputs(buffer,vlf);
            }
        }
        if (edge_exist(cara[0],cara[lados-1],obj_name) == position){
            sprintf(buffer, "\nE %d %d",cara[0],cara[lados-1]);
            fputs(buffer,vlf);
        }
        
    }
    

    fclose(vlf);
    vlf = fopen(vlf_face, "w");
    rewind(obj);
    type = 'd';
    
    //faces
    while (fscanf(obj, "%s", buffer) != EOF){
        if(strcmp(buffer, "v") == 0){
            if (type == 'f'){
                for (i = 1; i < lados-1; i++){
                    sprintf(buffer, "F %d %d %d\n",get_edge_vlf_vetex(cara[0],cara[i+1]),get_edge_vlf_vetex(cara[i],cara[0]),get_edge_vlf_vetex(cara[i],cara[i+1]));
                    fputs(buffer,vlf);
                    face_numer++;
                }
            }
            type = 'v';
        }else if(strcmp(buffer, "f") == 0){
            
            if (type == 'f'){
                for (i = 1; i < lados-1; i++){
                    sprintf(buffer, "F %d %d %d\n",get_edge_vlf_vetex(cara[0],cara[i+1]),get_edge_vlf_vetex(cara[i],cara[0]),get_edge_vlf_vetex(cara[i],cara[i+1]));
                    fputs(buffer,vlf);
                    face_numer++;
                }
            }
            
            position++; 
            type = 'f';
            lados = 0;
            
        }else if(type == 'f'){
            cara[lados] = atof(buffer);
            lados++;
        }
    }
    if (type == 'f'){
        
        for (i = 1; i < lados-1; i++){
            sprintf(buffer, "F %d %d %d\n",get_edge_vlf_vetex(cara[0],cara[i+1]),get_edge_vlf_vetex(cara[i],cara[0]),get_edge_vlf_vetex(cara[i],cara[i+1]));
            fputs(buffer,vlf);
            face_numer++;
        }
    }
    
    
    
    fclose(obj);
    fclose(vlf);
}

int edge_exist(int v1, int v2, char* file){
    
    int positionf = 0;
    int outf = 0;
    int i;
    char buffer[255];
    FILE* toread;
    char type = 'd';
    int lados;
    int cara[5];
    toread = fopen(file, "r");

    while (fscanf(toread, "%s", buffer) != EOF){
        if(strcmp(buffer, "f") == 0){
            if (type == 'f' && outf == 0){
                
                for (i = 0; i < lados-1; i++){
                    if ( (cara[i] == v1 && cara[i+1] == v2) || (cara[i] == v2 && cara[i+1] == v1) ){
                        outf = positionf;
                    }
                }
                for (i = 2; i < lados-1; i++){
                    if ( (cara[0] == v1 && cara[i] == v2) || (cara[0] == v2 && cara[i] == v1) ){
                        outf = positionf;
                    }
                }
                if ( (cara[0] == v2 && cara[lados-1] == v1) || (cara[lados-1] == v2 && cara[0] == v1) ){
                    outf = positionf;
                }
            }
            positionf++;            
            type = 'f';
            lados = 0;
        }else if(type == 'f'){
            cara[lados] = atof(buffer);
            lados++;
        }
        
    }
    
    if (type == 'f' && outf == 0){
        
        for (i = 0; i < lados-1; i++){
            if ( (cara[i] == v1 && cara[i+1] == v2) || (cara[i] == v2 && cara[i+1] == v1) ){
                outf = positionf;
            }
        }
        for (i = 2; i < lados-1; i++){
            if ( (cara[0] == v1 && cara[i] == v2) || (cara[0] == v2 && cara[i] == v1) ){
                outf = positionf;
            }
        }
        if ( (cara[0] == v1 && cara[lados-1] == v2) || (cara[lados-1] == v2 && cara[0] == v1) ){
            outf = positionf;
        }
    }

    fclose(toread);
    return outf;
}

vertex get_vertex_vlf(int position){
    FILE* vlf;
    vlf = fopen(vlf_vertex,"r");
    char buffer[255];
    int count = 0;
    vertex out;

    while (fscanf(vlf, "%s", buffer) != EOF){
        if (strcmp(buffer, "v") == 0){
            count++;
        } else if(count == position){
            out.x = atof(buffer);
            fscanf(vlf, "%s", buffer);
            out.y = atof(buffer);
            fscanf(vlf, "%s", buffer);
            out.z = atof(buffer);
            break;
        }
    }
    fclose(vlf);
    return out;
}

int get_edge_vlf_vetex(int v1, int v2){
    FILE* vlf;
    int tmp1,tmp2;
    char buffer[255];
    int out = 0;
    vlf = fopen(vlf_edge,"r");
    while (fscanf(vlf, "%s", buffer) != EOF){
        if (strcmp(buffer,"E") == 0){
            out++;
            fscanf(vlf, "%s", buffer);
            tmp1 = atoi(buffer);
            fscanf(vlf, "%s", buffer);
            tmp2 = atoi(buffer);
            if ((v1 == tmp1 && v2 == tmp2) || (v2 == tmp1 && v1 == tmp2)){
                return out;
            }
        }
    }
    
}

edge get_edge_vlf(int position){
    FILE* vlf;
    vlf = fopen(vlf_edge,"r");
    char buffer[255];
    int count = 0;
    edge out;

    while (fscanf(vlf, "%s", buffer) != EOF){
        if (strcmp(buffer, "E") == 0){
            count++;
        } else if(count == position){
            out.begin = get_vertex_vlf(atoi(buffer));
            fscanf(vlf, "%s", buffer);
            out.end = get_vertex_vlf(atoi(buffer));
            break;
        }
    }
    fclose(vlf);
    return out;
}

face get_face_vlf(int position){

    FILE* vlf;
    vlf = fopen(vlf_face,"r");
    char buffer[255];
    int count = 0;
    face out;

    while (fscanf(vlf, "%s", buffer) != EOF){
        if (strcmp(buffer, "F") == 0){
            count++;
        } else if(count == position){
            out.one = get_edge_vlf(atoi(buffer));
            fscanf(vlf, "%s", buffer);
            out.two = get_edge_vlf(atoi(buffer));
            fscanf(vlf, "%s", buffer);
            out.three = get_edge_vlf(atoi(buffer));
            break;
        }
    }
    fclose(vlf);
    return out;
}
