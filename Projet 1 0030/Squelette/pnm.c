/**
 * pnm.c
 *
 * Ce fic contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Nom Prenom Matricule
 * @date:
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pnm.h"

#define uint unsigned int
#define BUFFERSIZE 1024

/**
 * Définition du type opaque PNM
 *
 */

struct PNM_t
{
    uint lines;
    uint columns;
    uint max_value;
    uint type;
    uint **matrice;
};

//--------------------------------------------------
static void pass_comment(FILE *fic, char *buffer)
{
    assert(fic != NULL && buffer != NULL);

    do
        fgets(buffer, 100, fic);
    while (strncmp(buffer, "#", 1) == 0);
}
//-----------------------------------------------
//-----------------------------------------------
static int get_type(FILE *fic, char *buffer)
{
    assert(fic != NULL && buffer != NULL);

    // Read the line of the file which contains the magic number and put it in the buffer.
    pass_comment(fic, buffer);
    // returns 1 for pbm
    if (strncmp(buffer, "P1", 2) == 0)
    {
        printf("%s", buffer);
        return 1;
        // returns 2 for pgm
    }
    else if (strncmp(buffer, "P2", 2) == 0)
    {
        printf("%s", buffer);
        return 2;
        // returns 3 for ppm
    }
    else if (strncmp(buffer, "P3", 2) == 0)
    {
        printf("%s", buffer);
        return 3;
    }
    else
    {
        printf("%s", buffer);
        return 0;
    }

    fclose(fic);
}
//-----------------------------------------------
//-----------------------------------------------
static PNM *build_PNM(int type, int lines, int columns, int max_val)
{
    assert(type > 0 && type < 4 && lines > 0 && columns > 0 && max_val >= 0);
    PNM *image = malloc(sizeof(PNM));

    if (image == NULL)
    {
        printf("Error Mem Allocation");
        return NULL;
    }

    uint a = 1;

    if (type == 3)
        a = 3;

    image->lines = lines;
    image->type = type;
    image->columns = columns;

    image->matrice = malloc(sizeof(uint) * lines*2);
    

    for(int i =0; i<lines; i++){
        image->matrice[i] = malloc(sizeof(uint)* a*columns);
    }

    if(image->matrice == NULL){
        for(int i =0; i<columns*a; i++){
            free(image->matrice[i]);
        }
        free(image->matrice);
        free(image);
        printf("Error Mem Allocation");
        return NULL;
    }

    
    return image;
}

//-----------------------------------------------
//-----------------------------------------------
static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image)
{

    int pixel;
    int red, green, blue;

    switch (type)
    {
    // read the matrix from the file and fill it in our structure
    case 1:

        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                fscanf(fic, "%d ", &pixel);

                image->matrice[i][j] = pixel;
            }
        }
        break;
    case 2:
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                fscanf(fic, "%d ", &pixel);

                image->matrice[i][j] = pixel;
            }
        }
        break;
    case 3:
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns * 3; j += 3)
            {

                fscanf(fic, "%d %d %d ", &red, &green, &blue);
                image->matrice[i][j] = red;
                image->matrice[i][j + 1] = green;
                image->matrice[i][j + 2] = blue;
            }
        }

    default:
        break;
    }
    return image;
}
//-----------------------------------------------
//-----------------------------------------------
int load_pnm(PNM **image, char *filename)
{
    assert(filename != NULL && image != NULL);
    // printf("Filename : %s", filename);
    int choice;
    FILE *fic = fopen(filename, "r");
    if (fic == NULL)
    {
        printf("Unable to access the chosen input file, the name may be wrong, try again .\n");
        exit(1);
    }

    char buffer[BUFFERSIZE];

    int type = get_type(fic, buffer);

    int lines;
    int columns;
    int max_val;

    pass_comment(fic, buffer);
    if (type == 1)
    {

        sscanf(buffer, "%d %d", &lines, &columns);

        if (lines > 0 && columns > 0)
        {
            *image = build_PNM(type, lines, columns, 0);
            fill_matrix(type, lines, columns, fic, *image);
        }
    }
    else if (type == 2)
    {

        sscanf(buffer, "%d %d", &lines, &columns);

        pass_comment(fic, buffer);
        sscanf(buffer, "%d", &max_val);

        if (lines > 0 && columns > 0)
        {
            *image = build_PNM(type, lines, columns, max_val);
            fill_matrix(type, lines, columns, fic, *image);
        }
    }
    else if (type == 3)
    {
        printf("traitement du fichier ppm\n");
        sscanf(buffer, "%d %d", &lines, &columns);
        printf("lines :%d columns :%d\n", lines, columns);
        pass_comment(fic, buffer);
        sscanf(buffer, "%d", &max_val);
        printf("valeur max : %d", max_val);

        if (lines > 0 && columns > 0)
        {
            *image = build_PNM(type, lines, columns, max_val);
            fill_matrix(type, lines, columns, fic, *image);
        }
    }

    fclose(fic);

    return 0;
}
//-----------------------------------------------
//-----------------------------------------------
int write_pnm(PNM *image, char *filename)
{
    assert(filename != NULL && image != NULL);

    FILE *fic = fopen(filename, "w");
    if (fic == NULL)
    {
        printf("error, couldn't open new file");
        return -1;
    }

    switch (image->type)
    {
    case 1:;

        fprintf(fic, "P1\n%d %d\n", image->lines, image->columns);
        for (int i = 0; i < image->lines; i++)
        {
            for (int j = 0; j < image->columns; j++)
            {
                fprintf(fic, "%d ", image->matrice[i][j]);
            }
            fprintf(fic, "\n");
        }
        fclose(fic);
        break;
    case 2:;

        fprintf(fic, "P2\n%d %d\n%d\n", image->lines, image->columns, image->max_value);
        for (int i = 0; i < image->lines; i++)
        {
            for (int j = 0; j < image->columns; j++)
            {
                fprintf(fic, "%d ", image->matrice[i][j]);
            }
            fprintf(fic, "\n");
        }
        fclose(fic);
        break;
    case 3:;

        fprintf(fic, "P3\n %d %d\n%d\n", image->lines, image->columns, image->max_value);
        for (int i = 0; i < image->lines; i++)
        {
            for (int j = 0; j < image->columns * 3; j += 3)
            {
                fprintf(fic, "%d %d %d ", image->matrice[i][j], image->matrice[i][j + 1], image->matrice[i][j + 2]);
            }
            fprintf(fic, "\n");
        }
        fclose(fic);
        break;

    default:
        fclose(fic);
        return -3;
        
    }

    return 0;
}

//-----------------------------------------------
//-----------------------------------------------
void destroy_pnm(PNM *image)
{
    assert(image != NULL);


    for (int i = 0; i < image->lines; i++)
        {
            free(image->matrice[i]);
        }
        free(image->matrice);
        free(image);

   
}

//-----------------------------------------------
//-----------------------------------------------
void check_extension(char *input_file, char *output_file, char *format_file, PNM *image)
{
    char input_extension[5] = "";
    char output_extension[5] = "";
    if (check_filename(output_file) != NULL)
    {
        printf("output file contains the unallowed character '%c' ", check_filename(output_file));
        exit(1);
    }

    for (int i = 3; i > 0; i--)
    {
        strncat(input_extension, &input_file[strlen(input_file) - i], 1);
        strncat(output_extension, &output_file[strlen(output_file) - i], 1);
    }

    if (strncmp(format_file, "pgm", 3) != 0 && strncmp(format_file, "pbm", 3) != 0 && strncmp(format_file, "ppm", 3) != 0)
    {
        printf("Unallowed format chosen, the only allowed formats are pgm, ppm and pbm, you chosed : %s\n\n", format_file);
        exit(1);
    }

    if ((strncmp(format_file, input_extension, 3) == 0) && (strncmp(format_file, output_extension, 3) == 0))
    {
        printf("Format file :%s Input extension : %s, Output extension : %s\n", format_file, input_extension, output_extension);
        printf("Format : %s, Input : %s, Output : %s\n", format_file, input_file, output_file);
        load_pnm(&image, input_file);
        write_pnm(image, output_file);
        destroy_pnm(image);
    }
    else
    {
        printf("Different files extensions don't match : Chosen file extension : %s, Input file extension :%s, Output file extension :%s\n",
               format_file, input_extension, output_extension);
        exit(1);
    }
}

char check_filename(char *filename)
{
    for (int i = 0; i < strlen(filename); i++)
    {

        for (long unsigned int i = 0; i < strlen(filename); i++)
        {
            if (filename[i] == '/' || filename[i] == ':' || filename[i] == '*' || filename[i] == '?' || filename[i] == '"' || filename[i] == '<' || filename[i] == '>' || filename[i] == '|' || filename[i] == '\\')
            {
                return filename[i];
            }
        }
        return NULL;
    }
}