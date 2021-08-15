
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
#include "advanced_cipher.h"

int main(int argc, char * argv[]) {


   char *input_file1 = argv[2];
   char *output_file1 = argv[4];
   char *password = argv[6];
   int tap1 = atoi(argv[8]);

    PNM *image ; 
  
  int valeur1;
   /*
   *-i input
   *-o output
   *-p passowrd
   *-t tap 
   */
  char *optstring = ":i:o:p:t:";
  
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
            password = optarg;
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

    printf("\nINPUT :%s \nOUTPUT :%s \nPASSWORD :%s  \nTAP : %d\n", input_file1, output_file1, password, tap1);
    if(input_file1 !=  NULL){
        
        load_pnm(&image, input_file1);
        if(password != NULL){
            char *converted_pass = malloc(sizeof(char)*strlen(password)+5);
            strcpy(converted_pass, password_to_seed(password));
            LSFR *mylsfr = initialisation(converted_pass, tap1);
            encryption(mylsfr, image, output_file1 );

            destroy_pnm(image);
            //destructor(mylsfr);
            //free(converted_pass);
        }
    }
}