#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lsfr.h"

int main()
{
   
    LSFR *mylsfr = initialisation("01101000010", 8);
    
    printf("%d", operation(mylsfr));
    
    destructor(mylsfr);
  
}
