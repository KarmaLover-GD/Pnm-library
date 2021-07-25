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
#define BUFFERSIZE 512
/**
 * Définition de la structure RGB
 *
 */

typedef struct{
   int triplet[3]; // triplet RGB , 0-> rouge 1->vert 2->bleu
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
    unsigned int **matrice
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
   PBM *pbm;
   PGM *pgm;
   PPM *ppm;
}pnm;
/**
 * Définition du type opaque PNM
 *
 */


struct PNM_t {
    pnm *image;
};


int load_pnm(PNM **image, char* filename) {
    assert(filename != NULL && image != NULL);

    FILE *fic = fopen(filename, "r");
    if (fic == NULL){
        fclose(fic);
        printf("erreur à l'ouverture du fic");
        return -2;
    }
    

    char buffer[BUFFERSIZE];

    pass_comment(fic, buffer);

    int type = get_type(fic);
    int lines;
    int columns;


    
    
    if(type == 1){
        sscanf(fic, "%d %d", lines, columns);
        if(lines >0 && columns >0){
        *image = build_PNM(1, lines, columns, 0);
        fill_matrix(1, lines, columns, fic, *image);
        

            }
        }

    fclose(fic);
   return 0;
}

int write_pnm(PNM *image, char* filename) {

   /* Insérez le code ici */

   return 0;
}

static char *get_type(FILE* fic) {

    char* buffer[BUFFERSIZE];
    signed char n_magique[200];
    pass_comment(fic, buffer);
    while (fgets(n_magique, 200, fic) != NULL) {
        if (strcmp(fgets(n_magique, 200, fic), "P1") == 0) {
            return 1;
        } else if (strcmp(fgets(n_magique, 200, fic), "P2") == 0) {
            return 2;
        } else if (strcmp(fgets(n_magique, 200, fic), "P3") == 0) {
            return 3;
        } else
            return 0;

    }
    fclose(fic);
}

static int check_extension(){
    return 1;
}

static void pass_comment(FILE *fic, char*buffer){
   assert(fic != NULL && buffer != NULL);

   do
   fgets(buffer, 100, fic);
   while(strncmp(buffer, "#", 1) == 0);
   
}

static PNM *build_PNM(int type, int lines, int columns, int max_val){

    PNM *image = malloc(sizeof(PNM));

    if(image == NULL){
        return NULL;
    }
    
    switch (type)
    {
    case 1:
        image->image->pbm->n_columns = columns;
        image->image->pbm->n_lines = lines;
        image->image->pbm->matrice = malloc(sizeof(int)*lines*columns);

        if(image->image->pbm->matrice == NULL){
            free(image->image->pbm->matrice);
            free(image);
            return NULL;
        }

        break;
    case 2:
        image->image->pgm->n_columns = columns;
        image->image->pgm->n_lines = lines;
        image->image->pgm->valeur_max = max_val;
        image->image->pgm->matrice = malloc(sizeof(int)*lines*columns);

        if(image->image->pgm->matrice == NULL){
            free(image->image->pgm->matrice);
            free(image);
            return NULL;
        }
        break;
    case 3:
        image->image->ppm->n_columns = columns;
        image->image->ppm->n_lines = lines;
        image->image->ppm->valeur_max = max_val;
        image->image->ppm->matrice  = malloc(sizeof(RGB)*lines*columns);
        if(image->image->ppm->matrice == NULL){
            free(image->image->pgm->matrice);
            free(image);
            return NULL;
        }

    default:
            return NULL;
        break;

    return image;
    }
        
    
}

static PNM **fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image){
    char buffer[BUFFERSIZE];
    switch (type)
    {
    case 1:
        pass_comment(fic, buffer);
        for(int i = 0; i<lines; i++){
            for(int j =0; i<columns; i++){
                sscanf("%d", &image->image->pbm->matrice[i][j]);
            }
        }
        break;
    
    default:
        break;
    }
    return &image;
}

void display_content(int type, PNM *image){
    for(int i = 0; i<image->image->ppm->n_lines){
        for(int j = 0; j<image->image->ppm->n_columns){
            printf("%d", image->image->ppm->matrice[i][j]);
        }
        printf("/n");
    }
}

