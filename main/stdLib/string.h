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
int strlen (const char *__s);


/* Find the first occurrence of NEEDLE in HAYSTACK.  */
char *strstr (const char *__haystack, const char *__needle);


/* Find the first occurrence of C in S.  */
char *strchr (char *__s, char __c);




#endif // !STRING_H
