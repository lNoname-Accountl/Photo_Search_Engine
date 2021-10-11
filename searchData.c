/*
* searchData.c
*
* This file is function searching data that will call fuction from validation.c
* to search all data and and display user choose on web browser.
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

#include"structure.h"
#include"validation.h"
#include"abstractHashTable.h"

/* this function is bit wise option of hash table
*      key - character of string key
*/
unsigned int bitwiseOpHash(char* key)
    {
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();     /* call function hashTableSize */
    int i = 0;                      /* variable to run the loop */
    
    for (i = 0; i < strlen(key); i++)
        {
        /* shift up four bits then add in next char */
        result = (result << 4) + key[i];
        if (tmp == (result & 0xf0000000))  /* if high bit is set */
            {
            /* XOR result with down shifted tmp */
            result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
            result = result ^ tmp;
            }
        }
    /* make it fit in the table size */
    result = result % size;
    return result;
    }
/* this function is to build the hash table to used on next function. */
int buildHashTable()
    {
    FILE* pInput = NULL;                /* pointer of input file */
    PHOTODATA_T * nextPhoto = NULL;     /* set nextphoto equal zero */
    char info[512];                     /* array of information */
    int returnVal = 1;                  /* return the value */
    int dummy;                          /* collision variable - set to 1 or 0 by insert */
    int i = 0;                          /* variable to run the loop */

    /* open input file to read text file */
    pInput = fopen("input.txt", "r");
    /* check if file cannot open */
    if(pInput == NULL)
        {
        printf("Error can't open file name -> input.txt <-\n");
        exit(0);
        }
    else
        {
        /* loop to read all text on txt file */
        while(fgets(info, sizeof(info), pInput) != NULL)
            {
            /* calloc array of next photo */
            nextPhoto = calloc(1, sizeof(PHOTODATA_T));
            if(nextPhoto != NULL)
                {
                sscanf(info, "%s %s %d %s", nextPhoto->title, nextPhoto->filename, &nextPhoto->tagCount, nextPhoto->alltag);
                 /* token string by - */
                nextPhoto->pTags[0] = strtok(nextPhoto->alltag ,"-");
                for(i = 1; i < nextPhoto->tagCount; i++)
                    {
                    nextPhoto->pTags[i] = strtok(NULL ,"-");
                    }
                for(i = 0; i < nextPhoto->tagCount; i++)
                    {
                    /* call function to insert hash table */
                    returnVal = hashTableInsert(nextPhoto->pTags[i], nextPhoto, &dummy);
                    }
                }
            }
        }
     /* close file input */
    fclose(pInput);
    return (returnVal);
    }
/* this function is use to display picture on web browser.
*/
int printOnWeb()
    {
    char filename[128];     /* filename to display on browser */
    char input[128];        /* input text from keyboard */
    char command[256];      /* command from browser */
    int check2 = 0;         /* value of check sucess */
    char browser[128];      /* type of web browser */
    int len = 0;            /* length of string */
    int i = 0;              /* variable to run the loop */
    int check = 0;          /* return the value */
    int checkBrowser = 0;   /* use to check browser */

    while(1)
    {
    check = 0;
    printf("\n\tWhat browser do you want to use?(ex : firefox , google chrome) : ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%[^\n]s",browser);
    if(strcasecmp(browser,"google chrome") == 0)
        {
        checkBrowser = 1;
        check = 0;
        }
    len = strlen(browser);
    for(i = 0;i < len;i++)
        {
        browser[i] = tolower(browser[i]);
        if(isspace(browser[i]) != 0)
            {
            browser[i] = '-';
            }
        }
    if(checkBrowser != 1)
        {
        check = checkSpecialString(browser);
        }
    if(check == 1)
        {
        printf("\t\tInvalid browser, please input again.\n");
        }
    else if(check == 0)
        {
        break;
        }
    }
    
    while(1)
        {
        check = 0;
        printf("\n\tWhat name of photo do you want to display?(DONE to exit) : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",filename);
        if(strcasecmp(filename,"DONE") == 0)
            {
            return 2;
            }
        check = checkFilename(filename);
        if ( check == 0)
        {
        sprintf(command,"%s picture/%s",browser,filename);
        system(command);
        break;
        }
        else
            {
            printf("\t\tInvalid file name, please input again\n");
            }
        }
    return 1;
    }
/* this function is print all data Information of searhing process
 *      tagsUser - hastag from user
 */
void printSingleData(char* tagsUser)
    {
    PHOTODATA_T** pData = NULL;
    int count;
    int j = 0;

    pData = multiHashTableLookup(tagsUser,&count);
    if(pData != NULL)
	   {
        for ( j = 0; j < count; j++ )
           {
           printf("\t\tPhoto %d : %s\n",j+1,pData[j]->filename);
           }
	   }
    else
	   {
	   printf("\n\t\tThe tags that you input don't have in the system\n\n");
       return ;
	   }
    /* call function printOnWeb */
    printOnWeb();
    }

/* this function is print all data Information of searhing process
 *      tagCount - count of hastag
 */
int printData(int tagsCount)
    {
    PHOTODATA_T *pData = NULL;          /* pointer of data */
    PHOTODATA_T *pFinalData = NULL;     /* pointer of final data */
    FILE * checkData1 = NULL;            /* pointer of file */
    FILE * checkData2 = NULL;            /* pointer of file */
    char input[512];                    /* input text from key */
    char inputName[512];
    int j = 0;                          /* variable to run the loop */
    int k = 0;                          /* variable to run the loop */
    int i = 0;                          /* variable to run the loop */
    int s = 1;                          /* variable to run the loop */
    int free = 0;                       /* variable to free */
    int count = 0;                      /* to count hastag */
    int keep = 0;                       /* to keep data */
    int fig[50];                        /* array of figture */
    int match = 0;                      /* to check match sucess */
    int dataInfile = 0;

    /* open text file */
    checkData1 = fopen("Check.txt","r");
    checkData2 = fopen("Check.txt","r");
    while(fgets(input,sizeof(input),checkData2) != NULL)
        {
        dataInfile++;
        }
    pData = (PHOTODATA_T*) calloc(dataInfile,sizeof(PHOTODATA_T));
    if(pData == NULL)
        {
        printf("\t\tError to calloc\n");
        exit(0);
        }

    while(fgets(input,sizeof(input),checkData1) != NULL)
        {
        sscanf(input,"%s",inputName);
        strcpy(pData[free].filename,inputName);
        free++;
        }
    printf("\n\t\t[PHOTO INCLUDE THE TAG]\n\n");
    for ( i = 0; i < free; i++)
        {
        fig[i] = 0;
        }
    for(i = 0; i < free; i++)
        {
        for(j = 0; j < free; j++)
            {
            if ( i != j)
                {
                if(strcasecmp(pData[i].filename,pData[j].filename) == 0)
                    {
                    fig[i] = j;
                    pData[i].matchCount = pData[i].matchCount+1;
                    pFinalData = pData;
                    match++;
                    }
                }
            }
        }
    if(match > 1)
        {
        j = 0;
        for ( i = 0; i < free ; i++)
            {
            if ( fig[i] == 0)
                {
                j++;
                }
            keep = i;
            }

        j = 0;
        for ( i = 0 ; i < free ; i++)
            {
            for ( j = 0 ; j < free ; j++)
                {
                if (strcasecmp(pData[i].filename,pData[j].filename) == 0)
                    {
                    if ( i < j)
                        {
                        keep++;
                        printf("\tPhoto %d : %s\n", s, pData[i].filename);
                        s++;
                        }
                    }
                }
            }
        }
    else
	   {
	   printf("\n\t\tThe tags not relative to each other.\n\n");
       match = 0;
	   }
    /* close text file */
    fclose(checkData1);
    fclose(checkData2);
    return match;
    }

/* this function is check to hastag from user compare with the system
*      tagsUser - hashtag from the user
*      pCheck - Text file that keep the data in system.
*/
int lastCheck(char* tagsUser , FILE * pCheck,int check)
    {
    PHOTODATA_T** pData = NULL;     /* pointer of data */
    int count = 0;                      /* count of hastag */
    int j = 0;                      /* variable to run the loop */
    int ret = 0;
    int order = 0;
        
    /* call function multiHashTableLookup */
    pData = multiHashTableLookup(tagsUser,&count);
    if (pData == NULL)
        {
        printf("\n\tThe %d tag is NULL!\n",check+1);
        ret = 1;
        }
    else
        {
        printf("\n\n\tTag  %d is %s\n\n",check+1,tagsUser);
    for ( j = 0; j < count; j++ )
        {
        fprintf(pCheck ,"%s\n", pData[j]->filename);
        printf("\t- %s\n",pData[j]->filename);
        }
        }
        return ret;
    }

/* this function check dash from hastag keyword that user input
 *      tagUser - hastag keyword from user
 */
int checkDash(char * tagUser)
    {
    int i = 0;          /* variable to run the loop */
    int check = 0;      /* to return the value */
    
    /* loop to check dash */
    for(i = 0; i < strlen(tagUser); i++)
        {
        if(tagUser[i] == '-')
            {
            check++;
            }
        }
    return check;
    }
/* this function check space from hastag keyword that user input
 *      tagUser - hastag keyword from user
 */
int checkSpace(char * tagUser)
    {
    int i = 0;          /* variable to run the loop */
    int check = 0;      /* to return the value */

    /* loop to check space */
    for(i = 0; i < strlen(tagUser); i++)
        {
        if(tagUser[i] == ' ')
            {
            check++;
            }
        }
    return check;
    }

/* this function is call function hashTableInit and buildHashTable
* to check hashtable and call function printdata to continue searching process
*/
int searchOption()
    {
    int checkTable = 1;         /* check hashtable */
    int checkBuild = 1;         /* check build hashtable */
    int check = 0;              /* check validation input */
    char keepdata[10][30];      /* array to keep data */
    char *token;                /* pointer of token string */
    int i = 0;                  /* vatiable to run the loop */
    int j = 0;                  /* variable to run the loop */
    int count = 0;		/* amount of tag */
    int print = -1;		/* keep data from printOnWeb function */
    int k = 0;			/* for loop */
    int cDash = 0;		/* keep data from checkDash function */
    int cSpace = 0;		/* keep data from checkSpace function */
    int checkLastCheck = 0;	/* keep data from lastcheck function */
    int checkFindTag = 0;	/* keep data from printdata function */
    FILE * pCheck = NULL;


    /* call function hashTableInit */
    checkTable = hashTableInit(BUCKET_COUNT, &bitwiseOpHash);
    /* create table sucess? */
    if(checkTable == 0)
        {
        printf("Error can't create table");
        exit(1);
        }
    /* call function buildHashTable */
    checkBuild = buildHashTable();
    /* build hash table sucess? */
    if(checkBuild == 0)
        {
        printf("Error building Hashtable\n");
        exit(0);
        }
    /* loop to searching data */
    while (1)
        {
        i = 0;
        printf("\n\t = = = = = = = = = = = \n\n");
        printf("\t\tSearch Photo Function! \n\n");
        printf("\t = = = = = = = = = = = \n");

        /* call function to display validation rules */
        rules();
        char input[128]; /* input text from keyboard */
        char tagsUser[128]; /* hastag input from user */
        memset(keepdata, 0,sizeof(keepdata));
        memset(tagsUser,0,sizeof(tagsUser));
        printf("\n\tFind Photo for what tags (Max 5 tags)('EXIT' to exit)? : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]s",tagsUser);
        /* call function to check dash */
        cDash = checkDash(tagsUser);
        cSpace = checkSpace(tagsUser);
        if (strcasecmp(tagsUser,"EXIT") == 0)
            {
            break;
            }
        /* get the first token */
        token = strtok(tagsUser, "-");
        /* walk through other tokens */
        while( token != NULL )
            {
            strcpy(keepdata[i],token);
            token = strtok(NULL, "-");
            i++;
            }
        count = i;
        j = 0;
            
        if (cSpace == 0)
        {
            if(cDash == 0)
            {
            for ( k = 0; k < count ; k++)
                {
                if(strlen(keepdata[k]) != 0)
                    {
                    printSingleData(keepdata[k]);
                    }
                }
            }
            else
            {
            if (cDash+1 > 5)
                {
                printf("\n\tMaximum tag is 5 sorry.\n");
                break;
                }
            checkLastCheck = 0;
            /* open output file to write */
            pCheck = fopen("Check.txt","w");
            if(pCheck == NULL)
                {
                printf("Error can't search\n");
                exit(0);
                }
            printf("\n");
            for ( k = 0; k < cDash+1 ; k++)
                {
                checkLastCheck = lastCheck(keepdata[k],pCheck,k);
                }
            if (checkLastCheck != 0)
                {
                printf("\n\tYou input wrong tags\n");
                fclose(pCheck);
                }
            /* close text file */
            /* call function to print data */
                else
                {
                fclose(pCheck);
                checkFindTag = printData(count);
                if(checkFindTag != 0)
                {
                print = printOnWeb();
                }
                if (print == 2 )
                {
                break;
                }
                }
            }
        }
            else
            {
                printf("\t- The tag only accept - in special string!\n");
            }
        }
    /* free the hash table before we exit */
    hashTableFree();
    return 0;
    }
