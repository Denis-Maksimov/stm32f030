#ifndef STRING_H
#define STRING_H


#include "stdlib.h"

/**********************************
 * \brief slowely func for 
 * conversion integer to ASCII
 * \return pointer of array ASCII 
**********************************/
//void* itoa(int integer);

// conversion integer --> to string 
void intToStr(int integer,char* baf); 

/* Return the length of S.  */
int strlen (const char* __s);


/* Find the first occurrence of NEEDLE in HAYSTACK.  */
char *strstr (const char* __haystack, const char* __needle);


/* Find the first occurrence of C in S.  */
char *strchr (const char* __s, const char __c);

//обратный поиск массива от адреса, длинной len
char* strrevchr(const char* line, int len , const char chr);

size_t strncmp(const char* str1, const char* str2, size_t len);

/* Find the last occurrence of C in S.  */
char* strrchr(const char* __s, const char __c);


#endif // !STRING_H
