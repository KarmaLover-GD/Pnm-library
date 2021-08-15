
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "basic_cipher.h"


int main(int argc, char * argv[]) {


   char *input_file1 = argv[2];
   char *output_file1 = argv[4];
   char *seed1 = argv[6];
   int tap1 = atoi(argv[8]);

    PNM *image = NULL; 
  
  int valeur1;
   /*
   *-i input
   *-o output
   *-s seed
   *-t tap 
   */
  char *optstring = ":i:o:s:t:";
  
  if(argc != 9){
      printf("Not the right amount of arguments");
      exit(1);
  }
   while((valeur1=getopt(argc, argv, optstring)) != EOF){
    switch(valeur1) {
        case 'i':
            input_file1 = optarg;
            printf("\n%s", optarg);
            break;
        case 'o':
            output_file1 = optarg;  
            printf("\n%s", optarg);    
            break;
        case 't':
            tap1 = atoi(optarg);
            printf("\n%s", optarg);
            break;
        case 's':
            seed1 = optarg;
            printf("\n%s", optarg);
            break;
        case '?':
            printf("UNKNOW ARGUMENT %d", optopt);
            break;
        case ':':
            printf("numers of arguments doesn't match, %d", optopt);
            break;
         default:
            printf("Wrong command %d", optopt);
            exit(1);
            break;
    }// fin switch

   }
        
//compilation_args(argc, argv, optstring, &seed, &input_file, &output_file, &tap);
        
        printf("\n\nTHE TAP VALUE IS %d\n\n", tap1);
        printf("\n\nTHE SEED IS %s \n\n", seed1);
        printf("\n\nTHE INPUT FILE IS %s \n\n", input_file1);
if(input_file1 !=  NULL){
    
    load_pnm(&image, input_file1);
    if(seed1 != NULL){
        
    LSFR *mylsfr = initialisation(seed1, tap1);
    encryption(mylsfr, image, output_file1 );

    destroy_pnm(image);
    destructor(mylsfr);
    }
}

}
