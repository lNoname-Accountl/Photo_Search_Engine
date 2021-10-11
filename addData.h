/*
 * addData.h
 *
 * This file is function adding data that will call fuction from validation.c
 * to display all data , edit(rename) data dataand writing data into the text file.
 *
 * created by GET_A team for CPE111 project
 * Kodchaphon Treesak 62070503401
 * Kulchaya Songkwan 62070503405
 * Chotiya Pertpring 62070503413
 * Prakasit Issanapong 62070503431
 */
#include "structure.h"
/* this function is rename from filename that already check in folder
 * and adding into the text file.
 *      name1 - filename already check in folder
 *      name2 - new filename want to change
 */
int renameFunction(char *name1,char *name2);

/* this function is writing all data into the text file
 *      titleName - titlename of adding photo
 *      fileName - filename of adding photo
 *      numberOfTag - count tag of adding photo
 *      inputTag - array of hastag of adding photo
 */
void writeInFile(char * titleName, char * fileName, int numberOfTag, char* inputTag);


/* use to free data */
void freeList(PHOTODATA_T* pListHead);
/* this function is call function of validation.c to continue adding process
 * and display all information in data.
 */
int AddOption();

   
