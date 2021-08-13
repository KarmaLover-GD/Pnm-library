#include "lsfr.h"
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
    printf("Seed :");
    for(int i = 0;i < seed_lenght; i++){
        printf( "%d", mylsfr->seed[i]);
    }
    printf(" Lenght :%d,  tap :%d,", mylsfr->lenght, mylsfr->tap);

    return mylsfr;
}



int operation(LSFR *mylsfr){
    assert( mylsfr != NULL);

    int new_lower_bit;
  
    new_lower_bit = mylsfr->seed[mylsfr->lenght] ^ mylsfr->seed[mylsfr->tap+1];


    return new_lower_bit;
}

char *transformation(LSFR *mylsfr){
    assert(mylsfr != NULL);
    int newseed[mylsfr->lenght];
    int last_bit = operation(mylsfr);

    for(unsigned int i = 0; i<mylsfr->lenght-1; i++){
        newseed[i] = mylsfr->seed[i+1];
    }
    newseed[mylsfr->lenght-1] = last_bit;

   for(unsigned int i = 0; i<mylsfr->lenght; i++){
       mylsfr->seed[i] = newseed[i];
   } 
//    char result[255];

//    strcpy(result, arraytostring(mylsfr->seed, mylsfr));
    
    

   return ;
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

char *arraytostring(int *array, LSFR* mylsfr){
    char string[strlen(mylsfr->lenght +2)];
    int index = 0;
    for (int i = 0; i<mylsfr->lenght; i++)
    index += sprintf(&string[index], "%d", array[i]);
    return string;
}


// initialisation of the setters
 void set_seed(LSFR *mylsfr, char *seed){
     int number = atoi(seed);
    for(unsigned int i = 0; i < mylsfr->lenght; i++){
        mylsfr->seed[i] = number %10;
        number /= 10;
    }
}

 void set_tap(LSFR *mylsfr, unsigned int tap){
    mylsfr->tap = tap;
}

 void set_lenght(LSFR *mylsfr, unsigned int lenght){
    mylsfr->lenght = lenght;
}

// initialisation of the getters
//  char* get_seed(LSFR *mylsfr){
//     assert(mylsfr != NULL);
//     return mylsfr->seed;
// }
 int get_tap(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->tap;
}

 int get_lenght(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->lenght;
}




