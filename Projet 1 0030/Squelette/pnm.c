/**
 * pnm.c
 *
 * Ce fic contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Ouro-Gomma Marzouk S204743
 * @date:
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pnm.h"
#include <ctype.h>

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
    uint type; // 1 = PBM 2 = PGM, 3 = PPM (Consider using Enum)
    uint **matrice;
};

/*
This function saves the first line readed that doesn't contain the commenttag

*/
static void pass_comment(FILE *fic, char *buffer)
{
    assert(fic != NULL && buffer != NULL);

    do
        fgets(buffer, 100, fic);
    while (strncmp(buffer, COMMENTTAG, 1) == 0);
}
/*
    This function reads the magic number and return the corresponding type ( see comment in PNM_T).
    If The buffer doesn't contain a recognized tag, returns 0
*/

static int get_type(FILE *fic, char *buffer)
{
    assert(fic != NULL && buffer != NULL);

    // Read the line of the file which contains the magic number and put it in the buffer.
    pass_comment(fic, buffer);

    if (strncmp(buffer, PBMTAG, 2) == 0)
    {

        return PBM;
    }
    else if (strncmp(buffer, PGMTAG, 2) == 0)
    {

        return PGM;
    }
    else if (strncmp(buffer, PPMTAG, 2) == 0)
    {

        return PPM;
    }
    else
    {

        printf("Unrecognized Magic Number\n");
        return 0;
    }
}
/*
Constructor for PNM structure
*/
static PNM *build_PNM(int type, int lines, int columns, int max_val)
{
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
    image->max_value = max_val;

    image->matrice = malloc(sizeof(uint) * lines * 2);
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
        for (uint i = 0; i < columns * malloc_factor; i++)
        {
            free(image->matrice[i]);
        }
        free(image->matrice);
        free(image);
        printf("Error Mem Allocation");
        return NULL;
    }

    return image;
}

/*
Loads the data of the file to our structure
*/
static PNM *fill_matrix(int type, int lines, int columns, FILE *fic, PNM *image)
{
    assert(type > 0 && type < 4 && lines > 0 && columns > 0 && fic != NULL && image != NULL);
    printf("Starting MAatrix filling Process\n");
    uint fill_factor = 1;

    if (type == PPM)
        fill_factor = 3;

    int pixel;

    for (int i = 0; i < lines; i++)
    {
        for (uint j = 0; j < columns * fill_factor; j++)
        {
            // CAHNGE FOR RESUBMISSION
            if (fscanf(fic, "%d ", &pixel) != EOF)
            {
                image->matrice[i][j] = pixel;
            }
            else
            {
                return NULL;
            }
        }
    }
    printf("Matric Filled Succesfullyu\n");
    return image;
}
/*
Load our image using build_pnm and fill_matrix
*/
int load_pnm(PNM **image, char *filename)
{
    assert(filename != NULL && image != NULL);
    // printf("Filename : %s", filename);

    FILE *fic = fopen(filename, "r");
    if (fic == NULL)
    {
        printf("Unable to access the chosen input file, the name may be wrong, try again .\n");
        return -2;
    }

    char buffer[BUFFERSIZE];

    int type = get_type(fic, buffer);

    if (type == 0)
    {
        printf("Unrecognized Magic Number\n");
        return -3;
    }
    int lines;
    int columns;
    int max_val;

    pass_comment(fic, buffer);
    sscanf(buffer, "%d %d", &columns, &lines);
    pass_comment(fic, buffer);

    if (type == PBM)
    {
        max_val = 1;
    }
    else if (type == PPM || type == PGM)
    {
        sscanf(buffer, "%d", &max_val);
    }
    else
    {
        printf("Unknown type\n");
        return -3;
    }

    *image = build_PNM(type, lines, columns, max_val);
    if (*image == NULL)
    {
        printf("Unable to allocate memory for the PNM image\n");
        return -1;
    }
    //CHANGES FOR RESUBMISSION
    if (fill_matrix(type, lines, columns, fic, *image) == NULL)
    {
        printf("the matrix is corrupted.\n");
        fclose(fic);
        return -3;
    }

    fclose(fic);

    return 0;
}
/*
Writes the image stored in the memory in a new file
*/
int write_pnm(PNM *image, char *filename)
{

    assert(filename != NULL && image != NULL);
    if (check_filename(filename) != 1)
    {
        printf("Unothorized character %c found in output file name", check_filename(filename));
        return -1;
    }
    printf("Beginning of the writing operation\n");
    FILE *fic = fopen(filename, "w");
    if (fic == NULL)
    {
        printf("error, couldn't open new file");
        return -2;
    }
    uint write_factor = 1;
    if (image->type == PPM)
        write_factor = 3;

    switch (image->type)
    {
    case PBM:

        fprintf(fic, "P1\n%d %d\n", image->columns, image->lines);

        break;
    case PGM:

        fprintf(fic, "P2\n%d %d\n%d\n", image->columns, image->lines, image->max_value);

        break;
    case PPM:

        fprintf(fic, "P3\n%d %d\n%d\n", image->columns, image->lines, image->max_value);

        break;

    default:
        fclose(fic);
        return -3;
    }
    for (uint i = 0; i < image->lines; i++)
    {
        for (uint j = 0; j < image->columns * write_factor; j++)
        {
            fprintf(fic, "%d ", image->matrice[i][j]);
        }
        fprintf(fic, "\n");
    }
    fclose(fic);
    printf("image written succesfully\n");
    return 0;
}

/*
takes a pointer to a pnm image as input and
Frees the memory allocated for the file
*/
void destroy_pnm(PNM *image)
{
    assert(image != NULL);

    for (uint i = 0; i < image->lines; i++)
    {
        free(image->matrice[i]);
    }
    free(image->matrice);
    free(image);
}

/*

returns 0 if extension is not supported and 1 if it is
*/
int match_extension(char *input_file, char *output_file, char *format_file)
{
    char input_extension[5] = "";
    char output_extension[5] = "";
    if (check_filename(output_file) != 1)
    {
        printf("output file contains the unallowed character '%c' ", check_filename(output_file));
        return 0;
    }

    for (int i = 3; i > 0; i--)
    {
        strncat(input_extension, &input_file[strlen(input_file) - i], 1);
        strncat(output_extension, &output_file[strlen(output_file) - i], 1);
    }
    // CHANGE FOR RESUBMISSION
    if (strncmp(format_file, "pgm", 3) != 0 && strncmp(format_file, "pbm", 3) != 0 && strncmp(format_file, "ppm", 3) != 0 &&
        strncmp(format_file, "PGM", 3) != 0 && strncmp(format_file, "PBM", 3) != 0 && strncmp(format_file, "PPM", 3) != 0)
    {
        printf("Unallowed format chosen, the only allowed formats are pgm, ppm and pbm, you chosed : %s\n\n", format_file);
        return 0;
    }
    // CHANGES FOR RESUBMISSION
    for (int i = 0; i < 3; i++)
    {
        if ((tolower(format_file[i]) != input_extension[i]) && (tolower(format_file[i]) != output_extension[i]))
        {
            printf("Different files extensions don't match : Chosen file extension : %s, Input file extension :%s, Output file extension :%s\n",
                   format_file, input_extension, output_extension);
            return 0;
        }
       
    }
    printf("Format file :%s Input extension : %s, Output extension : %s\n", format_file, input_extension, output_extension);
    printf("Format : %s, Input : %s, Output : %s\n", format_file, input_file, output_file);
    return 1;
}



/*
returns 0 if extension is not supported and 1 if it is
*/
int check_extension(char *filename, char *match)
{

    char extension[5] = "";
    for (int i = 3; i > 0; i--)
    {
        strncat(extension, &filename[strlen(filename) - i], 1);
    }

    if (strncmp(extension, match, 3) != 0)
    {

        return 0;
    }
    return 1;
}
/*
Verify if the filename doesn't contain any  unothorized character returns 0 if it doesn't else returns the unothorized character
*/
char check_filename(char *filename)
{

    for (long unsigned int i = 0; i < strlen(filename); i++)
    {
        if (filename[i] == '/' || filename[i] == ':' || filename[i] == '*' || filename[i] == '?' || filename[i] == '"' || filename[i] == '<' || filename[i] == '>' || filename[i] == '|' || filename[i] == '\\')
        {
            return filename[i];
        }
    }

    return 1;
}