
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
  

        
compilation_args(argc, argv, optstring, &seed, &input_file, &output_file, &tap);

        printf("\n\nTHE TAP VALUE IS %d\n\n", tap);
        printf("\n\nTHE SEED IS %s \n\n", seed);
        printf("\n\nTHE INPUT FILE IS %s \n\n", input_file);
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
