#include "lsfr.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


struct LSFR_t{
    unsigned int lenght;
    char *seed;
    unsigned int tap;
};


LSFR *initialisation(char *seed, unsigned int tap){


    // start with getting the lenght of our seed

    unsigned int seed_lenght = strlen(seed);


    if(tap >= seed_lenght){
        printf("ERROR, the tap value is not within the seed");
        return 0;
    }
    // create our lsfr using our constructor
    LSFR *mylsfr = constructor();

    // fill our LSFR structure using setters
    set_lenght(mylsfr, seed_lenght);
    set_seed(mylsfr, seed);
    set_tap(mylsfr, tap);

    return mylsfr;
}

int operation(LSFR *mylsfr){
    assert( mylsfr != NULL);

    unsigned int lenght = get_lenght(mylsfr);
    unsigned int tap = get_tap(mylsfr);
    char seed = get_seed(mylsfr);

   
    int tap_number =  atoi(&seed[tap]);

    unsigned int new_lower_bit;

    new_lower_bit =  tap_number;

    return new_lower_bit;
}

char *transformation(LSFR *mylsfr){
    assert(mylsfr != NULL);
    
    unsigned int lenght = get_lenght(mylsfr);

    // allocate memory for  a temporary seed
    char *seed = malloc(sizeof(char)*lenght);
    //allocate memory for an array of integers 
    int *int_seed = malloc(sizeof(int)* lenght);

    // put the seed in our sturcture in our newly allocated space
    strcpy(seed, get_seed(mylsfr));
    
    // transform our seed into an array of integers and store it in aur allocated array
    char *temporary_seed = malloc(sizeof(char)*lenght);
      for(unsigned int i =0; i<lenght; i++){
        int_seed[i] = atoi(&seed[i]);
    }
    // use sprintf to convert our array of integers into a string
    int index;
    for(unsigned int i = 0; i < lenght; i++){
        if(i < lenght-1){
            index += sprintf(&temporary_seed[index], "%d", int_seed[i+1]);
        }else{
            index += sprintf(&temporary_seed, "%d", operation(mylsfr));
        }
    }

    // put the new seed in our structure
    set_seed(mylsfr, temporary_seed);

    // free our temporary seed after use
    free(temporary_seed);
    free(seed);
    free(int_seed);

    return get_seed(mylsfr);

}
// initialisation of the constructor
LSFR *constructor(){
    LSFR *mylsfr;
    mylsfr = malloc(sizeof(LSFR));
    return mylsfr;
}
// initiallisation of the destructor 
 void destructor(LSFR *mylsfr){
    free(mylsfr);
}
// initialisation of the setters
 void set_seed(LSFR *mylsfr, char *seed){
    mylsfr->seed = seed;
}

 void set_tap(LSFR *mylsfr, unsigned int tap){
    mylsfr->tap = tap;
}

 void set_lenght(LSFR *mylsfr, unsigned int lenght){
    mylsfr->lenght = lenght;
}

// initialisation of the getters
 char* get_seed(LSFR *mylsfr){
    assert(mylsfr != NULL);
    return mylsfr->seed;
}
 int get_tap(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->tap;
}

 int get_lenght(LSFR *mylsfr){
    assert( mylsfr != NULL);
    return mylsfr->lenght;
}




