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
            printf("%s", buffer);
            return 1;
        } else if (strncmp(buffer, "P2", 2) == 0) {
            printf("%s", buffer);
            return 2;
        } else if (strncmp(buffer, "P3", 2) == 0) {
            printf("%s", buffer);
            return 3;
        } else
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
       

        image->columns = columns;
        image->lines = lines;
        image->type = type;

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
        image->type = type;
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
                
            }
        }
        break;
    case 2:
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d ", &pixel);
              
            
                image->matrice_black[i][j] = pixel;
              
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
    //printf("Filename : %s", filename);
    FILE *fic = fopen(filename, "r");
    if (fic == NULL){
        fclose(fic);
        printf("erreur à l'ouverture du fic");
        return -2;
    }
    

    char buffer[BUFFERSIZE];
   
    int type = get_type(fic, buffer);
   
    int lines;
    int columns;
    int max_val;


    
    pass_comment(fic, buffer);
    if(type == 1){
        
        sscanf(buffer, "%d %d", &lines, &columns);
        
        if(lines >0 && columns >0){
        *image = build_PNM(type, lines, columns, fic);
        fill_matrix(type, lines, columns, fic, *image);
        
    
            }
        }else if(type == 2){
       
            sscanf(buffer, "%d %d", &lines, &columns);
           
            pass_comment(fic, buffer);
            sscanf(buffer, "%d", &max_val);
          

            if(lines >0 && columns >0){
                *image = build_PNM(type, lines, columns, max_val);
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
            *image = build_PNM(type, lines, columns, max_val);
            fill_matrix(type, lines, columns, fic, *image);
            }
        }


    fclose(fic);

   return 0;
}

int write_pnm(PNM *image, char* filename) {
    assert(filename != NULL && image != NULL);

    FILE* fic = fopen(filename, "w");
        if(fic == NULL){
            printf("error, couldn't open new file");
            return -1;
        }

   switch (image->type)
   {
    case 1: ;
       
       fprintf(fic, "P1\n%d %d\n", image->lines, image->columns);
       for(int i = 0; i< image->lines; i++){
           for(int j =0; j<image->columns; j++){
               fprintf(fic, "%d ", image->matrice_black[i][j]);
           }
           fprintf(fic, "\n");

       }
       fclose(fic);
       break;
    case 2: ;
       
       fprintf(fic, "P2\n%d %d\n%d\n", image->lines, image->columns, image->max_value);
       for(int i = 0; i< image->lines; i++){
           for(int j =0; j<image->columns; j++){
               fprintf(fic, "%d ", image->matrice_black[i][j]);
           }
           fprintf(fic, "\n");
       }
       fclose(fic);
       break;
    case 3: ;
         
        
        fprintf(fic, "P3\n %d %d\n%d\n", image->lines, image->columns, image->max_value);
        for(int i = 0; i< image->lines; i++){
            for(int j =0; j<image->columns; j++){
                fprintf(fic, "%d %d %d ", image->matrice_rgb[i][j].red, image->matrice_rgb[i][j].green, image->matrice_rgb[i][j].blue);
            }
           fprintf(fic, "\n");
        }
        fclose(fic);
       break;
   
    default:
       
        fclose(fic);
        return -2;
       break;
   }

   return 0;
}


void destroy_pnm(PNM *image){
    assert(image != NULL);
    switch(image->type){

        case 1:

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


void check_extension(char *input_file, char *output_file, char *format_file, PNM *image){
    char input_extension[5] = "";
    char output_extension[5] = "";

    

   for(int i = 3; i>0; i--){
      strncat(input_extension, &input_file[strlen(input_file)-i], 1);
      strncat(output_extension, &output_file[strlen(output_file)-i], 1);
   }

    if(strncmp(format_file, "pgm", 3) != 0 && strncmp(format_file, "pbm", 3) != 0 && strncmp(format_file, "ppm", 3) != 0){
        printf("Unallowed format chosen, the only allowed formats are pgm, ppm and pbm, you chosed : %s\n\n", format_file);
        printf("Do you want to change format ? press 1 to change and press anything alse to terminate the program\n");
        int choicef;
        scanf("%d", &choicef);
        if(choicef == 1){
            printf("chose new format\n");
            scanf("%s", format_file);
            check_extension(input_file, output_file, format_file, image);
        }else{
            printf("Goodbye");
            return;
        }

    }

   if((strncmp(format_file, input_extension, 3) == 0) && (strncmp(format_file, output_extension, 3) == 0))
   {
      printf("Format file :%s Input extension : %s, Output extension : %s\n",format_file, input_extension, output_extension);      
      printf("Format : %s, Input : %s, Output : %s\n", format_file, input_file, output_file);
      load_pnm(&image, input_file);
      write_pnm(image, output_file);
      destroy_pnm(image);

   }else{
    printf("Different files extensions don't match : Chosen file extension : %s, Input file extension :%s, Output file extension :%s\n",
                                     format_file, input_extension, output_extension);
    printf("Do you want to change the given data ?\n");
    int choice;
    printf("Press 1 for yes and anything To terminate the program\n");
    scanf("%d", &choice);
    if(choice == 1){
        printf("Give us the new data (the order is : format input_file output_file) separated by spaces\n");
        scanf("%s %s %s", format_file, input_file, output_file);
        check_extension(input_file, output_file, format_file, image);
    }else{
        printf("Goodbye");
        return;
    }

   }

}