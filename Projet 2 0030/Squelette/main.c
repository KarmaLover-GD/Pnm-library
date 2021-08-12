#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lsfr.h"

int main()
{
   
    LSFR *mylsfr = initialisation("01101000010", 8);
    
    printf("%s,  %d",transformation(mylsfr), operation(mylsfr));
    
    destructor(mylsfr);
  
}
