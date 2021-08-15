#include "lfsr.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


struct LSFR_t{
    unsigned int lenght;
    int *seed;
    unsigned int tap;
};


LSFR *initialisation(char *seed, unsigned int tap){
    assert(seed != NULL && tap > 0);

    // start with getting the lenght of our seed

    unsigned int seed_lenght = strlen(seed);


    if(tap >= seed_lenght){
        printf("ERROR, the tap value is not within the seed\n");
        printf(" if you want to chose a enw tap value, press 1 (tap value should be between 0 and %d)\n press anything else to terminate the program", seed_lenght);
        int choice;
        scanf("\n %d", & choice);
        if(choice == 1){
            scanf("enter your new tap value %d", &tap);
        initialisation(seed, tap);
        }else{
            printf("\n\n Program ended");
            exit(1);
        }
        
        return 0;
    }
    // checking the seed content
    for(unsigned int i= 0; i<seed_lenght; i++){
        if(seed[i] != '0' && seed[i] != '1'){
            printf("unallowed caracters in the seed\n");
            return 0;
        }
    }

    // create our lsfr using our constructor
    LSFR *mylsfr = constructor();
    mylsfr->seed = malloc(sizeof(int)*seed_lenght);
    if(mylsfr->seed == NULL){
        printf("couldn't allocate memory for the seed");
        return NULL;
    }
    // fill our LSFR structure using setters
    set_lenght(mylsfr, seed_lenght);
    set_tap(mylsfr, tap);
    set_seed(mylsfr, seed);

    return mylsfr;
}

int operation(LSFR *mylsfr){
    assert( mylsfr != NULL);

    int new_lower_bit;
  
    new_lower_bit = mylsfr->seed[0] ^ mylsfr->seed[mylsfr->lenght-mylsfr->tap-1];
    //printf("%d XOR %d\n", mylsfr->seed[mylsfr->lenght] ^ mylsfr->seed[mylsfr->tap+1]);

     int newseed[mylsfr->lenght];
    for(unsigned int i = 0; i<mylsfr->lenght-1; i++){
        newseed[i] = mylsfr->seed[i+1];
    }
    newseed[mylsfr->lenght-1] = new_lower_bit;

   for(unsigned int i = 0; i<mylsfr->lenght; i++){
       mylsfr->seed[i] = newseed[i];
   } 
    return new_lower_bit;
}

char *string(LSFR *mylsfr){
    assert(mylsfr != NULL);
   
 

    // transforming our array of integers into a string.
    int lenght = mylsfr->lenght;
    char digit[5];
    char *strseed= malloc(sizeof(char)*mylsfr->lenght);


    for(int i =0; i<mylsfr->lenght; i++){
        
        sprintf(digit, "%d", mylsfr->seed[i]);
        if(i == 0){
            strcpy(strseed, digit);
        }else{
            strncat(strseed, &digit, 1);
        }
        
    }
    

   return strseed;
}

int generation(LSFR *mylsfr, int nombre){
    int init_seed[mylsfr->lenght];

    // keeping the initial value of the seed
    for(int i=0; i<mylsfr->lenght; i++){
        init_seed[i] = mylsfr->seed[i];
    }

    
    int result = 0, bit = 0;
    for(int i =0; i<nombre; i++){
        bit = operation(mylsfr);
        result = (result *2) + bit;
        
    }

    return result;
}
// initialisation of the constructor
LSFR *constructor(){
    LSFR *mylsfr;
    mylsfr = malloc(sizeof(LSFR));
    if(mylsfr == NULL){
        printf("couldn't allocate memory for our lsfr\n");
        return NULL;
    }
    return mylsfr;
}
// initiallisation of the destructor 
 void destructor(LSFR *mylsfr){
    free(mylsfr->seed);
    free(mylsfr);
}

// initialisation of the setters
 void set_seed(LSFR *mylsfr, char *seed){
     int number = atoi(seed);
     int temp[mylsfr->lenght];
    for(unsigned int i = 0; i < mylsfr->lenght; i++){
        temp[i] = number %10;
        number /= 10;
    }
    // put the array int the right order
    for(int i = 0; i<mylsfr->lenght; i++){
        mylsfr->seed[i] = temp[mylsfr->lenght-1-i];
    }
}

 void set_tap(LSFR *mylsfr, unsigned int tap){
    mylsfr->tap = tap;
}

 void set_lenght(LSFR *mylsfr, unsigned int lenght){
    mylsfr->lenght = lenght;
}

 int get_tap(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->tap;
}

 int get_lenght(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->lenght;
}