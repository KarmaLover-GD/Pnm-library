#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "controleur_five.h"

ControleurFive *creer_controleur_five(VueFive *vf, ModeleFive *mf){

   ControleurFive *cf = malloc(sizeof(ControleurFive));
   if(cf == NULL){
      return NULL;
   }
   
   
   cf->vf = vf;
   cf->mf = mf;
   cf->bouton = g_new(GtkWidget*, cf->mf->cellules);
   cf->nombre = 0;

   for(int i = 0; i < cf->mf->hauteur; i++){
      for(int j = 0; j < cf->mf->largeur; j++){
      cf->bouton[(i * cf->mf->largeur) + j] = gtk_button_new();
      gtk_container_add(GTK_CONTAINER(cf->bouton[(i * cf->mf->largeur) + j]), cf->vf->image[(i * cf->mf->largeur) + j]);
      change_valeur(cf->mf, i, j, 0); 
      }
   }
   
   ajoute_images(cf);
   charge_images_aleatoires(cf->vf);
   compteur_case_libre_ajoute_images_aleatoire(cf->vf);


return cf;
}//fin creer_controleur_five() 

void click_init(GtkWidget *click_init, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;
   if( cf->nombre == 0){
      for(int i = 0; i < cf->mf->hauteur; i++){
         for(int j = 0; j < cf->mf->largeur; j++){
            if(click_init == cf->bouton[(i * cf->mf->largeur) + j] && cf->mf->grille[i][j] != 0 && cf->nombre == 0){
               cf->x_init = j;
               cf->y_init = i;
               cf->nombre += 1;
            }
         }
      }
   }
   if( cf->nombre == 1){
      for(int i = 0; i < cf->mf->cellules; i++){
         g_signal_connect(G_OBJECT(cf->bouton[i]), "clicked", G_CALLBACK(position_dest_et_jeu_principale), cf);
      }
   }     
} // fin click_init()

void position_dest_et_jeu_principale(GtkWidget *click_dest, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;
   int score_horizontale = 0;
   int score_verticale = 0;
   int score_croissant1 = 0;
   int score_croissant2 = 0; 
   int score_decroissant1 = 0;
   int score_decroissant2 = 0;
   if(cf->nombre == 1){
      int i;
      for(i = 0; i < cf->mf->hauteur; i++){
         for(int j = 0; j < cf->mf->largeur; j++){ 
            if(click_dest == cf->bouton[(i * cf->mf->largeur) + j] && cf->mf->grille[i][j] == 0 && cf->nombre == 1){

               cf->x_dest = j;
               cf->y_dest = i;
               cf->nombre += 1;
            }
         }
      }
      if(cf->nombre == 1 && i == cf->mf->hauteur - 1){

         cf->nombre = 0;
      }
   }
   
   if(cf->nombre == 2){
      int impossible = deplacement(cf);
      if (impossible == 0){
         ajoute_images(cf);
         score_horizontale = verification_horizontale(cf);
         score_verticale = verification_verticale(cf);
         score_croissant1 = oblique_croissant1(cf);
         score_croissant2 = oblique_croissant2(cf);
         score_decroissant1 = oblique_decroissant1(cf);
         score_decroissant2 = oblique_decroissant2(cf);
         cf->mf->score += score_horizontale + score_verticale + score_croissant1 + score_croissant2 + score_decroissant1 + score_decroissant2;
         redessiner(cf->vf);
         int compteur = case_blanche_compteur(cf->mf);
         charge_images_aleatoires(cf->vf);
         compteur_case_libre_ajoute_images_aleatoire(cf->vf);
         cf->nombre = 0;
         //fin du jeu si compteur egale a zero
         if(compteur == 0){
            classement(cf->mf);
            cf->nombre = 0;
         }
      }
   }
} //position_dest_et_jeu_principale()

GtkWidget *click_creer_menu(GtkWidget *Fenetre_Principale, ControleurFive *cf){

   cf->Fenetre = Fenetre_Principale;
   //Déclaration de la barre du menu
   GtkWidget *barre_menu;

   //Déclaration du bouton partie avec ses sous repertoires
   GtkWidget *menu_partie;
   GtkWidget *item_partie;
   GtkWidget *item_nouvelle_partie;
   GtkWidget *item_liste_score;
   GtkWidget *item_quitter;
   GtkWidget *item_separateur;

   //Déclaration du bouton niveau avec ses sous repertoires
   GtkWidget *menu_niveau;                                         
   GtkWidget *item_niveau;
   GtkWidget *item_facile;
   GtkWidget *item_moyen;
   GtkWidget *item_difficile;
  
   //Déclaration du bouton aide avec son sous repertoire
   GtkWidget *menu_aide;
   GtkWidget *item_aide; 
   GtkWidget *item_createurs_jeu;
   
   GtkAccelGroup *accelerateur = NULL;

   //barre de menu
   barre_menu = gtk_menu_bar_new();

   //le menu "Partie"
   menu_partie = gtk_menu_new();

   //le menu "Niveau"
   menu_niveau = gtk_menu_new();

   //le menu "Aide"
   menu_aide = gtk_menu_new();

   //accélérateur
   accelerateur = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(Fenetre_Principale), accelerateur);

   //création des items pour la partie
   item_partie = gtk_menu_item_new_with_mnemonic("_Partie");
   item_nouvelle_partie = gtk_menu_item_new_with_mnemonic("_Nouvelle partie");
   item_liste_score = gtk_menu_item_new_with_mnemonic("_liste des scores");
   item_separateur = gtk_separator_menu_item_new();
   item_quitter = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accelerateur);

   //création des items pour les niveaux
   item_niveau = gtk_menu_item_new_with_mnemonic("_Niveau");
   item_facile = gtk_menu_item_new_with_mnemonic("_Facile");
   item_moyen = gtk_menu_item_new_with_mnemonic("_Moyen");
   item_difficile = gtk_menu_item_new_with_mnemonic("_Difficile");

   //création de l'item pour l'aide
   item_aide = gtk_menu_item_new_with_mnemonic("_Aide");
   item_createurs_jeu = gtk_menu_item_new_with_mnemonic("_Createurs de jeu");


   gtk_widget_add_accelerator(item_quitter, "activate", accelerateur,
   GDK_OR, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   //attacher les items de la partie
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_partie), menu_partie);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_nouvelle_partie);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_liste_score);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_separateur);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_quitter);
   gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_partie);

   //attacher les items du niveau
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_niveau), menu_niveau);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_facile);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_moyen);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_difficile);
   gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_niveau);

   //attacher l'item de l'aide
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_aide), menu_aide);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), item_createurs_jeu);
   gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_aide);
   
   //les signaux
   g_signal_connect(G_OBJECT(item_nouvelle_partie), "activate", G_CALLBACK(nouvelle_partie), cf);
   g_signal_connect(G_OBJECT(item_liste_score), "activate", G_CALLBACK(liste_score), cf);
   g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(gtk_main_quit), cf);
   g_signal_connect(G_OBJECT(item_facile), "activate", G_CALLBACK(facile), cf);          
   g_signal_connect(G_OBJECT(item_moyen), "activate", G_CALLBACK(moyen), cf);       
   g_signal_connect(G_OBJECT(item_difficile), "activate", G_CALLBACK(difficile), cf);  
   g_signal_connect(G_OBJECT(item_createurs_jeu), "activate", G_CALLBACK(aide), NULL);             

return barre_menu;

}//fin creer_menu()

void facile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;
   if(cf->mf->niveau != 0){
      nouvelle_fenetre_niveau(0, Nouvelle_Fenetre_Niveau, cf);
   } 
}// fin facile()

void moyen(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;
   if(cf->mf->niveau != 1){
      nouvelle_fenetre_niveau(1, Nouvelle_Fenetre_Niveau, cf);
   } 
}// fin moyen

void difficile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;
   if(cf->mf->niveau != 2){
         nouvelle_fenetre_niveau(2, Nouvelle_Fenetre_Niveau, cf);
   } 
}// fin difficile()

void liste_score(GtkWidget *Fenetre_Score, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;

   Fenetre_Score = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(Fenetre_Score), "Liste des meilleures joueurs");
   gtk_window_set_default_size(GTK_WINDOW(Fenetre_Score), LONGUEUR_FENETRE_AUTRES, LARGEUR_FENETRE_AUTRES);
   gtk_window_set_position(GTK_WINDOW(Fenetre_Score), GTK_WIN_POS_CENTER);

   char *classement = affiche_classement_score(cf);
   GtkWidget *Label = gtk_label_new(classement);
   gtk_container_add(GTK_CONTAINER(Fenetre_Score), Label);
   
   gtk_widget_show_all(Fenetre_Score);
   g_signal_connect(G_OBJECT(Fenetre_Score), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   gtk_main();
}// fin liste_score()


void aide(GtkWidget *Fenetre_Aide){

   GtkWidget *Label;
   gchar* sUtf8;
   Fenetre_Aide = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(Fenetre_Aide), "Createurs du jeu");
   gtk_window_set_default_size(GTK_WINDOW(Fenetre_Aide), LONGUEUR_FENETRE_AUTRES, LARGEUR_FENETRE_AUTRES);
   gtk_window_set_position(GTK_WINDOW(Fenetre_Aide), GTK_WIN_POS_CENTER);

   Label = gtk_label_new(NULL);
   sUtf8 = g_locale_to_utf8("<span foreground=\"#00CC00\">Five Or More </span>\n<span foreground=\"#00FFFF\"> Lucas et Marzouk</span>\n<span foreground=\"#EE21EE\"> (ULiege)Cours Info0030</span>",-1, NULL, NULL, NULL);
   gtk_label_set_markup(GTK_LABEL(Label), sUtf8);
   g_free(sUtf8);
   gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);
   gtk_container_add(GTK_CONTAINER(Fenetre_Aide), Label);
   gtk_widget_show_all(Fenetre_Aide);

   g_signal_connect(G_OBJECT(Fenetre_Aide), "destroy",G_CALLBACK(gtk_main_quit), NULL);

   gtk_main();
}// fin aide()

void nouvelle_partie(GtkWidget *bouton, gpointer data){
   ControleurFive *cf = (ControleurFive *)data;

   cf->mf->score = 0;
   redessiner(cf->vf);
   for (int i = 0; i < cf->mf->hauteur;  i++){
      for (int j = 0; j < cf->mf->largeur;  j++){
         if(cf->mf->grille[i][j] != 0){
            cf->vf->image[(i * cf->mf->largeur) + j] = gtk_image_new_from_file("images/default.png");
            gtk_button_set_image(GTK_BUTTON(cf->bouton[(i * cf->mf->largeur) + j]), cf->vf->image[(i * cf->mf->largeur) + j]);
            change_valeur(cf->mf, i, j, 0);
         }
      }
   }
   charge_images_aleatoires(cf->vf);
   compteur_case_libre_ajoute_images_aleatoire(cf->vf);
   ajoute_images(cf);

}//fin nouvelle_partie()

void ajoute_images( ControleurFive *cf){
   assert( cf != NULL);

   int *Donnet = malloc(cf->mf->symbolesTour *(sizeof(int)));
   int i = 0;
   while(i < cf->mf->symbolesTour){
      int largeur = 0;
      int hauteur = 0;
        
      Donnet[i] = generation_image_aleatoire(cf->mf);
      if(Donnet[i] != 1000){
         int position = Donnet[i];
         charge_1couleur(cf->vf, i, position);
         gtk_button_set_image(GTK_BUTTON(cf->bouton[position]), cf->vf->image[position]);
         largeur = position % cf->mf->largeur;
         hauteur = position / cf->mf->largeur;
         change_valeur(cf->mf, hauteur, largeur, cf->vf->couleur_actuelle[i]); 
         i++;
      }
      else if (Donnet[i] == 1000){
         i = cf->mf->symbolesTour;
      }
   }
   free(Donnet);
} // fin ajoute_images()

void nouvelle_fenetre_niveau(int nouveau_niveau, GtkWidget *Nouvelle_Fenetre_Niveau, ControleurFive *cf){
   GtkWidget *Barre_menu;
   GtkWidget *pVBox;
   GtkWidget *pHBox;
   GtkWidget *information_suivants;
   GtkWidget *information_score;
   char *char_score;
   free(cf->vf->couleur_actuelle);
   g_signal_connect(G_OBJECT(cf->Fenetre), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   gtk_widget_destroy(cf->Fenetre);
   Nouvelle_Fenetre_Niveau = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(Nouvelle_Fenetre_Niveau), "Five or more");
   gtk_window_set_default_size(GTK_WINDOW(Nouvelle_Fenetre_Niveau), LONGUEUR_FENETRE, LARGEUR_FENETRE);
   gtk_window_set_position(GTK_WINDOW(Nouvelle_Fenetre_Niveau), GTK_WIN_POS_CENTER);
   
   cf->mf = creer_modele_five(nouveau_niveau);
   //création d'une vue du five 
   cf->vf = creer_vue_five(cf->mf); 
   
   //création du contrôleur du five
   cf = creer_controleur_five(cf->vf,cf->mf);
   
   Barre_menu = click_creer_menu(Nouvelle_Fenetre_Niveau, cf);
   information_suivants = gtk_label_new("Suivants:");
   information_score = gtk_label_new("Score:"); 
   
   gtk_label_set_justify(GTK_LABEL(information_suivants), GTK_JUSTIFY_FILL);
   gtk_label_set_justify(GTK_LABEL(information_score), GTK_JUSTIFY_FILL);

   //affiche la barre de menu
   pVBox = gtk_vbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), Barre_menu, FALSE, FALSE, 3);
   
   //affiche le bouton des informations
   char_score = int_vers_char(cf->mf->score);
   cf->vf->Score = gtk_label_new(char_score);
   
   pHBox = gtk_hbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pHBox), information_suivants, TRUE, TRUE, 0);
   for(int i = 0; i < cf->mf->symbolesTour; i++){
   gtk_box_pack_start(GTK_BOX(pHBox), cf->vf->bouton_aleatoire[i], FALSE, FALSE, 0);
   }
   gtk_box_pack_start(GTK_BOX(pHBox), information_score, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pHBox), cf->vf->Score, TRUE, FALSE, 0);
   
   //affiche les boutons du jeu
   for(int i = 0; i < cf->mf->cellules; i++){
      if(i % cf->mf->largeur == 0){
         pHBox = gtk_hbox_new(TRUE, 0);
         gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);
      }
      gtk_box_pack_start(GTK_BOX(pHBox), cf->bouton[i], TRUE, TRUE, 0);
      g_signal_connect(G_OBJECT(cf->bouton[i]), "clicked", G_CALLBACK(click_init), cf);
   }
   
   gtk_container_add(GTK_CONTAINER(Nouvelle_Fenetre_Niveau), pVBox);
   gtk_widget_show_all(Nouvelle_Fenetre_Niveau);
   g_signal_connect(G_OBJECT(Nouvelle_Fenetre_Niveau), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   
   gtk_main();
}



         
int verification_horizontale( ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo; ComboAll >= 5; ComboAll--){
      for(int k = 0; k < cf->mf->avancer_tableau_horizontale; k++){
         for(int i = 0; i < cf->mf->hauteur; i++){
            for(int j = 1; j < cf->mf->typeSymboles+1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j  && cf->mf->grille[i][7+k] == j 
                     && cf->mf->grille[i][8+k] == j && cf->mf->grille[i][9+k] == j && cf->mf->grille[i][10+k] == j && cf->mf->grille[i][11+k] == j
                     && cf->mf->grille[i][12+k] == j && cf->mf->grille[i][13+k] == j && 13 + k < cf->mf->largeur){

                     score +=SCORE_COMBO_14;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j  && cf->mf->grille[i][7+k] == j
                     && cf->mf->grille[i][8+k] == j  && cf->mf->grille[i][9+k] == j  && cf->mf->grille[i][10+k] == j  && cf->mf->grille[i][11+k] == j
                     && cf->mf->grille[i][12+k] == j && 12 + k < cf->mf->largeur){

                     score +=SCORE_COMBO_13;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && cf->mf->grille[i][7+k] == j
                     && cf->mf->grille[i][8+k] == j && cf->mf->grille[i][9+k] == j && cf->mf->grille[i][10+k] == j && cf->mf->grille[i][11+k] == j
                     && 11 + k < cf->mf->largeur){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && cf->mf->grille[i][7+k] == j 
                     && cf->mf->grille[i][8+k] == j && cf->mf->grille[i][9+k] == j && cf->mf->grille[i][10+k] == j && 10 + k < cf->mf->largeur){

                     score += SCORE_COMBO_11;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && cf->mf->grille[i][7+k] == j
                     && cf->mf->grille[i][8+k] == j&& cf->mf->grille[i][9+k] == j && 9 + k < cf->mf->largeur){

                     score += SCORE_COMBO_10;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && cf->mf->grille[i][7+k] == j
                     && cf->mf->grille[i][8+k] == j && 8 + k < cf->mf->largeur){

                     score += SCORE_COMBO_9;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && cf->mf->grille[i][7+k] == j 
                     && 7 + k < cf->mf->largeur){

                     score += SCORE_COMBO_8;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && cf->mf->grille[i][6+k] == j && 6 + k < cf->mf->largeur){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && cf->mf->grille[i][5+k] == j && 5 + k < cf->mf->largeur){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[i][0+k] == j && cf->mf->grille[i][1+k] == j && cf->mf->grille[i][2+k] == j && cf->mf->grille[i][3+k] == j 
                     && cf->mf->grille[i][4+k] == j && 4 + k < cf->mf->largeur ){

                     score += SCORE_COMBO_5;
                     charge_modifie_combo_horizontale(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
return score;
}//fin victoire horizontale

int verification_verticale( ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo ; ComboAll >= 5 ; ComboAll--){
      for(int k = 0; k < cf->mf->avancer_tableau_verticale; k++){
         for(int i = 0; i < cf->mf->largeur; i++){
            for(int j = 1; j< cf->mf->typeSymboles+1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i]  == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j  && cf->mf->grille[9+k][i]  == j && cf->mf->grille[10+k][i]  == j && cf->mf->grille[11+k][i]  == j
                     && cf->mf->grille[12+k][i] == j && cf->mf->grille[13+k][i]  == j && 13 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_14;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i]  == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j  && cf->mf->grille[9+k][i]  == j && cf->mf->grille[10+k][i]  == j && cf->mf->grille[11+k][i]  == j
                     && cf->mf->grille[12+k][i] && 12 + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_13;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i]  == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j  && cf->mf->grille[9+k][i]  == j && cf->mf->grille[10+k][i]  == j && cf->mf->grille[11+k][i]  == j
                     && 11 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i]  == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j  && cf->mf->grille[9+k][i]  == j && cf->mf->grille[10+k][i] && 10 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_11;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i] == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i] == j && cf->mf->grille[6+k][i] == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j  && cf->mf->grille[9+k][i] == j && 9 + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_10;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i] == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i] == j && cf->mf->grille[6+k][i] == j  && cf->mf->grille[7+k][i]  == j
                     && cf->mf->grille[8+k][i]  == j && 8 + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_9;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i]  == j  && cf->mf->grille[7+k][i]  == j
                     && 7 + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_8;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i]  == j && cf->mf->grille[6+k][i] && 6 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && cf->mf->grille[5+k][i] && 5 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[0+k][i] == j && cf->mf->grille[1+k][i] == j && cf->mf->grille[2+k][i]  == j && cf->mf->grille[3+k][i]  == j 
                     && cf->mf->grille[4+k][i] == j && 4 + k < cf->mf->hauteur){

                     score += SCORE_COMBO_5;
                     charge_modifie_combo_verticale(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
return score;
}//fin victiore verticale


int oblique_croissant1(ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo; ComboAll >= 5; ComboAll--){
      for(int i = 0; i < cf->mf->largeur - 3; i++){ 
         for(int k = 0; k < cf->mf->avancer_tableau_oblique; k++){
            for(int j = 1; j< cf->mf->typeSymboles +1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-10-k][9+i+k] == j && cf->mf->grille[cf->mf->hauteur-11-k][10+i+k] == j && cf->mf->grille[cf->mf->hauteur-12-k][11+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-13-k][12+i+k] == j && cf->mf->grille[cf->mf->hauteur-14-k][13+i+k] == j && 13 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_14;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-10-k][9+i+k] == j && cf->mf->grille[cf->mf->hauteur-11-k][10+i+k] == j && cf->mf->grille[cf->mf->hauteur-12-k][11+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-13-k][12+i+k] == j && 12 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_13;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-10-k][9+i+k] == j && cf->mf->grille[cf->mf->hauteur-11-k][10+i+k] == j && cf->mf->grille[cf->mf->hauteur-12-k][11+i+k] == j
                     && 11 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-10-k][9+i+k] == j && cf->mf->grille[cf->mf->hauteur-11-k][10+i+k] == j && 10 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_11;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && cf->mf->grille[cf->mf->hauteur-10-k][9+i+k] == j && 9 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_10;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && cf->mf->grille[cf->mf->hauteur-9-k][8+i+k] == j
                     && 8 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_9;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && cf->mf->grille[cf->mf->hauteur-8-k][7+i+k] == j && 7 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_8;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-7-k][6+i+k] == j && 6 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && cf->mf->grille[cf->mf->hauteur-6-k][5+i+k] == j
                     && 5 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[cf->mf->hauteur-1-k][0+i+k] == j && cf->mf->grille[cf->mf->hauteur-2-k][1+i+k] == j && cf->mf->grille[cf->mf->hauteur-3-k][2+i+k] == j 
                     && cf->mf->grille[cf->mf->hauteur-4-k][3+i+k] == j && cf->mf->grille[cf->mf->hauteur-5-k][4+i+k] == j && 4 + i + k < cf->mf->largeur){

                     score += SCORE_COMBO_5;
                     charge_modifie_combo_croissant1(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
return score;
}

int oblique_croissant2(ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo; ComboAll >= 5; ComboAll--){
      for(int i = 4;i < cf->mf->hauteur - 1; i++){
         for(int k = 0; k < cf->mf->avancer_tableau_oblique - 1; k++){ // mettre 11 en dans la structure
            for(int j = 1; j< cf->mf->typeSymboles + 1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && cf->mf->grille[i-9-k][9+k] == j && cf->mf->grille[i-10-k][10+k] == j && cf->mf->grille[i-11-k][11+k] == j
                     && cf->mf->grille[i-12-k][12+k] == j && cf->mf->grille[i-13-k][13+k] == j && 13 + k < cf->mf->largeur && i - 6 - k >= 13){

                     score += SCORE_COMBO_14;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && cf->mf->grille[i-9-k][9+k] == j && cf->mf->grille[i-10-k][10+k] == j && cf->mf->grille[i-11-k][11+k] == j
                     && cf->mf->grille[i-12-k][12+k] == j && 12 + k < cf->mf->largeur && i - 12 - k >= 0){

                     score += SCORE_COMBO_13;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && cf->mf->grille[i-9-k][9+k] == j && cf->mf->grille[i-10-k][10+k] == j && cf->mf->grille[i-11-k][11+k] == j
                     && 11 + k < cf->mf->largeur && i - 11 - k >= 0){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && cf->mf->grille[i-9-k][9+k] == j && cf->mf->grille[i-10-k][10+k] == j && 10 + k < cf->mf->largeur
                     && i - 10 - k >= 0){
                     
                     score += SCORE_COMBO_11;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && cf->mf->grille[i-9-k][9+k] == j && 9 + k < cf->mf->largeur && i - 9 - k >= 0){

                     score += SCORE_COMBO_10;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && cf->mf->grille[i-8-k][8+k] == j && 8 + k < cf->mf->largeur && i - 8 - k >= 0){

                     score += SCORE_COMBO_9;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && cf->mf->grille[i-7-k][7+k] == j
                     && 7 + k < cf->mf->largeur && i - 7 - k >= 0){

                     score += SCORE_COMBO_8;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && cf->mf->grille[i-6-k][6+k] == j && 6 + k < cf->mf->largeur 
                     && i - 6 - k >= 0){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && cf->mf->grille[i-5-k][5+k] == j && 5 + k < cf->mf->largeur &&  i - 5 - k >= 0){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[i-0-k][0+k] == j && cf->mf->grille[i-1-k][1+k] == j && cf->mf->grille[i-2-k][2+k] == j && cf->mf->grille[i-3-k][3+k] == j 
                     && cf->mf->grille[i-4-k][4+k] == j && 4 + k < cf->mf->largeur && i - 4 - k >= 0){
                     
                     score += SCORE_COMBO_5;
                     charge_modifie_combo_croissant2(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
return score;
}

int oblique_decroissant1(ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo; ComboAll >= 5; ComboAll--){
      for(int k = 0; k < cf->mf->avancer_tableau_horizontale; k++){
         for(int i = 0; i < cf->mf->hauteur - 4; i++){
            for(int j = 1; j< cf->mf->typeSymboles + 1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && cf->mf->grille[9+i+k][9+k] == j
                     && cf->mf->grille[10+i+k][10+k] == j && cf->mf->grille[11+i+k][11+k] == j && cf->mf->grille[12+i+k][12+k] == j && cf->mf->grille[13+i+k][13+k] == j && 13 + k < cf->mf->largeur
                     && 13 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_14;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && cf->mf->grille[9+i+k][9+k] == j
                     && cf->mf->grille[10+i+k][10+k] == j && cf->mf->grille[11+i+k][11+k] == j && cf->mf->grille[12+i+k][12+k] == j && 12 + k < cf->mf->largeur && 12 + i + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_13;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && cf->mf->grille[9+i+k][9+k] == j
                     && cf->mf->grille[10+i+k][10+k] == j && cf->mf->grille[11+i+k][11+k] == j && 11 + k < cf->mf->largeur && 11 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && cf->mf->grille[9+i+k][9+k] == j
                     && cf->mf->grille[10+i+k][10+k] == j && 10 + k < cf->mf->largeur && 10 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_11;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && cf->mf->grille[9+i+k][9+k] == j
                     && 9 + k < cf->mf->largeur && 9 + i + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_10;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && cf->mf->grille[8+i+k][8+k] == j && 8 + k < cf->mf->largeur
                     && 8 + i + k < cf->mf->hauteur){
                     
                     score += SCORE_COMBO_9;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && cf->mf->grille[7+i+k][7+k] == j && 7 + k < cf->mf->largeur && 7 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_8;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && cf->mf->grille[6+i+k][6+k] == j && 6 + k < cf->mf->largeur && 6 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && cf->mf->grille[5+i+k][5+k] == j && 5 + k < cf->mf->largeur && 5 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[0+i+k][0+k] == j && cf->mf->grille[1+i+k][1+k] == j && cf->mf->grille[2+i+k][2+k] == j && cf->mf->grille[3+i+k][3+k] == j && cf->mf->grille[4+i+k][4+k] == j
                     && 4 + k < cf->mf->largeur && 4 + i + k < cf->mf->hauteur){

                     score += SCORE_COMBO_5;
                     charge_modifie_combo_decroissant1(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
   return score;
}

int oblique_decroissant2(ControleurFive *cf){
   assert( cf != NULL);

   int score = 0;
   for(int ComboAll = cf->mf->combo; ComboAll >= 5; ComboAll--){
      for(int i = 0;i < cf->mf->largeur - 5; i++){
         for(int k = 0; k < cf->mf->avancer_tableau_horizontale - 1; k++){ // mettre 11 en dans la structure
            for(int j = 1; j< cf->mf->typeSymboles+1; j++){
               if(ComboAll == 14){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && cf->mf->grille[9+k][i+10+k] == j && cf->mf->grille[10+k][i+11+k] == j && cf->mf->grille[11+k][i+12+k] == j
                     && cf->mf->grille[12+k][i+13+k] == j && cf->mf->grille[13+k][i+14+k] == j && i + 14 + k < cf->mf->largeur){
                     
                     score += SCORE_COMBO_14;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 13){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && cf->mf->grille[9+k][i+10+k] == j && cf->mf->grille[10+k][i+11+k] == j && cf->mf->grille[11+k][i+12+k] == j
                     && cf->mf->grille[12+k][i+13+k] == j && i + 13 + k < cf->mf->largeur){
                     
                     score += SCORE_COMBO_13;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 12){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && cf->mf->grille[9+k][i+10+k] == j && cf->mf->grille[10+k][i+11+k] == j && cf->mf->grille[11+k][i+12+k] == j
                     && i + 12 + k < cf->mf->largeur){

                     score += SCORE_COMBO_12;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 11){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && cf->mf->grille[9+k][i+10+k] == j && cf->mf->grille[10+k][i+11+k] == j  && i + 11 + k < cf->mf->largeur){

                     score += SCORE_COMBO_11;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 10){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && cf->mf->grille[9+k][i+10+k] == j  && i + 10 + k < cf->mf->largeur){

                     score += SCORE_COMBO_10;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 9){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && cf->mf->grille[8+k][i+9+k] == j
                     && i + 9 + k < cf->mf->largeur){

                     score += SCORE_COMBO_9;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 8){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && cf->mf->grille[7+k][i+8+k] == j && i + 8 + k < cf->mf->largeur){

                     score += SCORE_COMBO_8;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 7){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j
                     && cf->mf->grille[6+k][i+7+k] == j && i + 7 + k < cf->mf->largeur){

                     score += SCORE_COMBO_7;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 6){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j && cf->mf->grille[5+k][i+6+k] == j 
                      && i + 6 + k < cf->mf->largeur){

                     score += SCORE_COMBO_6;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
               else if(ComboAll == 5){
                  if(cf->mf->grille[0+k][i+1+k] == j && cf->mf->grille[1+k][i+2+k] == j && cf->mf->grille[2+k][i+3+k] == j
                     && cf->mf->grille[3+k][i+4+k] == j && cf->mf->grille[4+k][i+5+k] == j  && i + 5 + k < cf->mf->largeur){

                     score += SCORE_COMBO_5;
                     charge_modifie_combo_decroissant2(cf,ComboAll, k, i, j);
                  }
               }
            }
         }
      }
   }
return score;
}
void charge_modifie_combo_decroissant2(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[compteur+k][i+compteur+1+k] == j){
         
         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[(compteur+k) * cf->mf->largeur + (i+compteur+1+k)]), image[compteur]);
         change_valeur(cf->mf, compteur+k, i+compteur+1+k, 0);
      }
   }
}
void charge_modifie_combo_decroissant1(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[compteur+i+k][compteur+k] == j){
         
         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[((compteur+i+k) * cf->mf->largeur) + (compteur+k)]), image[compteur]);
         change_valeur(cf->mf,compteur+i+k, compteur+k, 0);
      }
   }
}
void charge_modifie_combo_croissant2(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[i - compteur - k][compteur + k] == j){

         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[((i - compteur - k) * cf->mf->largeur) + (compteur + k)]), image[compteur]);
         change_valeur(cf->mf, i - compteur - k, compteur + k, 0);
      }
   }
}
void charge_modifie_combo_croissant1(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[cf->mf->hauteur-compteur - 1 - k][compteur + i + k] == j){

         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[((cf->mf->hauteur-compteur - 1 - k) * cf->mf->largeur) + (compteur + i + k)]), image[compteur]);
         change_valeur(cf->mf, cf->mf->hauteur-compteur - 1 - k, compteur + i + k, 0);
      }
   }
} 

void charge_modifie_combo_verticale(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[compteur+k][i] == j){

         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[((compteur+k) * cf->mf->largeur) + i]), image[compteur]);
         change_valeur(cf->mf, compteur+k, i, 0);
      }
   }
} 

void charge_modifie_combo_horizontale(ControleurFive *cf,int ComboAll, int k, int i, int j){
   GtkWidget *image[ComboAll];
   for (int compteur = 0; compteur < ComboAll; compteur++){
      if(cf->mf->grille[i][compteur+k] == j){
         image[compteur] = gtk_image_new_from_file("images/default.png");
         gtk_button_set_image(GTK_BUTTON(cf->bouton[(i * cf->mf->largeur) + (compteur+k)]), image[compteur]);
         change_valeur(cf->mf, i, compteur+k, 0);
      }
   }
} 
int deplacement(ControleurFive *cf){

   int x_init = cf->x_init;
   int y_init = cf->y_init;
   int x_courant = cf->x_init;
   int y_courant = cf->y_init;
   int x_dest = cf->x_dest;
   int y_dest = cf->y_dest;
   int impossible = 1;
   int nombre_pas = 0;
   
   // verifions que l'on part d'une case pleine et que l'on se destine vers une case vide
   if(cf->mf->grille[y_init][x_init] != 0 && cf->mf->grille[y_dest][x_dest] == 0){
      x_init = x_init;
      x_dest = x_dest;
      y_init = y_init;
      y_dest = y_dest;
      x_courant = x_init;
      y_courant = y_init;
      impossible = 0;
   

      // commençons par l'algorithme montant
      while(((x_courant != x_dest) || (y_courant != y_dest)) && (impossible == 0)&& (nombre_pas < 200)){

         //prillegier la descente et la droite
         if(x_courant <= x_dest && y_courant <= y_dest){
            if(x_courant < x_dest && y_courant < y_dest){
               if(cf->mf->grille[y_courant+1][x_courant] == 0){
                  y_courant++;
                  nombre_pas++;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  x_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  x_courant--;
                  nombre_pas++;
               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant+1] == 0){
                  y_courant--;
                  x_courant++;
                  nombre_pas++;
               }else impossible = 1;

            }else if(x_courant < x_dest && y_courant == y_dest){
               if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  x_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant+1] == 0){
                  y_courant--;
                  x_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  x_courant--;
                  nombre_pas++;

               }else impossible = 1;

            }else if(x_courant == x_dest && y_courant < y_dest){
               if(cf->mf->grille[y_courant+1][x_courant] == 0){
                  y_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  x_courant++;
                  nombre_pas++;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  x_courant--;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant+1] == 0){
                  y_courant--;
                  x_courant++;
                  nombre_pas++;

               }else impossible = 1;
         
            }
         }
         
         // privillegier la desente à gauche
         else if(x_courant >= x_dest && y_courant <= y_dest){
            if(x_courant > x_dest && y_courant < y_dest){
               if(cf->mf->grille[y_courant+1][x_courant] == 0 && y_courant ){
                  y_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant-1] == 0 ){
                  x_courant--;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant-1] == 0){
                  y_courant--;
                  x_courant--;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant+1] == 0){
                  x_courant++;
                  nombre_pas++;

               }else impossible = 1;

            }else if(x_courant > x_dest && y_courant == y_dest){
               if(cf->mf->grille[y_courant][x_courant-1] == 0 ){
                  x_courant--;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant-1] == 0){
                  y_courant--;
                  x_courant--;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant+1] == 0){
                  x_courant--;
                  nombre_pas++;

               }else impossible = 1;

            }else if(x_courant == x_dest && y_courant < y_dest){
               if(cf->mf->grille[y_courant+1][x_courant] == 0){
                  y_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  x_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant-1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant+1] == 0){
                  y_courant--;
                  x_courant++;
                  nombre_pas++;

               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  x_courant--;
                  nombre_pas++;

               }else impossible = 1;
         
            }
         
         // montée  à droite
         }else if(x_courant <= x_dest && y_courant > y_dest){
            if(x_courant < x_dest && y_courant > y_dest){
               if(cf->mf->grille[y_courant-1][x_courant] == 0 ){
                  y_courant--;
                  nombre_pas++;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  x_courant++;
                  nombre_pas++;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant+1][x_courant+1]  == 0){
                  y_courant++;
                  nombre_pas++;
                  x_courant++;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  nombre_pas++;
                  x_courant--;
               }else impossible = 1;

            }else if(x_courant < x_dest && y_courant == y_dest){
               if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  nombre_pas++;
                  x_courant++;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant+1] == 0){
                  nombre_pas++;
                  y_courant++;
                  x_courant++;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  nombre_pas++;
                  x_courant--;
               }else impossible = 1;

            }else if(x_courant == x_dest && y_courant > y_dest){
               if(cf->mf->grille[y_courant-1][x_courant] == 0){
                  nombre_pas++;
                  y_courant--;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  nombre_pas++;
                  x_courant++;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
               nombre_pas++;
               x_courant--;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant+1][x_courant+1]  == 0){
                  y_courant++;
                  nombre_pas++;
                  x_courant++;
               
               }else impossible = 1;
         
            }
            // montée gauche
         }else if(x_courant > x_dest && y_courant >= y_dest){
            if(x_courant > x_dest && y_courant > y_dest){
               if(cf->mf->grille[y_courant-1][x_courant] == 0){
                  nombre_pas++;
                  y_courant--;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  nombre_pas++;
                  x_courant--;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant+1][x_courant-1] == 0){
                  y_courant++;
                  nombre_pas++;
                  x_courant--;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0){
                  nombre_pas++;
                  x_courant++;
               }else impossible = 1;

            }else if(x_courant > x_dest && y_courant == y_dest){
               if(cf->mf->grille[y_courant][x_courant-1] == 0 ){
                  nombre_pas++;
                  x_courant--;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant-1][x_courant-1] == 0){
                  y_courant++;
                  nombre_pas++;
                  x_courant--;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0){
                  nombre_pas++;
                  x_courant++;
               }else impossible = 1;

            }else if(x_courant == x_dest && y_courant > y_dest){
               if(cf->mf->grille[y_courant+1][x_courant] == 0){
                  nombre_pas++;
                  y_courant--;
               }else if(cf->mf->grille[y_courant][x_courant+1] == 0 ){
                  nombre_pas++;
                  x_courant++;
               }else if(cf->mf->grille[y_courant][x_courant-1] == 0){
                  nombre_pas++;
                  x_courant--;
               }else if(cf->mf->grille[y_courant+1][x_courant] == 0 && cf->mf->grille[y_courant+1][x_courant+1]  == 0){
                  nombre_pas++;
                  y_courant++;
                  x_courant++;
               
               }else impossible = 1;
         
            }
         }

         if(x_courant == x_dest && y_courant == y_dest){
            int couleur = charge_1couleur_deplacement(cf->vf, y_init, x_init, y_dest, x_dest);
            
            gtk_button_set_image(GTK_BUTTON(cf->bouton[(y_dest * cf->mf->largeur) + x_dest]), cf->vf->image[(y_dest * cf->mf->largeur) + x_dest]);
            change_valeur(cf->mf, y_dest, x_dest, couleur);

            GtkWidget *image_blanc = gtk_image_new_from_file("images/default.png");
            gtk_button_set_image(GTK_BUTTON(cf->bouton[(y_init * cf->mf->largeur) + x_init]), image_blanc);
            change_valeur(cf->mf, y_init, x_init, 0);
            
         }
         if(nombre_pas >= 199){
            impossible = 1;
            cf->nombre = 0;
         }
      }
   }

   if(impossible == 1){
      cf->nombre = 0;
   }
return impossible;
}
char *affiche_classement_score(ControleurFive *cf){

   char *classement_score;
   switch(cf->mf->nouvelle_partie){
      case 10 :
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d", cf->mf->ligneActuelle[9], cf->mf->ligneActuelle[8], cf->mf->ligneActuelle[7], cf->mf->ligneActuelle[6]
         , cf->mf->ligneActuelle[5], cf->mf->ligneActuelle[4], cf->mf->ligneActuelle[3], cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 9:
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d", cf->mf->ligneActuelle[8], cf->mf->ligneActuelle[7], cf->mf->ligneActuelle[6], cf->mf->ligneActuelle[5]
         , cf->mf->ligneActuelle[4], cf->mf->ligneActuelle[3], cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 7:
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d\n%d\n%d\n%d", cf->mf->ligneActuelle[6], cf->mf->ligneActuelle[5], cf->mf->ligneActuelle[4], cf->mf->ligneActuelle[3]
         , cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 6:
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d\n%d\n%d", cf->mf->ligneActuelle[5], cf->mf->ligneActuelle[4], cf->mf->ligneActuelle[3], cf->mf->ligneActuelle[2]
         , cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 5:
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d\n%d", cf->mf->ligneActuelle[4], cf->mf->ligneActuelle[3], cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1]
         , cf->mf->ligneActuelle[0]);
         break;
      case 4:
         classement_score = g_strdup_printf ("%d\n%d\n%d\n%d", cf->mf->ligneActuelle[3], cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 3:
         classement_score = g_strdup_printf ("%d\n%d\n%d", cf->mf->ligneActuelle[2], cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 2:
         classement_score = g_strdup_printf ("%d\n%d", cf->mf->ligneActuelle[1], cf->mf->ligneActuelle[0]);
         break;
      case 1:
         classement_score = g_strdup_printf ("%d", cf->mf->ligneActuelle[0]);
         break;
      case 0:
         classement_score = g_strdup_printf (" ");
         break;
   }
return classement_score;
}
