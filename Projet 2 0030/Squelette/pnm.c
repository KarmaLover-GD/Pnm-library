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
 * Définition du type opaque PNM
 *
 */


struct PNM_t {
    int lines;
    int columns;
    int max_value;
    int type;
    int **matrice;
    
};


//--------------------------------------------------
static void pass_comment(FILE *fic, char*buffer){
   assert(fic != NULL && buffer != NULL);

   do
   fgets(buffer, 100, fic);
   while(strncmp(buffer, "#", 1) == 0);  
}
//-----------------------------------------------
//-----------------------------------------------
static int get_type(FILE* fic, char *buffer) {
    assert(fic != NULL && buffer != NULL);
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
        } else{
            printf("%s", buffer);
            return 0;
        }
            
    fclose(fic);
}
//-----------------------------------------------
//-----------------------------------------------
static PNM *build_PNM(int type, int lines, int columns, int max_val){
    assert(type >0 && type <4 && lines > 0 && columns >0 && max_val >= 0);
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
 
        image->matrice = malloc(sizeof(int)*2*lines);
        for(int i = 0; i<lines; i++){
            image->matrice[i] = malloc(sizeof(int)*columns);
        }
               
        if(image->matrice == NULL){
        for(int i =0; i<lines; i++){
            free(image->matrice[i]);
        }
            free(image->matrice);
            free(image);
            printf("erreur encodage matrice");
            return NULL;
        }
        break;
    


    case 2: ;
  

        image->columns = columns;
        image->lines = lines;
        image->type = type;

        image->max_value = max_val;
        image->matrice = malloc(sizeof(int)*2*lines);
        for(int i = 0; i<lines; i++){
            image->matrice[i] = malloc(sizeof(int)*columns);
        }
        
        
        if(image->matrice == NULL){
            for(int i =0; i<lines; i++){
                free(image->matrice[i]);
                }
                free(image->matrice);
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
           image->matrice = malloc(sizeof(int)*2*lines);
          for(int i = 0; i<lines; i++){
            image->matrice[i] = malloc(sizeof(int)*3*columns);
        }
        
        
        if(image->matrice == NULL){
            for(int i =0; i<lines; i++){
                free(image->matrice[i]);
                }
                free(image->matrice);
            free(image);
            printf("erreur encodage matrice");
            return NULL;
        }

    }
    return image;
     }
        
    
//-----------------------------------------------
//-----------------------------------------------
static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image){
    
    int pixel;
    int red, green, blue;
    
    switch (type)
    {
    case 1:

        //pass_comment(fic, buffer);
       
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d ", &pixel);
    
                image->matrice[i][j] = pixel;
                
            }
        }
        break;
    case 2:
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns; j++){
                fscanf(fic, "%d ", &pixel);
              
            
                image->matrice[i][j] = pixel;
              
            }
        }
        break;
    case 3:
        for(int i = 0; i<lines; i++){
            for(int j =0; j<columns*3 ; j+=3){
               
                fscanf(fic, "%d %d %d ", &red, &green, &blue);
                image->matrice[i][j] = red;
                image->matrice[i][j+1] = green;
                image->matrice[i][j+2] = blue;
                
              
            }
        }
    
    default:
        break;
    }
    return image;
}
//-----------------------------------------------
//-----------------------------------------------
int load_pnm(PNM **image, char* filename) {
    assert(filename != NULL && image != NULL);
    //printf("Filename : %s", filename);
    int choice;
    FILE *fic = fopen(filename, "r");
    if (fic == NULL){
        printf("Unable to access the chosen input file, the name may be wrong, do you want to try again ?\n");
        printf("to change input file, press 1. press anything else to terminate the program\n");
        scanf("Your choice : %d", &choice);
        if(choice == 1){
            printf("enter you input file's name\n");
            scanf("%s", filename);
            load_pnm(image, filename);
        }else{
        fclose(fic);
        printf("erreur à l'ouverture du fic");
        return -2;
        }

        
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
        *image = build_PNM(type, lines, columns, 0);
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
//-----------------------------------------------
//-----------------------------------------------
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
               fprintf(fic, "%d ", image->matrice[i][j]);
           }
           fprintf(fic, "\n");

       }
       fclose(fic);
       break;
    case 2: ;
       
       fprintf(fic, "P2\n%d %d\n%d\n", image->lines, image->columns, image->max_value);
       for(int i = 0; i< image->lines; i++){
           for(int j =0; j<image->columns; j++){
               fprintf(fic, "%d ", image->matrice[i][j]);
           }
           fprintf(fic, "\n");
       }
       fclose(fic);
       break;
    case 3: ;
         
        
        fprintf(fic, "P3\n %d %d\n%d\n", image->lines, image->columns, image->max_value);
        for(int i = 0; i< image->lines; i++){
            for(int j =0; j<image->columns * 3; j+=3){
                fprintf(fic, "%d %d %d ", image->matrice[i][j], image->matrice[i][j+1], image->matrice[i][j+2]);
            }
           fprintf(fic, "\n");
        }
        fclose(fic);
       break;
   
    default:
        fclose(fic);
        return -3;
       break;
   }

   return 0;
}

//-----------------------------------------------
//-----------------------------------------------
void destroy_pnm(PNM *image){
    assert(image != NULL);
    switch(image->type){

        case 1:

            for(int i =0; i<image->lines; i++){
                free(image->matrice[i]);
            }
            free(image->matrice);
            free(image);

            break;
        case 2:
            
            for(int i =0; i<image->lines; i++){
                free(image->matrice[i]);
            }
            free(image->matrice);
            free(image);

            break;
        case 3:

            for(int i = 0; i<image->lines; i++){
                free(image->matrice[i]);
            }
            free(image->matrice);
            free(image);

            break;
        default:
            break;

    }

}

//-----------------------------------------------
//-----------------------------------------------
void check_extension(char *input_file, char *output_file, char *format_file, PNM *image){
    char input_extension[5] = "";
    char output_extension[5] = "";
    if(check_filename(output_file) != NULL){
        printf("output file contains the unallowed character '%c' ", check_filename(output_file));
        printf("\n Do you want to change the name of your output file ?");
        printf("\n press 1 for to retry and anything else to terminate the program");
        int choice;
        scanf("\n %d", & choice);
        if(choice == 1){
            printf("chose your new output type the name of you new output file\n");
            scanf("%s", output_file);
            check_extension(input_file, output_file, format_file, image);
        }
    }
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


char check_filename(char *filename){
    for(int i =0; i<strlen(filename); i++){
        
  for(long unsigned int i = 0; i < strlen(filename); i++){
    if(filename[i] == '/' || filename[i] == ':' || filename[i] == '*' || filename[i] == '?' || filename[i] == '"'       
                          || filename[i] == '<' || filename[i] == '>' || filename[i] == '|' || filename[i] == '\\'){           
        return filename[i];
      }
  }
  return NULL;
}
}

// Getters and setters

int get_type_pnm(PNM *image){

    return image->type;

}

int get_lines(PNM * image){
    return image->lines;
}
int get_columns(PNM *image){
    return image->columns;
}
int **get_matrix(PNM *image){

    return image->matrice;
}




void set_matrix(PNM *image, int x, int y, int value){

   if(image->type == 1 || image->type == 2){
       for(int i=0; i<image->lines; i++){
        for(int j =0; j<image->columns; j++){
            image->matrice[x][y] = value;
            }
        }
    }
}
