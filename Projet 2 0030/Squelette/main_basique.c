
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"
#include "lsfr.h"
#include "basique.h"


int main(int argc, char *argv[]) {

   char *optstring = ":i:o:s:t:";

   char *input_file ;
   char *output_file ;
   char *seed;
   int tap;

   int value;
    PNM *image; 
   

   while((value=getopt(argc, argv, optstring)) != EOF){
    switch(value) {
        case 'i':
            input_file = optarg;
            printf("\n%s", optarg);
            break;
        case 'o':
            output_file = optarg;  
            printf("\n%s", optarg);    
            break;
        case 't':
            tap = optarg;
            printf("\n%d", optarg);
            break;
        case 's':
            seed = optarg;
            printf("\n%s", optarg);
            break;
         default:
            printf("Wrong command");
            break;
    }// fin switch
   }

        // printf("\n\nTHE TAP VALUE IS %d\n\n", tap);
        // printf("\n\nTHE SEED IS %s \n\n", seed);
        // printf("\n\nTHE INPUT FILE IS %s \n\n", input_file);

if(input_file !=  NULL){
    
    //load_pnm(&image, input_file);
    if(seed != NULL && tap != NULL){
        
    LSFR *mylsfr = initialisation(seed, tap);
    //encryption(mylsfr, image, output_file );

    //destroy_pnm(image);
    destructor(mylsfr);
    }
}

}
