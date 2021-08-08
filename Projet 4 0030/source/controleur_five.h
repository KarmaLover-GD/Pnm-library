#ifndef __CONTROLEUR_FIVE__
#define __CONTROLEUR_FIVE__

#include <gtk/gtk.h>
#include <stdlib.h>

#include "modele_five.h"
#include "vue_five.h"

#define LONGUEUR_FENETRE_AUTRES 300
#define LARGEUR_FENETRE_AUTRES 100
#define LONGUEUR_FENETRE 500
#define LARGEUR_FENETRE 500

#define SCORE_COMBO_5 10
#define SCORE_COMBO_6 12
#define SCORE_COMBO_7 18
#define SCORE_COMBO_8 28
#define SCORE_COMBO_9 42
#define SCORE_COMBO_10 82
#define SCORE_COMBO_11 108
#define SCORE_COMBO_12 138
#define SCORE_COMBO_13 172
#define SCORE_COMBO_14 210

/**
 * \file controleur_five.h
 * \brief Contrôleur (pattern MVC) pour la gestion d'un five
 * \author Lucas Lolo
 * \author Marzouk Ouro-Gomma
 * \version 1.0
 * \date 2/5/2021
 *
 * Gestion d'un five via une approche MVC.  Ce module gère l'aspect contrôleur.
 * Le contrôleur fournit à l'utilisateur les contrôles sur le modèle (
 * En outre, le contrôleur traduit les actions de l'utilisateur en opération sur le modèle:
 * déclencher les traitements par des appels de fonctions/procédures sur le modèle.  Enfin, le
 * contrôleur sélectionne et met à jour la vue.
 */


/**
 * \brief Implémentation du contrôleur pour five.
 */
typedef struct controleur_t{
    VueFive *vf; /*!< vue du five */
    ModeleFive *mf; /*!< modèle du five */
    GtkWidget **bouton; /*!< le nombre de boutons du jeu */
    GtkWidget *Fenetre;  /*!< la fenetre courante */
    char *fichier_score; /*!< le fichier de l'utilisateur */
    int nombre; /*!< A savoir si l'utilisateur a clické correctement dans les bonnes cases  */
    int x_init; /*!< coordonnée horizontale du premier click */
    int y_init; /*!< coordonnée verticale du premier click */
    int x_dest; /*!< coordonnée horizontale du deuxieme click */
    int y_dest; /*!< coordonnée verticale du deuxieme click */
}ControleurFive;
/**
 * \brief Implémentation de la structure gerant les boutons
 * 
 */


/**
 * \fn ControleurFive *creer_controleur_five(struct vue_t *vf, ModeleFive *mf)
 * \brief Crée un contrôleur pour le five en fonction d'une vue et d'un modèle.
 *
 * \param vf la vue du five à prendre en compte.
 * \param mf le modèle du five à prendre en compte.
 *
 * \return ControleurFive *, un pointeur vers le contrôleur du five.
 *         NULL en cas d'erreur.
 */
ControleurFive *creer_controleur_five(VueFive *vf, ModeleFive *mf);

/**
 * \fn void ajoute_images( ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
void ajoute_images( ControleurFive *cf);

/**
 * \fn void click_init(GtkWidget *bouton, gpointer data)
 * \brief 
 *
 * \param bouton le widget en cause.
 * \param data widget en cause.
 * 
 */
void click_init(GtkWidget *click_init, gpointer data);

/**
 * \fn void position_dest_et_jeu_principale(GtkWidget *inutile, gpointer data)
 * \brief 
 *
 * \param inutile le widget en cause.
 * \param data widget en cause.
 */
void position_dest_et_jeu_principale(GtkWidget *click_dest, gpointer data);

/**
 * \fn int deplacement(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * 
 * \return 
 *      retourne une valeur :
 *          0 = deplacemt parfait
 *          1 = deplacement impossible 
 */
int deplacement(ControleurFive *cf);

/**
 * \fn GtkWidget *click_creer_menu(GtkWidget *Fenetre_Principale,ControleurFive *cf)
 * \brief 
 *
 * \param Fenetre_Principale le widget de la fenetre_pricipale
 * \param cf le controleur à modifier (ne peut être NULL).
 * 
 * \return 
 * retourne le Widget barre_menu
 */
GtkWidget *click_creer_menu(GtkWidget *Fenetre_Principale,ControleurFive *cf);

/**
 * \fn void nouvelle_fenetre_niveau(int nouveau_niveau, GtkWidget *Nouvelle_Fenetre_Niveau, ControleurFive *cf)
 * \brief 
 *
 * \param nouveau_niveau est le niveau selectionner par l'utilisateur (barre de menu)
 * \param Nouvelle_Fenetre_Niveau est une nouvelle fenetre correspondant à la taille du niveau
 * \param cf le controleur à modifier (ne peut être NULL).
 */
void nouvelle_fenetre_niveau(int nouveau_niveau, GtkWidget *Nouvelle_Fenetre_Niveau, ControleurFive *cf);

/**
 * \fn void aide(GtkWidget *Fenetre_Aide)
 * \brief 
 *
 * \param Fenetre_Aide est une fenetre qui donne des informations sur les createurs du jeu.
 */
void aide(GtkWidget *Fenetre_Aide);

/**
 * \fn void nouvelle_partie(GtkWidget *bouton, gpointer data)
 * \brief 
 *
 * \param bouton le widget en cause.
 * \param data widget en cause.
 */
void nouvelle_partie(GtkWidget *bouton, gpointer data);

/**
 * \fn void liste_score(GtkWidget *Fenetre_Score, gpointer data);
 * \brief 
 *
 * \param Fenetre_Score le widget en cause.
 * \param data widget en cause.
 */
void liste_score(GtkWidget *Fenetre_Score, gpointer data);

/**
 * \fn void facile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data)
 * \brief 
 *
 * \param Nouvelle_Fenetre_Niveau widget en cause.
 * \param data widget en cause.
 */
void facile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data);

/**
 * \fn void moyen(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data)
 * \brief 
 *
 * \param Nouvelle_Fenetre_Niveau widget en cause.
 * \param data widget en cause.
 */
void moyen(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data);

/**
 * \fn void difficile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data)
 * \brief 
 *
 * \param Nouvelle_Fenetre_Niveau widget en cause.
 * \param data widget en cause.
 */
void difficile(GtkWidget *Nouvelle_Fenetre_Niveau, gpointer data);

/**
 * \fn int verification_horizontale(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * 
 */
int verification_horizontale(ControleurFive *cf);

/**
 * \fn int verification_verticale(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
int verification_verticale(ControleurFive *cf);

/**
 * \fn int oblique_croissant1(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
int oblique_croissant1(ControleurFive *cf);

/**
 * \fn int oblique_croissant2(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
int oblique_croissant2(ControleurFive *cf);

/**
 * \fn int oblique_decroissant1(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
int oblique_decroissant1(ControleurFive *cf);

/**
 * \fn int oblique_decroissant2(ControleurFive *cf)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
int oblique_decroissant2(ControleurFive *cf);

/**
 * \fn void charge_modifie_combo_decroissant2(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
void charge_modifie_combo_decroissant2(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn void charge_modifie_combo_decroissant1(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * \param ComboAll est le combo gagnant
 * \param k est le deplacement de l'origine en bas a droite
 * \param i est l'origine du combo
 * \param j est la couleur des images
 */
void charge_modifie_combo_decroissant1(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn void charge_modifie_combo_croissant2(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * \param ComboAll est le combo gagnant
 * \param k est le deplacement de l'origine en haut a gauche
 * \param i est l'origine du combo
 * \param j est la couleur des images
 */
void charge_modifie_combo_croissant2(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn void charge_modifie_combo_croissant1(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * \param ComboAll est le combo gagnant
 * \param k est le deplacement de l'origine en haut a gauche
 * \param i est l'origine du combo
 * \param j est la couleur des images
 */
void charge_modifie_combo_croissant1(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn void charge_modifie_combo_verticale(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * \param ComboAll est le combo gagnant
 * \param k est le deplacement de l'origine en bas
 * \param i est l'origine du combo
 * \param j est la couleur des images
 */
void charge_modifie_combo_verticale(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn void charge_modifie_combo_horizontale(ControleurFive *cf,int ComboAll, int k, int i, int j)
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 * \param ComboAll est le combo gagnant
 * \param k est le deplacement de l'origine a droite
 * \param i est l'origine du combo
 * \param j est la couleur des images
 */
void charge_modifie_combo_horizontale(ControleurFive *cf,int ComboAll, int k, int i, int j);

/**
 * \fn char *affiche_classement_score(ControleurFive *cf);
 * \brief 
 *
 * \param cf le controleur à modifier (ne peut être NULL).
 */
char *affiche_classement_score(ControleurFive *cf);

#endif
