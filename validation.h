/*
 * validation.h
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

/* this function is rules to guide user to typing correctly information */
void rules();

/* this function will check all filename of picture in data folder
 * if input has found on data folder this function will print all data.
 *      name - input of filename in .jpg or .png
 *      valid = 0 , invalid = 1
 */
int checkNameSystem(char *name);
    
/* this function will compare is input of title name same as titile name in data
 * if input has same as data this function will invalid.
 *      string1 - input of title name from user
 *      data - structure of data
 *      count - count of all data
 *      valid = 0 , invalid = 1
*/
int checkCompareTitleInFile(char * string1, PHOTODATA_T * data, int count);

/* this function will check the special string of all hastag
 * if input has found any speacial string this function will invalid.
 *      string - input of hastag from user
 *      numberTag - count of hastag from user
 *      valid = 0 , invalid = 1 , invalid(not match tag) = 2
 */
int checkSpecialStringIntag(char * string, int numberTag);

/* this function will check the special string of all title name
* if input has found any speacial string this function will invalid.
*      string - input of title name from user
*      valid = 0 , invalid = 1
*/
int checkSpecialString(char * string);

/* this function will check all filename from user.
 * if input has any special string has blankspace and no has .jpg or .png
 * this function will invalid.
 *      filename - input of filename in .jpg or .png
 *      valid = 0 , invalid = 1
 */
int checkFilename(char * filename);

/* this function will check is new input has the same filename in data.
 * if input has same as data this function will invalid.
 *      name - new input of filename in .jpg or .png
 *      tagplus - count of information in data.
 *      pData - pointer of data
 *      valid = 0 , invalid = 1
 */
int checkAllFileName(char *name,int tagplus,PHOTODATA_T * pData);
    

   
