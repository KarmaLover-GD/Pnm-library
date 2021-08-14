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

#include "lsfr.h"
#include "pnm.h"
#include "basique.h"

int **build_matrix(int lines, int columns, int columns_size, int **matrix){
               matrix = malloc(sizeof(int)* lines);
                if(matrix == NULL){
                    free(matrix);
                    return NULL;
                }
            
            for(int i =0; i< lines; i++){
                matrix[i] = malloc(sizeof(int)*columns*columns_size);
                    if(matrix[i]== NULL){
                        for(int j = 0; j<= i; j++){
                            free(matrix[j]);
                            free(matrix);
                            return NULL;
                        }
                    }
            }
            return matrix;
}


void encryption(LSFR *mylsfr,   PNM *image, char *filename){
    assert(mylsfr != NULL && image != NULL && filename != NULL);

     int chiff;
     
    if(get_type_pnm(image) == 1 || get_type_pnm(image) == 2){
 
        
            
        for(int i=0; i<get_lines(image); i++){
            for(int j =0; j<get_columns(image); j++){
            chiff =  generation(mylsfr, 32);
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