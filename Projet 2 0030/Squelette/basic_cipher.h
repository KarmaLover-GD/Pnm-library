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
 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <unistd.h>
 #include <ctype.h>
 #include <getopt.h>
 #include <string.h>
 #include "lfsr.h"
 #include "pnm.h"

void encryption(LSFR *mylsfr,   PNM *image, char *filename);
void compilation_args(int argc, char *argv[], char *optstring, char **seed, char **input_file, char **output_file, int *tap );





#ifndef __BASICCIPHER__
#define __BASICCIPHER__

































































#endif // __BASICCIPHER__
