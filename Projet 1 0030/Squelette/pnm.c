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

#define BUFFERSIZE 1024
#define PBM 1
#define PGM 2
#define PPM 3
#define PBMTAG "P1"
#define PGMTAG "P2"
#define PPMTAG "P3"
#define COMMENTTAG "#"

typedef unsigned int uint;
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

    if (strncmp(buffer, "P1", 2) == 0)
    {
        printf("%s", buffer);
        fclose(fic);
        return PBM;
    }
    else if (strncmp(buffer, "P2", 2) == 0)
    {
        printf("%s", buffer);
        fclose(fic);
        return PGM;
    }
    else if (strncmp(buffer, "P3", 2) == 0)
    {
        printf("%s", buffer);
        fclose(fic);
        return PPM;
    }
    else
    {
        printf("%s", buffer);
        fclose(fic);
        return 0;
    }
}
//-----------------------------------------------
//-----------------------------------------------
static PNM *build_PNM(int type, int lines, int columns, int max_val)
{
    printf("Starting Memory allocation process \n");
    assert(type > 0 && type < 4 && lines > 0 && columns > 0 && max_val > 0);
    PNM *image = malloc(sizeof(PNM));

    if (image == NULL)
    {
        printf("Error Mem Allocation");
        return NULL;
    }

    uint malloc_factor = 1;

    if (type == PPM)
        malloc_factor = 3;

    image->lines = lines;
    image->type = type;
    image->columns = columns;

    image->matrice = malloc(sizeof(uint) * lines);
    if (image->matrice == NULL)
    {
        free(image->matrice);
        free(image);
        printf("Mem Allocation error");
        return NULL;
    }

    for (int i = 0; i < lines; i++)
    {
        image->matrice[i] = malloc(sizeof(uint) * malloc_factor * columns);
    }

    if (image->matrice == NULL)
    {
        for (int i = 0; i < columns * malloc_factor; i++)
        {
            free(image->matrice[i]);
        }
        free(image->matrice);
        free(image);
        printf("Error Mem Allocation");
        return NULL;
    }
    printf("Memory allocated Succesfully\n");
    return image;
}

//-----------------------------------------------
//-----------------------------------------------
static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image)
{
    assert(type > 3 && type < 4 && lines > 0 && columns > 0 && fic != NULL && image != NULL);
    printf("Starting MAatrix filling Process\n");
    uint fill_factor = 1;

    if (type == PPM)
        fill_factor = 3;

    int pixel;

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns * fill_factor; j++)
        {
            fscanf(fic, "%d ", &pixel);

            image->matrice[i][j] = pixel;
        }
    }
    printf("Matric Filled Succesfullyu\n");
    return image;
}
//-----------------------------------------------
//-----------------------------------------------
int load_pnm(PNM **image, char *filename)
{
    assert(filename != NULL && image != NULL);
    // printf("Filename : %s", filename);
    printf("Starting the loading process\n");
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
    if (type == PBM)
    {

        sscanf(buffer, "%d %d", &columns, &lines);

        *image = build_PNM(type, lines, columns, 1);
        fill_matrix(type, lines, columns, fic, *image);
    }
    else if (type == PGM)
    {

        sscanf(buffer, "%d %d", &columns, &lines);

        pass_comment(fic, buffer);
        sscanf(buffer, "%d", &max_val);

        *image = build_PNM(type, lines, columns, max_val);
        fill_matrix(type, lines, columns, fic, *image);
    }
    else if (type == PPM)
    {

        sscanf(buffer, "%d %d", &columns, &lines);

        pass_comment(fic, buffer);
        sscanf(buffer, "%d", &max_val);

        *image = build_PNM(type, lines, columns, max_val);
        fill_matrix(type, lines, columns, fic, *image);
    }

    fclose(fic);
    printf("Image loaded successfully \n");
    return 0;
}
//-----------------------------------------------
//-----------------------------------------------
int write_pnm(PNM *image, char *filename)
{
    assert(filename != NULL && image != NULL);
    printf("Beginning of the writing operation\n");
    FILE *fic = fopen(filename, "w");
    if (fic == NULL)
    {
        printf("error, couldn't open new file");
        return -1;
    }
    uint write_factor = 1;
    if (image->type == PPM)
        write_factor = 3;

    switch (image->type)
    {
    case PBM:;

        fprintf(fic, "P1\n%d %d\n", image->columns, image->lines);

        break;
    case PGM:;

        fprintf(fic, "P2\n%d %d\n%d\n", image->columns, image->lines, image->max_value);

        break;
    case PPM:;

        fprintf(fic, "P3\n%d %d\n%d\n", image->columns, image->lines, image->max_value);

        break;

    default:
        fclose(fic);
        return -3;
    }
    for (int i = 0; i < image->lines; i++)
    {
        for (int j = 0; j < image->columns * write_factor; j++)
        {
            fprintf(fic, "%d ", image->matrice[i][j]);
        }
        fprintf(fic, "\n");
    }
    fclose(fic);
    printf("image written succesfully\n");
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

/*
returns 0 if extension is not supported and 1 if it is
*/
int check_extension(char *input_file, char *output_file, char *format_file)
{
    char input_extension[5] = "";
    char output_extension[5] = "";
    if (check_filename(output_file) != NULL)
    {
        printf("output file contains the unallowed character '%c' ", check_filename(output_file));
        return 0;
    }

    for (int i = 3; i > 0; i--)
    {
        strncat(input_extension, &input_file[strlen(input_file) - i], 1);
        strncat(output_extension, &output_file[strlen(output_file) - i], 1);
    }

    if (strncmp(format_file, "pgm", 3) != 0 && strncmp(format_file, "pbm", 3) != 0 && strncmp(format_file, "ppm", 3) != 0)
    {
        printf("Unallowed format chosen, the only allowed formats are pgm, ppm and pbm, you chosed : %s\n\n", format_file);
        return 0;
    }

    if ((strncmp(format_file, input_extension, 3) == 0) && (strncmp(format_file, output_extension, 3) == 0))
    {
        printf("Format file :%s Input extension : %s, Output extension : %s\n", format_file, input_extension, output_extension);
        printf("Format : %s, Input : %s, Output : %s\n", format_file, input_file, output_file);
        return 1;
    }
    else
    {
        printf("Different files extensions don't match : Chosen file extension : %s, Input file extension :%s, Output file extension :%s\n",
               format_file, input_extension, output_extension);
        return 0;
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