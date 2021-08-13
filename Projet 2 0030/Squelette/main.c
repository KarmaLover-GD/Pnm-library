#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lsfr.h"

int main()
{
   
    LSFR *mylsfr = initialisation("01101000010", 8);
    // for(int i=0; i<10; i++){
    //     printf("%s %d", operation(mylsfr), transformation(mylsfr));
    // }
    printf("operation result :%d\n", operation(mylsfr));
    printf("transformation : %s", transformation(mylsfr));
    //transformation(mylsfr);
    destructor(mylsfr);
  
}
