/**
 * \file basique.c
 *
 *
 * \brief INFO0030 Projet 2 - Chiffrement basique d'images
 * \author Andries Alexandre s196948
 * \version 0.1
 * \date 15/03/2021
 *
 * Ce fichier contient les définitions de types et
 * les fonctions pour le chiffrement basique d'images.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "lfsr.h"
#include "pnm.h"
#include "basic_cipher.h"

// int **build_matrix(int lines, int columns, int columns_size, int **matrix){
//                matrix = malloc(sizeof(int)* lines);
//                 if(matrix == NULL){
//                     free(matrix);
//                     return NULL;
//                 }
            
//             for(int i =0; i< lines; i++){
//                 matrix[i] = malloc(sizeof(int)*columns*columns_size);
//                     if(matrix[i]== NULL){
//                         for(int j = 0; j<= i; j++){
//                             free(matrix[j]);
//                             free(matrix);
//                             return NULL;
//                         }
//                     }
//             }
//             return matrix;
// }

// void compilation_args(int argc, char *argv[], char *optstring, char **seed, char **input_file, char **output_file, int *tap ){
//      int val;

//    while((val=getopt(argc, argv, optstring)) != EOF){
//     switch(val) {
//         case 'i':
//             *input_file = optarg;
//             printf("\n%s", optarg);
//             break;
//         case 'o':
//             *output_file = optarg;  
//             printf("\n%s", optarg);    
//             break;
//         case 't':
//             *tap = atoi(optarg);
//             printf("\n%s", optarg);
//             break;
//         case 's':
//             *seed = optarg;
//             printf("\n%s", optarg);
//             break;
//          default:
//             printf("Wrong command");
//             break;
//     }// fin switch
//    }
// }

void encryption(LSFR *mylsfr,   PNM *image, char *filename){
    assert(mylsfr != NULL && image != NULL && filename != NULL);

     int chiff;
     printf("%d, %d", get_columns(image), get_lines(image));
    if(get_type_pnm(image) == 1 || get_type_pnm(image) == 2){  
        for(int i=0; i<get_lines(image); i++){
            for(int j =0; j<get_columns(image); j++){
            chiff =  generation(mylsfr, 32);
            //printf("%d ", chiff);
            set_matrix(image, i, j, get_matrix(image)[i][j] ^ chiff);
        }
    }
    }else if(get_type_pnm(image) == 3){
          
            
        for(int i=0; i<get_lines(image); i++){
            for(int j =0; j<get_columns(image)*3; j++){
            chiff =  generation(mylsfr, 32);
            set_matrix(image, i, j, get_matrix(image)[i][j] ^ chiff);
        }
    }

    }

    write_pnm(image, filename); 
}