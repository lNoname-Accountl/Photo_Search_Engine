/*
 * interface.c
 *
 * this file is user interface to display main menu to get option from user.
 *
 * created by GET_A team for CPE111 project
 * Kodchaphon Treesak 62070503401
 * Kulchaya Songkwan 62070503405
 * Chotiya Pertpring 62070503413
 * Prakasit Issanapong 62070503431
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<dirent.h>

#include"addData.h"
#include"searchData.h"

/* this function is user interface to display main menu to get option from user */
int main()
    {
    char input[128];            /* input text from keyboard */
    int choice = 0;             /* keep the choice that user choose */
   
    /* loop to display main menu to get option from user */
    while (1)
        {
        choice = 0;
        printf("\n\t =  =  =  =  =  =  =  =  =  =  =  =  =\n\n");
            printf("\t    Welcome to Photos search engine! \n\n");
            printf("\t =  =  =  =  =  =  =  =  =  =  =  =  =\n");
            
            printf("\n\t What would you want to do? \n");
            printf("\t [1] Add photo \n");
            printf("\t [2] Search photo\n");
            printf("\t [3] Exit \n");
            printf("\n\t Enter number : ");
            fgets(input,sizeof(input),stdin);
            sscanf(input,"%d",&choice);
        
        /* choice of option */
        if (choice == 1)
            {
            AddOption();
            }
        else if (choice == 2)
            {
            searchOption();
            }
        else if (choice == 3)
            {
            exit(0);
            }
        else
            {
            printf("\t Invalid choice, Try again!! \n");
            }
        }
    }
