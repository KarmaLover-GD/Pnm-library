#ifndef __chiffrement__
#define __chiffrement__


typedef struct LSFR_t LSFR;

LSFR *initialisation(char *seed, unsigned int bits);

int operation(LSFR *string);

char *transformation(LSFR *string);
// getters

int get_lenght(LSFR *mylsfr);
char *get_seed(LSFR *mylsfr);
int get_tap(LSFR *mylsfr);

// setters

void set_tap(LSFR *mylsfr, unsigned int tap);
void set_seed(LSFR *mylsfr, char *seed);
void set_lenght(LSFR *mylsfr, unsigned int lenght);


// constructor and destructor

LSFR *constructor();
void destructor(LSFR *mylsfr);
#endif 