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