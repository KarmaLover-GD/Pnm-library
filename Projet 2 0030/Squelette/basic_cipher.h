/**
 * \file basique.h
 *
 * \brief INFO0030 Projet 2 - Chiffrement basique d'images
 * \author Ouro-Gomma Marzouk S204743
 * \version 0.1
 * \date  10/08/2021
 *
 * Ce fichier contient les déclarations de types
 *  et les prototypes des fonctions pour le chiffrement basique d'images.
 */


#ifndef __BASICCIPHER__
#define __BASICCIPHER__

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <unistd.h>
 #include <ctype.h>
 #include <getopt.h>
 #include <string.h>
 #include "lfsr.h"
 #include "pnm.h"

/*
*
* this function creates a new enrypted image. and can alse be used to decryp the image the same way.
* 
*
*
*/

void encryption(LSFR *mylsfr,   PNM *image, char *filename);


#endif // __BASICCIPHER__
