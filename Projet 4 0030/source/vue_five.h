#ifndef __VUE_FIVE__
#define __VUE_FIVE__

#include <gtk/gtk.h>

#include "modele_five.h"

/**
 * \file vue_five.h
 * \brief Vue (pattern MVC) pour la gestion du jeu five
 * \author Lucas Lolo
 * \author Marzouk Ouro-Gomma
 * \version 1.0
 * \date 2/5/2021
 *
 * Gestion d'un five via une approche MVC.Ce module gère l'aspect vue.
 * La vue contient l'image de chaque case de la grille.
 */
 
/**
 * \brief Implémentation de la vue pour le jeu five
 */
typedef struct vue_t{

   ModeleFive *mf; /*!< modèle du five */
   GtkWidget **image; /*!< le nombre d'image à insirer dans chaque bouton */
   GtkWidget **image_aleatoire; /*!< le nombre d'image à insirer dans les boutons aleatoires*/
   GtkWidget **bouton_aleatoire; /*!< le nombre de boutons aleatoires */
   GtkWidget *Score; /*!< le score courant à affiché sur le jeu*/
   int *couleur_actuelle; /*!< la position des boutons contenant les informations prochaines */
}VueFive;

/**
 * \fn VueFive *creer_vue_five(ModeleFive *mf)
 * \brief Crée une vue pour le five en fonction d'un certain modèle.
 *
 * \param mo le modèle du five à prendre en compte.
 *
 * \return VueFive *, un pointeur sur une nouvelle vue.
 *         NULL en cas d'erreur.
 */
VueFive *creer_vue_five(ModeleFive *mf);

/**
 * \fn void charge_images_aleatoire( VueFive *vf);
 * \brief 
 *
 * \param vf la vue à modifier (ne peut être NULL).
 */
void charge_images_aleatoires( VueFive *vf);

/**
 * \fn void charge_1couleur(VueFive *vf , int position_une_des_trois_images, int position);
 * \brief 
 *
 * \param vf la vue à modifier (ne peut être NULL).
 * \param position_une_des_images_aleatoires est l'une des 3 ou 7 images au dessus du jeu
 * \param position est la position d'une case libre du jeu
 */
void charge_1couleur(VueFive *vf , int position_une_des_images_aleatoires, int position);

/**
 * \fn void compteur_case_libre_ajoute_images_aleatoire(VueFive *vf);
 * \brief 
 *
 * \param vf le vue à modifier (ne peut être NULL).
 */
void compteur_case_libre_ajoute_images_aleatoire(VueFive *vf);

/**
 * \fn void redessiner(vue_Five *vf)
 * \brief Redessine la vue suite à un changement de score.
 *
 * \param vf la vue à redessiner.
 */
void redessiner(VueFive *vf);

/**
 * \fn char *int_vers_char(int d)
 * \brief Transforme un int en chaîne de caractères
 *
 * \param d le int à transformer.
 *
 * \return char *, la chaîne de caratères résultante.
 *         NULL en cas d'erreur
 */
char *int_vers_char(int d);

/**
 * \fn int charge_1couleur_deplacement(VueFive *vf, int y_init, int x_init, int y_dest, int x_dest)
 *
 * \param vf la vue à modifier (ne peut être NULL).
 * \param y_init la hauteur du premier click
 * \param x_init la largeur du premier click
 * \param y_dest la hauteur du deuxieme click
 * \param x_dest la largeur du deuxieme click
 * 
 * \return: 
*  Retourne la couleur du premier click:
*        1 = cyan
*        2 = blue
*        3 = green
*        4 = orange
*        5 = purple
*        6 = red
*        7 = yellow
*     
*/
int charge_1couleur_deplacement(VueFive *vf, int y_init, int x_init, int y_dest, int x_dest);

#endif