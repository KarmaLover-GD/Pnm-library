#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lsfr.h"

int main()
{
   
    LSFR *mylsfr = initialisation("01101000010", 8);
    
    for(int i=0; i<10; i++){
        int r = generation(mylsfr, 5);
        printf("%s %d\n", string(mylsfr), r);
        
    }
    
    //string(mylsfr);
    destructor(mylsfr);
  
}
