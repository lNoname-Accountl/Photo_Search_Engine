/*
 * addData.c
 *
 * This file is function adding data that will call fuction from validation.c
 * to display all data , edit(rename) data dataand writing data into the text file.
 *
 * created by GET_A team for CPE111 project
 * Kodchaphon Treesak 62070503401
 * Kulchaya Songkwan 62070503405
 * Chotiya Pertpring 62070503413
 * Prakasit Issanapong 62070503431
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<dirent.h>

#include"structure.h"
#include"validation.h"
#include"abstractHashTable.h"

/* this function is rename from filename that already check in folder
 * and adding into the text file.
 *      name1 - filename already check in folder
 *      name2 - new filename want to change
 */
int renameFunction(char *name1,char *name2)
{
  DIR * folder = NULL;          /* directory folder */
  char data1[100];              /* coppy format string of old filename */
  char data2[100];              /* coppy format string of new filename */
  int value;                    /* to get sucess rename */

  /* open folder of picture data */
  folder = opendir("picture");
 
 /* coppy format string into another variable */
 sprintf(data1,"picture/%s",name1);
 sprintf(data2,"picture/%s",name2);
  /* File name is changed here */
  value = rename(data1,data2);

  /* Print the result */
  if(!value)
    {
    printf("%s", "\t\tFile name changed successfully.\n");
    return 1;
    }
  else
    {
    perror("Error to rename\n");
    return 0;
    }
  /* close folder */
  closedir(folder);
  
}

/* this function is writing all data into the text file
 *      titleName - titlename of adding photo
 *      fileName - filename of adding photo
 *      numberOfTag - count tag of adding photo
 *      inputTag - array of hastag of adding photo
 */
void writeInFile(char * titleName, char * fileName, int numberOfTag, char* inputTag)
{
    FILE *pIn = NULL;       /* pointer of input file */
    int i = 0;              /* variable to run the loop */
    
    /* open input file to read and write */
    pIn = fopen("input.txt","a");
    
    /* check if file cannot open */
    if (pIn == NULL)
        {
        printf("Error open file.\n");
        }
    /* print all data into the text file */
    fprintf(pIn,"%s %s %d %s\n",titleName,fileName,numberOfTag,inputTag);
    i++;
    /* close file */
    fclose(pIn);
}
/*
 *  this function use to free the data
 *
*/
void freeList(PHOTODATA_T* pListHead)
    {
    PHOTODATA_T * pCurrent = pListHead;
    PHOTODATA_T * pFreeMe = NULL;
    while (pCurrent != NULL)
       {
       pFreeMe = pCurrent;
       pCurrent = pCurrent->pNext;
       free(pFreeMe);
       }
    }


/* this function is call function of validation.c to continue adding process
 * and display all information in data.
 */
int AddOption()
    {
    int check2 = 0;             /* check filename */
    int check = 0;              /* check title and hastag */
    char finalFile[100];        /* final filename */
    char newWord[100];          /* new filename from user */
    char choose [5];            /* answer to change filename  */
    char input[128];            /* input text from user */
    char checkFold[50];         /* input to check filename in folder */
    char titleName[128];        /* array of titlename */
    char inputTag[128];         /* array of input hastag*/
    int tagplus = 0;            /* count of line */
    int tocheck = 0;            /* check same filename in data */
    int renam = 0;              /* rename the filename */
    int check3 = 0;             /* check filename in system */
    int i = 0;                  /* variable to run the loop */
    int dummy;
    int returnVal = 0;
    int numberOfTag = 0;        /* count of hastag */
    FILE *pIn = NULL;           /* pointer of inout file */

    char keepData1[128];
    char keepData2[128];
    int keepData3 = 0;
    char keepData4[256];
    PHOTODATA_T* pData = NULL;
    PHOTODATA_T* pHead = NULL;
    PHOTODATA_T* pTail = NULL;
    PHOTODATA_T* pCurrent = NULL;

    /* option to check photo is already add */
    pIn = fopen("input.txt","r+");
    /* in case you already add */
    /* add title name */
    if ( pIn == NULL )
        {
        printf("Error - can not open file 'input.txt'\n");
        exit(0);
        }
    tagplus = 0;
    /* calloc array of data */
    while (fgets(input,sizeof(input),pIn) != NULL)
        {
        memset(keepData1,0,sizeof(keepData1));
        memset(keepData2,0,sizeof(keepData2));
        memset(keepData4,0,sizeof(keepData4));
        keepData3 = 0;
            
        sscanf(input,"%s %s %d %[^\n]s",keepData1,keepData2,&keepData3,keepData4);
        pData = (PHOTODATA_T*) calloc(1,sizeof(PHOTODATA_T));
            
        if(pData == NULL)
            {
            printf("\t\tError to calloc\n");
            exit(0);
            }

        /* copy data to our new item */
        strncpy(pData->title,keepData1,sizeof(pData->title)-1);
        strcpy(pData->filename,keepData2);
        pData->tagCount = keepData3;
        strcpy(pData->alltag,keepData4);
        if(pHead == NULL)
            {
            pHead = pTail = pData;
            }
        else
            {
            pTail->pNext = pData;
            pTail = pData;
            }
        tagplus++;
        }
    fclose(pIn);
     
    pCurrent = pHead;

    while(1)
        {
        printf("\n\t =  =  =  =  =  =  =  =  =  =  = \n\n");
        printf("\t\tAdd Photo Function! \n\n");
        printf("\t =  =  =  =  =  =  =  =  =  =  = \n");
        rules();
            printf("\n\t \t [FILE ON TEXT]\n\n");
        pCurrent = pHead;
        i = 0;
        /* display all data if check filename already sucess */
        while ( pCurrent != NULL )
        {
        printf("\t%d) %s   %s  %d  %s \n",i,pCurrent->title,pCurrent->filename,pCurrent->tagCount,pCurrent->alltag);
        i++;
        pCurrent = pCurrent->pNext;
        }
    
        printf("\n\t--> You have to copy your photo to PICTURE before use this function.");
        printf("\n\n\tPlease input you file name to check in the folder : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",checkFold);
        /* call function to check filename */
        check3 = checkNameSystem(checkFold);

        if (check3 != 0)
            {
            printf("\t\tIn PICTURE folder does not have this file name.\n");
            printf("\t\tPlease check your file name or type of file (jpg or png).\n");
            }
        else
            {
            pCurrent = pHead;
            while(pCurrent != NULL)
                {
                if(strcasecmp(checkFold,pCurrent->filename) == 0)
                    {
                    printf("\t\tThis photo already has data in file. Please input new file name.\n");
                    check3 = 1;
                    break;
                    }
                pCurrent = pCurrent->pNext;
                }
            }
        if(check3 == 0)
            {
            break;
            }
    }

    pData = pHead ;
    
    /* loop to adding titlename */
    while(1)
        {
        check = 0;
        memset(titleName,0,sizeof(titleName));
        printf("\n\tInput title name : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",titleName);
        /* call function to check titlename */
        check = checkCompareTitleInFile(titleName,pData,tagplus);
        if(check == 0)
            {
            /* call function to check titlename */
            check = checkSpecialString(titleName);
            if(check == 0)
                {
                break;
                }
            else
                {
                printf("\t\tInvalide Title name.\n");
                }
            }
        else
            {
            printf("\t\tThis title has already been use.\n");
            }
        }

    /* loop to adding filename */
    while(1)
        {
        tocheck = 0;
        check2 = 0;
        printf("\n\tDo you want to change file name?(YES or NO) : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",choose);
        if (strcasecmp("yes",choose) == 0)
            {
            while(1)
                {
                check2 = 0;
                memset(newWord,0,sizeof(newWord));
                printf("\n\tPlease enter new file name : ");
                fgets(input,sizeof(input),stdin);
                sscanf(input,"%s",newWord);
                /* call function to check new filename */
                check2 = checkFilename(newWord);
                tocheck = checkAllFileName(newWord,tagplus,pData);
                if(tocheck == 0)
                    {
                    break;
                    }
                }
            /* call function to rename */
            renam = renameFunction(checkFold,newWord);
            /* coppy new filename into new variable */
            strcpy(finalFile,newWord);
            break;
            }
        else if (strcasecmp("no",choose) == 0)
            {
            /* coppy old filename into new variable */
            strcpy(finalFile,checkFold);
            break;
            }
        else
            {
            printf("\n\tYou must input yes or no!\n");
            }
        }
    /* loop asking to add how many tags */
    while(1)
        {
        printf("\tHow many tag do you want to add(Max 10 tags)?: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&numberOfTag);
        if(numberOfTag > 0)
            {
            break;
            }
        else
            {
            printf("\t\tPlease input only numbers\n");
            }
        }
    /* loop to adding hastag */
    while(1)
        {
        printf("\tInput the tag(use - to separate tags) : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",inputTag);
        /* call function to check hastag */
        check = checkSpecialStringIntag(inputTag,numberOfTag);
        if(check == 0)
            {
            break;
            }
        else if(check == 2)
            {
            printf("\t\tNumber of tag is not match with tag\n");
            }
        else
            {
            printf("\t\tTag is incorrect, Please input again\n");
            }
        }
    strcpy(pData->title,titleName);
    strcpy(pData->filename,finalFile);
    pData->tagCount = numberOfTag;
    strcpy(pData->alltag,inputTag);
    i = 0;

    for(i = 0; i < pData->tagCount; i++)
    {
    /* call function to insert hash table */
    returnVal = hashTableInsert(pData->pTags[i], pData, &dummy);
    }

    /* call function to writing in file */
    writeInFile(titleName,finalFile,numberOfTag,inputTag);
    freeList(pHead);
    return 0;
    }
    
    
