/*
* searchData.h
*
* This file is function searching data that will call fuction from validation.c
* to search all data and and display user choose on web browser.
*
* created by GET_A team for CPE111 project
* Kodchaphon Treesak 62070503401
* Kulchaya Songkwan 62070503405
* Chotiya Pertpring 62070503413
* Prakasit Issanapong 62070503431
*/

#define MAXTAGS 10
#define BUCKET_COUNT 5003




/* this function is bit wise option of hash table
*      key - character of string key
*/
unsigned int bitwiseOpHash(char* key);

/* this function is to build the hash table to used on next function.
*/
int buildHashTable();
    
/* this function is use to display picture on web browser.
*/
int printOnWeb(PHOTODATA_T * pData, int check);

/* this function is print all data Information of searhing process
*      tagsUser - hastag from user
*/
void printSingleData(char* tagsUser);

/* this function is print all data Information of searhing process
*      tagCount - count of hashtag
*/
int printData(int tagsCount);
    
/* this function is check to hastag from user compare with the system
*      tagsUser - hashtag from the user
*      pCheck - Text file that keep the data in system.
*/
int lastCheck(char* tagsUser , FILE * pCheck,int check);
/* this function check dash from hastag keyword that user input
*      tagUser - hastag keyword from user
*/
int checkDash(char * tagUser);
/* this function check space from hastag keyword that user input */
int checkSpace(char * tagUser);

/* this function is call function hashTableInit and buildHashTable
* to check hashtable and call function printdata to continue searching process
*/
int searchOption();
    
