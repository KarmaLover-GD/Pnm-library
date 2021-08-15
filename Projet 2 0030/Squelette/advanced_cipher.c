/**
 * \file main-advanced_cipher.c
 *
 *
 * \brief INFO0030 Projet 2 - Chiffrement avancé d'images
 * \author Ouro-Gomma Marzouk s204743  
 * \version 0.1
 * \date 15/08/2021
 *
 * Ce fichier contient le programmme principal (main)
 * pour le chiffrement avancé d'images.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "lfsr.h"
#include "pnm.h"
#include "basic_cipher.h"
#include "advanced_cipher.h"



   char *password_to_seed(char* password){
       assert(password != NULL);
       char * base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ " ;
       char *seed;
       char *first_caracter;
       int check = 0;
       int position;
       int *seed_array = malloc(sizeof(int)* strlen(password)*6);


       for(int i = 0; i<strlen(password); i++){
           //check if the caracter is from base 64
           for(int j = 0; j<strlen(base64); j++){
               if(password[i] ==  base64[j]){
                   check = 1;
               }
              
           }
           //managing the case where a caracter within the apssword isn't from base 64
            if(check != 1){
                   printf("Unallowed caracter within the password, do you want to change ?");
                   int choice;
                   scanf("\nPress 1 to chose a new password and anything else to terminate the program\n%d", &choice);
                   if(choice == 1){
                       scanf("\n what is your new apssord ?\n%s", password);
                       password_to_seed(password);
                   }else{
                       exit(1);
                   }
               }

            //translating the caracter to binary with 6 digits and adding it to our seed
            for(int k = 0; k<6; k++){
                position = i*6 + 5-k; 
                if(atoi(password[i]) %2 ==0){
                    seed_array[position] = 0;
                }else{
                    seed_array[position] = 1;
                }
                k = k/2;
            }
       }

       //transforming our array to a string and returning it
    char digit[5];
    char *strseed= malloc(sizeof(char)*strlen(password)*6);


    for(int i =0; i<strlen(password)*6; i++){
        
        sprintf(digit, "%d", seed_array[i]);
        if(i == 0){
            strcpy(strseed, digit);
        }else{
            strncat(strseed, &digit, 1);
        }
        
        return strseed;
    }

   }

