#ifndef U_STRING_H
#define U_STRING_H


#include "u_stddef.h"
#include "u_mallocat.h"
#define STDLIB_API  extern
//если не поддерживается деление
// #define NO_DIVISION

STDLIB_API void u_intToStr(unsigned int n, char* s);
// extern void u_intToStr(unsigned int n, char* s);


STDLIB_API void u_intToHex(unsigned int integer,char* baf);
//

// conversion integer --> to string 
// void intToStr(int integer,char* baf); 

/* Return the length of S.  */
STDLIB_API int u_strlen (const char* __s);


/* Find the first occurrence of NEEDLE in HAYSTACK.  */
STDLIB_API char* u_strstr (const char* __haystack, const char* __needle);


/* Find the first occurrence of C in S.  */
STDLIB_API char* u_strchr (const char* __s, const char __c);

//обратный поиск массива от адреса, длинной len
STDLIB_API char* u_strrevchr(const char* line, int len , const char chr);

STDLIB_API size_t u_strncmp(const char* str1, const char* str2, size_t len);

/* Find the last occurrence of C in S.  */
STDLIB_API char* u_strrchr(const char* __s, const char __c);

#undef STDLIB_API
#endif // !STRING_H
