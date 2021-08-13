#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lsfr.h"

int main()
{
   
    LSFR *mylsfr = initialisation("01101000010", 8);
    
    printf(" operation result :%d\n", operation(mylsfr));
    //printf("transformation : %s", transformation(mylsfr));
    transformation(mylsfr);
    destructor(mylsfr);
  
}
