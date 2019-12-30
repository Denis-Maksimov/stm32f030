#ifndef STDLIB_H
#define STDLIB_H

typedef unsigned int uint32_t;
typedef unsigned int size_t;

void* malloc(int _size);
void* calloc(int _size);
void free(void* pointer);

/* Set N bytes of S to C.  */
void* memset (char *__s, int __c, uint32_t __n);


#endif // !STDLIB_H
