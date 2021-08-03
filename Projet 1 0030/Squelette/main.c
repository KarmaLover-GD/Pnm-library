/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Ouro-Gomma Marzouk S204743
 * @date: 
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"


int main(int argc, char *argv[]) {

   char *optstring = "";
   PNM *image;
   
   load_pnm(&image, "totem.pgm");

   destroy_pnm(image);
   
    //printf("%d %d",mon_image, image);

   //display_content(1, image);


   return 0;
}

