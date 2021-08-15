#ifndef __ADVANCEDCIPHER__
#define __ADVANCEDCIPHER__

/**
 * \file advanced_cipher.h
 *
 * \brief INFO0030 Projet 2 - Chiffrement avancé d'images
 * \author Andries Alexandre s196948
 * \version 0.1
 * \date 15/03/2021
 *
 * Ce fichier contient les déclarations de types
 *  et les prototypes des fonctions pour le chiffrement avancé d'images.
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

char *password_to_seed(char* password);


 #endif