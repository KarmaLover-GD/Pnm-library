/**
 * pnm.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author: Nom Prenom Matricule
 * @date:
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char *filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char *filename);

/** CHANGES FOR RESUBMISSION
 * destroy_pnm
 *
 * Frees an image
 *
 * @param image un pointeur sur PNM.
 *
 * @pre: image != NULL
 * @post: The image was freed
 *

 *
 */
void destroy_pnm(PNM *image);

/**
 * match_extension
 *
 * Check whether the given format is supported and whether the files extension and the formats corresponds
 *
 * @param input_file the input file (as the name suggest)
 * @param output_file the output file (as the name suggests)
 * @param format_file the format of the input and output files
 * 
 *
 * @pre: input output and format_file  != NULL
 * @post: returns an integer according to the results of operations and display it.
 *
 * @return:
 *        1 everything is okay
 *        0 format is unsupported or extensions don't match
 *
 */
int match_extension(char *input_file, char *output_file, char *format_file);

/*

Checks if there is anny forbidden characters in the given file's name
*/
char check_filename(char *filename);
/*

Checks if the file extension correspond to the expected one
*/
int check_extension(char *filename, char *match);
#endif // __PNM__
