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
        printf("on a bien eu le type %d", type);
        image->image->pbm->n_columns = columns;
        //image->image->pbm->n_lines = lines;
        //image->image->pbm->matrice = malloc(sizeof(int)*lines*columns);

        // if(image->image->pbm->matrice == NULL){
        //     free(image->image->pbm->matrice);
        //     free(image);
        //     printf("erreur encodage matrice");
        //     return NULL;
        // }
        break;
    }

//         break;
//     case 2:
//         printf("on a bien eu le type %d", type);

//         image->image->pgm->n_columns = columns;
//         image->image->pgm->n_lines = lines;
//         image->image->pgm->valeur_max = max_val;
//         image->image->pgm->matrice = malloc(sizeof(int)*lines*columns);

//         if(image->image->pgm->matrice == NULL){
//             free(image->image->pgm->matrice);
//             free(image);
//             return NULL;
//         }
//         break;
//     case 3:
//         printf("on a bien eu le type %d", type);

//         image->image->ppm->n_columns = columns;
//         image->image->ppm->n_lines = lines;
//         image->image->ppm->valeur_max = max_val;
//         image->image->ppm->matrice  = malloc(sizeof(RGB)*lines*columns);
//         if(image->image->ppm->matrice == NULL){
//             free(image->image->pgm->matrice);
//             free(image);
//             return NULL;
//         }

//     default:
//             printf("pourquoi defaut");
//             return NULL;
//         break;

//     return image;
//     }
        
    
// }
// static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image){
//     char buffer[BUFFERSIZE];
//     switch (type)
//     {
//     case 1:
//         pass_comment(fic, buffer);
//         for(int i = 0; i<lines; i++){
//             for(int j =0; i<columns; i++){
//                 sscanf("%d", &image->image->pbm->matrice[i][j]);
//             }
//         }
//         break;
    
//     default:
//         break;
//     }
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
    printf("before\n");
    int type = get_type(fic, buffer);
    printf("after\n");
    printf("type %d ok\n", type);
    int lines;
    int columns;


    
    pass_comment(fic, buffer);
    if(type == 1){
        printf("traitement du fichier pbm\n");
        sscanf(buffer, "%d %d", &lines, &columns);
        printf("lines :%d columns :%d\n", lines, columns);
        if(lines >0 && columns >0){
        *image = build_PNM(1, lines, columns, 0);
        //fill_matrix(1, lines, columns, fic, *image);
        

            }
        }

    fclose(fic);
   return *image;
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
    printf("%d", image->image->ppm->n_lines);

    // for(int i = 0; i<image->image->ppm->n_lines; i++){
    //     for(int j = 0; j<image->image->ppm->n_columns ; j++){
    //         printf("%d", image->image->ppm->matrice[i][j]);
    //     }
    //     printf("/n");
    //}
}

