/*
 * Projet 4 ("FIVE OR MORE")
 * 
 *
 * Pour compiler:
 *  $>make all
 *
 * Pour générer la documentation:
 *  $>make doc
 *
 * Pour nettoyer le répertoire:
 *  $>make clean
 *
 * @author: Lucas Lolo
 * @author: Marzouk Ouro-Gomma
 * Mise à jour: 2 mai 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "controleur_five.h"
#include "vue_five.h"
#include "modele_five.h"

#define LONGUEUR_FENETRE 500
#define LARGEUR_FENETRE 500


int main(int argc, char *argv[]){
   char *optstring = ":n:f:";
   char *niveauUtilisateur;
   char *fichier_source;
   int getopt_val;
   //Ligne de commande 
   if(argc != 5){
      printf("Vous avez mal complété la commande\n");
      return -2;
   }
   else{
      while((getopt_val = getopt(argc, argv, optstring)) != EOF){
         switch(getopt_val){
            case 'n':
               niveauUtilisateur = optarg;
               printf("niveau Utilisateur : %s\n", niveauUtilisateur);
               break;
            case 'f':
               fichier_source = optarg;
               printf("fichier source : %s\n", fichier_source);
               break;
            case '?':
               printf("Option inconue : %c\n", optopt);
               break;
            case ':':
               printf("Argument manquant : %c\n", optopt);
               break;
            default:
               printf("Vous avez mal complété la commande\n");
               return -2;
         }
      }
   }

   //conversion de char à int 
   
   int niveau_utilisateur = atoi(niveauUtilisateur);

   if(niveau_utilisateur < 0 || niveau_utilisateur > 2){
      printf("Le niveau doit etre 0, 1 ou 2 et non %d!\n", niveau_utilisateur);
      return EXIT_FAILURE;
   }
   

   //création d'un modèle du five
   ModeleFive *mf = creer_modele_five(niveau_utilisateur);
   if(mf == NULL){
      return EXIT_FAILURE;
   }
   
   //création d'une vue du five 
   VueFive *vf = creer_vue_five(mf); 
   if(vf == NULL){
      return EXIT_FAILURE;
   }
   
   //création du contrôleur du five
   ControleurFive *cf = creer_controleur_five(vf, mf);
   if(cf == NULL){
      return EXIT_FAILURE;
   }

   GtkWidget *Fenetre_Principale;
   GtkWidget *pVBox;
   GtkWidget *pHBox;
   GtkWidget *information_suivants;
   GtkWidget *information_score;
   GtkWidget *Barre_menu;
   char *char_score;

   //initialisation de l'environnement GTK
   gtk_init(&argc, &argv);

   //création de la fenêtre
   Fenetre_Principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(Fenetre_Principale), "five or more");
   gtk_window_set_default_size(GTK_WINDOW(Fenetre_Principale), LONGUEUR_FENETRE, LARGEUR_FENETRE);
   gtk_window_set_position(GTK_WINDOW(Fenetre_Principale), GTK_WIN_POS_CENTER);

   g_signal_connect(G_OBJECT(Fenetre_Principale), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   
   cf->fichier_score = fichier_source;
   Barre_menu = click_creer_menu(Fenetre_Principale, cf);

   information_suivants = gtk_label_new("Suivants:");
   information_score = gtk_label_new("Score:"); 
   
   gtk_label_set_justify(GTK_LABEL(information_suivants), GTK_JUSTIFY_FILL);
   gtk_label_set_justify(GTK_LABEL(information_score), GTK_JUSTIFY_FILL);

   //affiche la barre de menu
   pVBox = gtk_vbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), Barre_menu, FALSE, FALSE, 3);

   //affiche le bouton des informations
   char_score = int_vers_char(cf->mf->score);
   vf->Score = gtk_label_new(char_score);
   
   //affiche les 3 ou 7 boutons au dessus
   pHBox = gtk_hbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pHBox), information_suivants, TRUE, TRUE, 0);
   for(int i = 0; i < mf->symbolesTour; i++){
   gtk_box_pack_start(GTK_BOX(pHBox), vf->bouton_aleatoire[i], FALSE, FALSE, 0);
   }
   gtk_box_pack_start(GTK_BOX(pHBox), information_score, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pHBox), vf->Score, TRUE, FALSE, 0);

   //affiche les boutons du jeu
   for(int i = 0; i < cf->mf->cellules; i++){
      if(i % cf->mf->largeur == 0){
         pHBox = gtk_hbox_new(TRUE, 0);
         gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);
      }
      gtk_box_pack_start(GTK_BOX(pHBox), cf->bouton[i], TRUE, TRUE, 0);
      g_signal_connect(G_OBJECT(cf->bouton[i]), "clicked", G_CALLBACK(click_init), cf);
   }
   
   gtk_container_add(GTK_CONTAINER(Fenetre_Principale), pVBox);
   gtk_widget_show_all(Fenetre_Principale);

   gtk_main();

return EXIT_SUCCESS;
}//fin programme