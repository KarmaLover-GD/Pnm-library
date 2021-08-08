#ifndef __MODELE_FIVE__
#define __MODELE_FIVE__

/**
 * \file modele_five.h
 * \brief Modèle (pattern MVC) pour la gestion d'un Five or More
 * \author Lucas Lolo
 * \author Marzouk Ouro-Gomma
 * \version 1.0
 * \date 2/5/2021
 *
 * Gestion du jeu five via une approche MVC.  Ce module gère l'aspect modèle.
 * Le modèle gère la valeur des grilles .
 *
 * Par défaut, la grille est initialisé à 0.
 */


/**
 * \brief Implémentation du modèle pour le five.
 */
typedef struct modele_t{
   int niveau;/*!< le niveau courant de l'utilisateur */
   int largeur;/*!< la largeur de la grille */
   int hauteur;/*!< la hauteur de la grille*/
   int typeSymboles;/*!< le nombre de symboles */
   int symbolesTour;/*!< le nombre de symboles a ajouter par tour */
   int cellules;/*!< le nombre de cellules de la grille */
   int grille[20][15]; /*!< la taille de la grille en 2 dimensions contenant les valeurs des couleurs*/
   int aleatoire[20][15]; /*!< la taille de la grille en 2 dimensions contennant un compteur pour l'aléatoire */
   int combo;/*!< un nombre maximale de combinaison */
   int avancer_tableau_horizontale; /*!< un nombre maximale qui permet d'avancer d'un pas de 1 à droite  */
   int avancer_tableau_verticale;/*!<  un nombre maximale qui permet d'avancer d'un pas de 1 en bas*/
   int avancer_tableau_oblique;/*!<  un nombre maximale qui permet d'avancer d'un pas de 1 en haut à droite*/
   int oblique_decroissant;/*!<  un nombre maximale qui permet de ne pas chercher un combo quand il y a moins de 5 cases*/
   int score; /*!<  Contient le score total de l'utilisateur*/
   int ligneActuelle[10]; /*!<  Contient les 10 meilleures scores*/
   int nouvelle_partie; /*!<  Permet de savoir combien de partie ont été jouée*/
}ModeleFive;

/**
 * \fn ModeleFive *creer_modele_five(int niveau)
 * \brief Crée un modèle five de base.
 *
 * \return ModeleFive *, un pointeur vers un modèle de five.
 *         NULL en cas d'erreur.
 */
ModeleFive *creer_modele_five(int niveau);

/**
 * \fn void change_valeur(ModeleFive *mf, int i, int j, int val)
 * \brief 
 *
 * \param mf le modèle à modifier (ne peut être NULL).
 * \param i est l'indice de la grille.
 * \param val est la valeur de la grille.
 */
void change_valeur(ModeleFive *mf, int i, int j, int val);

/**
 * \fn void position_case_blanche(ModeleFive *mf, int i, int j, int compteur)
 * \brief Cetter fonction stocke les positions des cases blanches 
 * avec un compteur.
 *
 * \param mf le modèle à modifier (ne peut être NULL).
 * \param i est la hauteur de la grille.
 * \param j est la largeur de la grille.
 * \param compteur est un compteur qui contient les positions des cases
 */
void position_case_blanche(ModeleFive *mf, int i, int j, int compteur);

/**
 * \fn int generation_image_aleatoire(ModeleFive *mf);
 *
 * \param mf le modèle à modifier (ne peut être NULL).
 *
 * \return: 
 *        Retourne la position d'une des cases blanches selectionner au hazard.
 *     
 */
int generation_image_aleatoire(ModeleFive *mf);

/**
 * \fn int case_blanche_compteur(ModeleFive *mf)
 *
 * \param mf le modèle à modifier (ne peut être NULL).
 *
 * \return: 
 *        Retourne le nombre de case blanche.
 *     
 */
int case_blanche_compteur(ModeleFive *mf);

/**
 * \fn void classement(ModeleFive *mf)
 * \brief 
 *
 * \param mf le modèle à modifier (ne peut être NULL).
 */
void classement(ModeleFive *mf);

#endif