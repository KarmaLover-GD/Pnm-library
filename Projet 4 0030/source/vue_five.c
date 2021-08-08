#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>  

#include "vue_five.h"
#include "controleur_five.h"

VueFive *creer_vue_five(ModeleFive *mf){
   assert(mf != NULL);

   VueFive *vf = malloc(sizeof(VueFive));
   if(vf == NULL){
      return NULL;
   }
   

   vf->mf = mf;
   vf->image = g_new (GtkWidget *, vf->mf->cellules);
   vf->image_aleatoire = g_new (GtkWidget *, vf->mf->symbolesTour);
   vf->bouton_aleatoire = g_new (GtkWidget *, vf->mf->symbolesTour);
   vf->couleur_actuelle = malloc(vf->mf->symbolesTour * sizeof(int));
   for(int i = 0; i < mf->cellules; i++){
      vf->image[i] = gtk_image_new_from_file("images/default.png");
   }
   
   charge_images_aleatoires(vf);
  
   for (int i = 0; i < vf->mf->symbolesTour; i++){
      vf->bouton_aleatoire[i] = gtk_button_new();
      gtk_container_add(GTK_CONTAINER(vf->bouton_aleatoire[i]), vf->image_aleatoire[i]);
   }
   
return vf;
}//fin creer_vue()

int charge_1couleur_deplacement(VueFive *vf, int y_init, int x_init, int y_dest, int x_dest){
   assert(vf != NULL);
   int couleur;
      switch (vf->mf->grille[y_init][x_init]){

         case 1:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/cyan.png");
            couleur = 1;
            break;

         case 2:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/blue.png");
            couleur = 2;
            break;

         case 3:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/green.png");
            couleur = 3;
            break;

         case 4:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/orange.png");
            couleur = 4;
            break;

         case 5:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/purple.png");
            couleur = 5;
            break;

         case 6:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/red.png");
            couleur = 6;
            break;

         case 7:
            vf->image[(y_dest * vf->mf->largeur) + x_dest] = gtk_image_new_from_file("images/yellow.png");
            couleur = 7;
            break;

         default:
            break;
      }
return couleur;
} //charge_1couleur_deplacement()

void charge_images_aleatoires( VueFive *vf){
   assert(vf != NULL);

   srand(time(NULL));
   for(int i = 0; i < vf->mf->symbolesTour; i++){
      vf->couleur_actuelle[i] = (rand () % vf->mf->typeSymboles) + 1;
      switch (vf->couleur_actuelle[i]){
         
         case 1:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/cyan.png");
            break;
            
         case 2:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/blue.png");
            break;

         case 3:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/green.png");
            break;

         case 4:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/orange.png");
            break;

         case 5:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/purple.png");
            break;

         case 6:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/red.png");
            break;

         case 7:
            vf->image_aleatoire[i] = gtk_image_new_from_file("images/yellow.png");
            break;
         
         default:
            break;
      }
   }
} //charge_images_aleatoires()

void charge_1couleur(VueFive *vf , int position_une_des_images_aleatoires, int position){
   assert(vf != NULL && position_une_des_images_aleatoires >= 0 && position_une_des_images_aleatoires < vf->mf->symbolesTour + 1 && position >= 0 && position < vf->mf->cellules);

   switch (vf->couleur_actuelle[position_une_des_images_aleatoires]){
      
      case 1:
         vf->image[position] = gtk_image_new_from_file("images/cyan.png");
         break;

      case 2:
         vf->image[position] = gtk_image_new_from_file("images/blue.png");
         break;

      case 3:
         vf->image[position] = gtk_image_new_from_file("images/green.png");
         break;

      case 4:
         vf->image[position] = gtk_image_new_from_file("images/orange.png");
         break;

      case 5:
         vf->image[position] = gtk_image_new_from_file("images/purple.png");
         break;

      case 6:
         vf->image[position] = gtk_image_new_from_file("images/red.png");
         break;

      case 7:
         vf->image[position] = gtk_image_new_from_file("images/yellow.png");
         break;
      
      default:
         break;
   }
} //charge_1couleur()

void compteur_case_libre_ajoute_images_aleatoire(VueFive *vf){
   assert(vf != NULL);
   int cpt = 0;
   for(int i = 0; i < vf->mf->hauteur; i++){
      for(int j = 0; j < vf->mf->largeur; j++){
         if(vf->mf->grille[i][j] == 0){
            cpt += 1;
         }
         if(cpt == vf->mf->symbolesTour){
            i = vf->mf->hauteur;
            j = vf->mf->largeur;
         }
      }
   }
   switch(cpt){
      case 7:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[6]), vf->image_aleatoire[6]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[5]), vf->image_aleatoire[5]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[4]), vf->image_aleatoire[4]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[3]), vf->image_aleatoire[3]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[2]), vf->image_aleatoire[2]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      case 6:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[5]), vf->image_aleatoire[5]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[4]), vf->image_aleatoire[4]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[3]), vf->image_aleatoire[3]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[2]), vf->image_aleatoire[2]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      case 5:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[4]), vf->image_aleatoire[4]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[3]), vf->image_aleatoire[3]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[2]), vf->image_aleatoire[2]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      case 4:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[3]), vf->image_aleatoire[3]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[2]), vf->image_aleatoire[2]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      case 3:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[2]), vf->image_aleatoire[2]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;
      case 2:

         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[1]), vf->image_aleatoire[1]);
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      case 1:
         gtk_button_set_image(GTK_BUTTON(vf->bouton_aleatoire[0]), vf->image_aleatoire[0]);
         break;

      default:
         break;
   }
} //compteur_case_libre_ajoute_images_aleatoire

void redessiner(VueFive *vf){
   assert (vf != NULL);

   int score_courante = 0;
   char *char_score;

   //transformer le score en chaîne de caractères
   score_courante = vf->mf->score;

   char_score = int_vers_char(score_courante);

   //Redessiner
   gtk_label_set_text(GTK_LABEL(vf->Score), char_score);

}//fin redessiner()

char *int_vers_char(int d){

   char *arr = malloc(11*sizeof(char)); //10 chiffres + '\0'
   if(arr == NULL)
      return NULL;

   sprintf(arr , "%d", d);

   return arr;
}//fin int_vers_char()