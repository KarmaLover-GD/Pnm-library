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
    assert(seed != NULL && tap > 0);

    // start with getting the lenght of our seed

    unsigned int seed_lenght = strlen(seed);


    if(tap >= seed_lenght){
        printf("ERROR, the tap value is not within the seed\n");
        return 0;
    }
    // checking the seed content
    for(int i= 0; i<seed_lenght; i++){
        if(seed[i] != '0' && seed[i] != '1'){
            printf("unallowed caracters in the seed\n");
            return 0;
        }
    }

    // create our lsfr using our constructor
    LSFR *mylsfr = constructor();

    // fill our LSFR structure using setters
    set_lenght(mylsfr, seed_lenght);
    set_seed(mylsfr, seed);
    set_tap(mylsfr, tap);

    return mylsfr;
}

static int *stringtoarray(char *string){

}

int operation(LSFR *mylsfr){
    assert( mylsfr != NULL);

    unsigned int lenght = get_lenght(mylsfr);
    unsigned int tap = get_tap(mylsfr);
    char *seed = get_seed(mylsfr);

   
    int tap_number =  atoi(&seed[tap]);

    unsigned int new_lower_bit;

    new_lower_bit =  tap_number;

    return new_lower_bit;
}

char *transformation(LSFR *mylsfr){
    assert(mylsfr != NULL);
    
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




