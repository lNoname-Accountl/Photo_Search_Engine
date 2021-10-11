/*
* structure.h
*
* This file is structure all structure that we use on this program
* and has call library on file addData.c and searchData.c
*
* created by GET_A team for CPE111 project
* Kodchaphon Treesak 62070503401
* Kulchaya Songkwan 62070503405
* Chotiya Pertpring 62070503413
* Prakasit Issanapong 62070503431
*/

#define BUCKET_COUNT 5003
#define MAXTAGS 10

/* structure of all photo data */
typedef struct _file
    {
    char title[128];            /* array of titlename */
    char filename[128];         /* array of filename */
    char alltag[256];           /* array of all hastag */
    char tags[MAXTAGS][256];    /* array of tag in each photo */
    char* pTags[MAXTAGS];
    int tagCount;               /* how many tags are associated with this photos */
    int matchCount;             /* temporary, user in searching algorithm */
    struct _file *pNext;
    } PHOTODATA_T;


/* struct to keep all name file.*/
typedef struct
    {
    char namefile[128];         /* keep the name file of photo*/
    } PHOTODATA2_T;
