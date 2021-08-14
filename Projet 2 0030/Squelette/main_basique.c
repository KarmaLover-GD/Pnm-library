
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"
#include "lsfr"
#include "basique.h"


int main(int argc, char *argv[]) {

   char *optstring = ":f:i:o:s:t";
   char *format_file;
   char *input_file;
   char *output_file;
   char *seed;
   char *tap;

   int value;
    PNM *image; 
   

   while((value=getopt(argc, argv, optstring)) != EOF){
    switch(value) {
        case 'f':
            format_file = optarg;
            break;
        case 'i':
            input_file = optarg;
         break;
        case 'o':
            output_file = optarg;          
            break;
        case 't':
            tap = optarg;
            break;
        case 's':
            seed = optarg;
            break;
         default:
            printf("Wrong command");
            break;
    }// fin switch
   }
if(input_file !=  NULL){
    load_pnm(&image, input_file);
    if(seed != NULL && tap != NULL){
    LSFR *mylsfr = initialisation(seed, tap);
    encryption(mylsfr, image, output_file );
    }
}

}