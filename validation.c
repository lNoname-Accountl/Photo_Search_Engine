/*
 * validation.c
 *
 * This file will check all of validation that user typing from keyborad
 * and it will return value to addData.c and searchData.c
 * and if it invalid program will loop to get input from user again.
 *
 * created by GET_A team for CPE111 project
 * Kodchaphon Treesak 62070503401
 * Kulchaya Songkwan 62070503405
 * Chotiya Pertpring 62070503413
 * Prakasit Issanapong 62070503431
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<dirent.h>

#include"structure.h"

/* this function is rules to guide user to typing correctly information */
void rules()
{
    printf("\n\t [ Rules of Titlename ] \n");
    printf("\t\t - CAN be ONLY alphabet and number \n");
    printf("\t\t - CANNOT has any blank space \n");
    printf("\n\t [ Rules of Hashtag ] \n");
    printf("\t\t - CAN use only dash(-) to get next hastag \n");
    printf("\n\t [ Rules of Filename ] \n");
    printf("\t\t - CAN be ONLY alphabet and number \n");
    printf("\t\t - CAN be ONLY .jpg or .png\n");
    printf("\t\t - CANNOT has any blank space \n");
}

/* this function will check all filename of picture in data folder
 * if input has found on data folder this function will print all data.
 *      name - input of filename in .jpg or .png
 *      valid = 0 , invalid = 1
 */
int checkNameSystem(char *name)
    {
    DIR *folder;                /* directory data folder */
    struct dirent *entry;
    int files = 0;              /* count all picture */
    int retu = 1;               /* return value */
    int j = 0;                  /* variable to run the loop */
    int i = 0;                  /* variable to run the loop */
    PHOTODATA2_T * data = NULL;

    /* open folder name picture */
    folder = opendir("picture");
    if(folder == NULL)
        {
        perror("Unable to read directory.\n");
        }

    /* count all files in folder */
    while( (entry=readdir(folder)) )
        {
        files++;
        }
    /* close folder */
    closedir(folder);
    
    /* calloc data */
    data = calloc(files,sizeof(PHOTODATA2_T));
    /* open folder name picture */
    folder = opendir("picture");
    /* coppy input to data */
    while( (entry=readdir(folder)) )
        {
        strcpy(data[i].namefile,entry->d_name);
        i++;
        }
    /* close folder */
    closedir(folder);
    
    /* loop to check is input already add on data */
    for (j = 0; j < files; j++)
        {
        if(strcmp(data[j].namefile,name) == 0)
            {
            printf("\t\tYou already have this file.\n");
            retu = 0;
            break;
            }
        }
    //printf("\t1\n");
    return retu;
    }
/* this function will compare is input of title name same as titile name in data
 * if input has same as data this function will invalid.
 *      string1 - input of title name from user
 *      data - structure of data
 *      count - count of all data
 *      valid = 0 , invalid = 1
*/
int checkCompareTitleInFile(char * string1, PHOTODATA_T * data, int count)
    {
    int i = 0;              /* variable run the loop */
    int y = count+1;        /* variable plus count value to run the loop */
    
    /* loop to compare is input has the same name in data */
    while(data != NULL)
        {
        if(strcasecmp(string1,data->title) == 0)
            {
            return 1;
            }
        data = data->pNext;
        }
    return 0;
    }

/* this function will check the special string of all hastag
 * if input has found any speacial string this function will invalid.
 *      string - input of hastag from user
 *      numberTag - count of hastag from user
 *      valid = 0 , invalid = 1 , invalid(not match tag) = 2
 */
int checkSpecialStringIntag(char * string, int numberTag)
    {
    int check = 0;          /* count if not digit or alphabet */
    int i = 0;              /* variable to run the loop */
    int checkDash = 0;      /* count dash */

    /* loop to check type of string */
    for(i = 0;i < strlen(string);i++)
        {
        /* check - */
        if(string[i] == 45)
            {
            checkDash++;
            }
        /* not alpha */
        if(isalnum(string[i]) == 0)
            {
            check++;
            }
        }
    /* check is input match hastag count */
    if(numberTag != checkDash+1)
        {
        return 2;
        }
    /* check any special string except dash */
    else if(check == checkDash)
        {
        return 0;
        }
    else
        {
        return 1;
        }
    }

/* this function will check the special string of all title name
* if input has found any speacial string this function will invalid.
*      string - input of title name from user
*      valid = 0 , invalid = 1
*/
int checkSpecialString(char * string)
    {
    int check = 0;          /* return validation value */
    int i = 0;              /* variable to run the loop */
    
    /* loop to check any special string or space in title name*/
    for(i = 0;i < strlen(string);i++)
        {
        if((isalnum(string[i]) == 0) || (isspace(string[i]) != 0))
            {
            check = 1;
            }
        }
    return check;
    }

/* this function will check all filename from user.
 * if input has any special string has blankspace and no has .jpg or .png
 * this function will invalid.
 *      filename - input of filename in .jpg or .png
 *      valid = 0 , invalid = 1
 */
int checkFilename(char * filename)
    {
    int len = 0;                /* value of string lenght */
    int i = 0;                  /* variable to run the loop */
    //int checkDot = 0;           /* count dot */
    //int checkString = 0;        /* count if not digit or alphabet */
    
    len = strlen(filename);
    /* call fuction to get the same input if it has valid value */
    checkNameSystem(filename);
    if(strcasecmp(&filename[len-4],".jpg") == 0)
        {
        return 0;
        }
    else if(strcasecmp(&filename[len-4],".png") == 0)
        {
        return 0;
        }
    else
        {
        return 1;
        }
    }
/* this function will check is new input has the same filename in data.
 * if input has same as data this function will invalid.
 *      name - new input of filename in .jpg or .png
 *      tagplus - count of information in data.
 *      pData - pointer of data
 *      valid = 0 , invalid = 1
 */
int checkAllFileName(char *name,int tagplus,PHOTODATA_T * pData)
    {
    int check1 = 0;
    int check2 = 0;
    int i = 0;
    
    /* loop to check is new input already used */
    while(pData != NULL)
        {
        if(strcmp(pData->filename,name) == 0 )
            {
            printf("\t\tThis name is already used. You must changed it\n");
            check2 = 1;
            break;
            }
        pData = pData->pNext;
        }
    if(check2 == 1)
        {
        return 1;
        }
        
    /* call function to check filename */
    check1 = checkFilename(name);
    if(check1 == 0)
        {
        return 0;
        }
    else
        {
        printf("\t\tInvalide File name\n");
        return 1;
        }
    }
