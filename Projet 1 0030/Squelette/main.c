/**
 * main.c
 *
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Ouro-Gomma Marzouk S204743
 * @date:
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"

int main(int argc, char *argv[])
{

    char *optstring = ":f:i:o:";
    char *format_file;
    char *input_file;
    char *output_file;

    int value;

    while ((value = getopt(argc, argv, optstring)) != EOF)
    {

        switch (value)
        {
        case 'f':
            format_file = optarg;
            break;
        case 'i':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        default:
            printf("Wrong command");
            break;
        } // fin switch
    }
    PNM *image;

    if (match_extension(input_file, output_file, format_file) == 0)
    {
        exit(1);
    }
    load_pnm(&image, input_file);

    write_pnm(image, output_file);

    destroy_pnm(image);

    return 0;
}
