#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>  

#include "modele_five.h"


ModeleFive *creer_modele_five(int niveau){
   ModeleFive *mf = malloc(sizeof(ModeleFive));
   if(mf == NULL){
      return NULL;
   }

   mf->niveau = niveau;
   mf->score = 0;
   mf->nouvelle_partie = 0;

   if(mf->niveau == 0){

      mf->cellules = 49;
      mf->hauteur = 7;
      mf->largeur = 7;
      mf->symbolesTour = 3;
      mf->typeSymboles = 5;
      mf->combo = 7;
      mf->avancer_tableau_horizontale = 3;
      mf->avancer_tableau_verticale = 3;
      mf->avancer_tableau_oblique = 5;
      mf->oblique_decroissant = 1; 
   }
   else if(mf->niveau == 1){

      mf->cellules = 81;
      mf->hauteur = 9;
      mf->largeur = 9;
      mf->symbolesTour = 3;
      mf->typeSymboles = 7;
      mf->combo = 9;
      mf->avancer_tableau_horizontale = 5;
      mf->avancer_tableau_verticale = 5;
      mf->avancer_tableau_oblique = 7;
      mf->oblique_decroissant = 1;
   }
   else if(mf->niveau == 2){

      mf->cellules = 300;
      mf->hauteur = 20;
      mf->largeur = 15;
      mf->symbolesTour = 7; 
      mf->typeSymboles = 7;
      mf->combo = 14;
      mf->avancer_tableau_horizontale = 11;
      mf->avancer_tableau_verticale = 16;
      mf->avancer_tableau_oblique = 11;
      mf->oblique_decroissant = 6; 
   }

   for(int i = 0; i < mf->hauteur; i++){
      for(int j = 0; j < mf->largeur; j++){
         mf->grille[i][j] = 0;
         mf->aleatoire[i][j] = 0;
      }
   }
return mf;
}//fin creer_modele_five()

void change_valeur(ModeleFive *mf, int i, int j, int val){
   assert(mf != NULL && i < mf->hauteur && j < mf->largeur && val >= 0 && val < mf->typeSymboles + 1);

   mf->grille[i][j] = val;
}//fin change_valeur()

void position_case_blanche(ModeleFive *mf, int i, int j, int compteur){
   assert(mf != NULL && i < mf->hauteur && j < mf->largeur && compteur >= 0 && compteur < mf->cellules + 1 );
 
   mf->aleatoire[i][j] = compteur;
}//fin position_case_blanche()

int generation_image_aleatoire(ModeleFive *mf){
   assert(mf != NULL);
   int compteur = 0;
   for (int i = 0; i < mf->hauteur; i++){
      for (int j = 0; j < mf->largeur; j++){
         position_case_blanche(mf, i, j, 0);
         if(mf->grille[i][j] == 0){
            compteur += 1;
            position_case_blanche(mf, i, j, compteur);
               
         }
      }
   }
   if(compteur != 0){
      srand(time(NULL));
      int a = rand () % compteur;
      for (int i = 0; i < mf->hauteur; i++){
         for (int j = 0; j < mf->largeur; j++){
            if(mf->aleatoire[i][j] == a + 1){ 
               compteur = (i * mf->largeur) + j;
            }
         }
      }
   }
   else{
      compteur = 1000;
   }
return compteur;
}// fin generation_image_aleatoire()

int case_blanche_compteur(ModeleFive *mf){
   assert(mf != NULL);
   int compteur = 0;
   for (int i = 0; i < mf->hauteur;  i++){
      for(int j = 0; j < mf->largeur; j++){
         if (mf->grille[i][j] == 0){
            compteur += 1;
         }
      }
   }
   return compteur;
}// fin case_blanche_compteur()

void classement(ModeleFive *mf){
   assert(mf != NULL);
   if(mf->nouvelle_partie > 9 && mf->score > mf->ligneActuelle[0]){
      mf->ligneActuelle[0] = mf->score;
   }
   else if(mf->nouvelle_partie < 10){
      mf->ligneActuelle[mf->nouvelle_partie] = mf->score;
      mf->nouvelle_partie += 1;
   }
}// fin classement()