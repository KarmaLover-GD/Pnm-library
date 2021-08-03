/**
 * pnm.c
 * 
 * Ce fic contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Nom Prenom Matricule
 * @date: 
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#define BUFFERSIZE 1024
/**
 * Définition de la structure RGB
 *
 */

typedef struct{
   int red;
   int green;
   int blue;// triplet RGB , 0-> rouge 1->vert 2->bleu
}RGB;





/**
 * Définition du type opaque PBM
 *
 */

typedef struct{
    char *n_magique;
    unsigned int n_columns;
    unsigned int n_lines;
    unsigned int **matrice; 
}PBM;
/**
 * Définition du type opaque PGM
 *
 */

typedef struct{
    char *n_magique;
    unsigned int n_columns;
    unsigned int n_lines;
    unsigned int valeur_max;
    unsigned int **matrice;
}PGM;
/**
 * Définition du type opaque PPM
 *
 */
typedef struct{
    char *n_magique;
    unsigned int n_columns;
    unsigned int n_lines;
    unsigned int valeur_max;
    RGB **matrice;
}PPM;

 typedef union{
   RGB** matrice_color;
   int **matrice_black;
}arraytype;
/**
 * Définition du type opaque PNM
 *
 */


struct PNM_t {
    int lines;
    int columns;
    int max_value;
    int type;
    RGB **matrice_rgb;
    int **matrice_black;
    
};
static void pass_comment(FILE *fic, char*buffer){
   assert(fic != NULL && buffer != NULL);

   do
   fgets(buffer, 100, fic);
   while(strncmp(buffer, "#", 1) == 0);
   
}

static int get_type(FILE* fic, char *buffer) {

    pass_comment(fic, buffer);

        if (strncmp(buffer, "P1", 2) == 0) {
            printf("type pbm\n");
            printf("%s", buffer);
            return 1;
        } else if (strncmp(buffer, "P2", 2) == 0) {
            printf("type pgm\n");
            printf("%s", buffer);
            return 2;
        } else if (strncmp(buffer, "P3", 2) == 0) {
            printf("type ppm\n");
            printf("%s", buffer);
            return 3;
        } else
            printf("unknown type");
            printf("%s", buffer);
            return 0;

    
    fclose(fic);
}



static PNM *build_PNM(int type, int lines, int columns, int max_val){
    
    PNM *image = malloc(sizeof(PNM));
    
     if(image == NULL){
         printf("erreur allocation");
         return NULL;
     }
    
    switch (type)
    {
    case 1:

        image->lines = lines;
        image->type = type;
        image->columns = columns;
        printf(" les différents champs ont bien étés remplis %d %d %d\n", image->columns, image->lines, image->type);
        image->matrice_black = malloc(sizeof(int)*2*lines);
        for(int i = 0; i<lines; i++){
            image->matrice_black[i] = malloc(sizeof(int)*columns);
        }
        
        
       
        
        if(image->matrice_black == NULL){
        for(int i =0; i<lines; i++){
            free(image->matrice_black[i]);
        }
            free(image);
            printf("erreur encodage matrice");
            return NULL;
        }
        break;
    


    case 2: ;
        
        char buffer[BUFFERSIZE];
        int max_val; 

        image->columns = columns;
        image->lines = lines;
       
        image->max_value = max_val;
        image->matrice_black = malloc(sizeof(int)*2*lines);
        for(int i = 0; i<lines; i++){
            image->matrice_black[i] = malloc(sizeof(int)*columns);
        }
        
        
        if(image->matrice_black == NULL){
            for(int i =0; i<lines; i++){
                free(image->matrice_black[i]);
                }
            free(image);
            printf("erreur encodage matrice");
            return NULL;
        }

        break;

    case 3: ;

       
        image->columns = columns;
        image->lines = lines;
        image->max_value = max_val;
           image->matrice_rgb = malloc(sizeof(RGB)*lines);
          for(int i = 0; i<lines; i++){
            image->matrice_rgb[i] = malloc(sizeof(RGB)*columns);
        }
        
        
        if(image->matrice_rgb == NULL){
            for(int i =0; i<lines; i++){
                free(image->matrice_rgb[i]);
                }
            free(image);
            printf("erreur encodage matrice");
            return NULL;
        }

    }
    return image;
     }
        
    

static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image){
    char buffer[BUFFERSIZE];
    unsigned int pixel;
    unsigned int red, green, blue;
    unsigned int buffer_counter = 0;
    switch (type)
    {
    case 1:

        //pass_comment(fic, buffer);
       
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d ", &pixel);
    
                image->matrice_black[i][j] = pixel;
                 if(i == lines-1 && j> columns -5){
                     printf("%u",image->matrice_black[i][j]);
                }
            }
        }
        break;
    case 2:
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d ", &pixel);
              
            
                image->matrice_black[i][j] = pixel;
                 if(i == lines-1 && j > columns -5){
                   printf("%u ",image->matrice_black[i][j]);
                }
            }
        }
        break;
    case 3:
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d %d %d ", &red, &green, &blue);
                printf(" %d %d %d", red, green, blue);
              
                //printf(" (%d, %d, %d)", red, green, blue);
                image->matrice_rgb[i][j].red = red;
                image->matrice_rgb[i][j].green = green;
                image->matrice_rgb[i][j].blue = blue;
                
                 if(i == lines-1 && j> columns -5){
                     printf("%u",image->matrice_black[i][j]);
                }
            }
        }
    
    default:
        break;
    }
    return image;
}

int load_pnm(PNM **image, char* filename) {
    assert(filename != NULL && image != NULL);

    FILE *fic = fopen(filename, "r");
    if (fic == NULL){
        fclose(fic);
        printf("erreur à l'ouverture du fic");
        return -2;
    }
    

    char buffer[BUFFERSIZE];
   
    int type = get_type(fic, buffer);
    printf("type %d ok\n", type);
    int lines;
    int columns;
    int max_val;


    
    pass_comment(fic, buffer);
    if(type == 1){
        printf("traitement du fichier pbm\n");
        sscanf(buffer, "%d %d", &lines, &columns);
        printf("lines :%d columns :%d\n", lines, columns);
        if(lines >0 && columns >0){
        *image = build_PNM(type, lines, columns, fic);
        fill_matrix(type, lines, columns, fic, *image);
        
    
            }
        }else if(type == 2){
            printf("traitement du fichier ppm\n");
            sscanf(buffer, "%d %d", &lines, &columns);
            printf("lines :%d columns :%d\n", lines, columns);
            pass_comment(fic, buffer);
            sscanf(buffer, "%d", &max_val);
            printf("ON A MAXVAL QUI EST DE  %d\n", max_val);

            if(lines >0 && columns >0){
                *image = build_PNM(type, lines, columns, fic);
            fill_matrix(type, lines, columns, fic, *image);
            }
        }else if(type == 3){
                printf("traitement du fichier ppm\n");
            sscanf(buffer, "%d %d", &lines, &columns);
            printf("lines :%d columns :%d\n", lines, columns);
            pass_comment(fic, buffer);
            sscanf(buffer, "%d", &max_val);
            printf("valeur max : %d", max_val);


            if(lines >0 && columns >0){
            *image = build_PNM(type, lines, columns, fic);
            fill_matrix(type, lines, columns, fic, *image);
            }
        }


    fclose(fic);

   return 0;
}

int write_pnm(PNM *image, char* filename) {

   /* Insérez le code ici */

   return 0;
}



static int check_extension(){
    return 1;
}






void display_content(int type, PNM *image){
    assert(image != NULL);
    printf("yep");
    //printf("%d", image->n_lines);

    // for(int i = 0; i<image->image->ppm->n_lines; i++){
    //     for(int j = 0; j<image->image->ppm->n_columns ; j++){
    //         printf("%d", image->image->ppm->matrice[i][j]);
    //     }
    //     printf("/n");
    //}
}


void destroy_pnm(PNM *image){
    assert(image != NULL);
    switch(image->type){

        case 1:
    //printf("image content : %d, %d, %d, %d", image->type, image->lines, image->columns, image->matrice_black[0][2]);

            for(int i =0; i<image->lines; i++){
                free(image->matrice_black[i]);
            }
            free(image->matrice_black);
            free(image);

            break;
        case 2:
            
            for(int i =0; i<image->lines; i++){
                free(image->matrice_black[i]);
            }
            free(image->matrice_black);
            free(image);

            break;
        case 3:

            for(int i = 0; i<image->lines; i++){
                free(image->matrice_rgb[i]);
            }
            free(image->matrice_rgb);
            free(image);

            break;
        default:
            break;

    }

}
