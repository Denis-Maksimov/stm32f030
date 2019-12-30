#include "stdlib.h"
#define _HEAP_ADR (void*)0x20000800
#define _HEAP_END _HEAP_ADR+0x200
#define _HEAP_MAX_N 20
//extern char __heap[256];


static struct _obj
{
    void* _adress; 
    int _size;
}objects[_HEAP_MAX_N];

static int count=0;
static int cursor=0;


//------------------------------------------------------------
void* malloc(int size){

    if (count==_HEAP_MAX_N)
        return 0;
        
    if (count==0){
        objects[0]._adress=_HEAP_ADR;
        objects[0]._size=size;
        cursor+=size;
    }
    else if (count==1){
        objects[1]._adress=objects[0]._adress+objects[0]._size;
        objects[1]._size=size;
        cursor+=size;
    }
    else{
        //void* tmp;
        for(int i=0;i<count-1;i++){

            if( //если между двумя можно впихнуть новый участок памяти
                (objects[i+1]._adress - (objects[i]._adress+objects[i]._size) ) >= size
              ){
                //то впихиваем его в конец первого
                objects[count]._adress = (objects[i]._adress+objects[i]._size);
                objects[count]._size=size;
                break;
            }
        //ну не впихнуть между!
        objects[count]._adress=_HEAP_ADR;
        objects[count]._size=size;
        cursor+=size;
        }

    }
    count++;
    return objects[count]._adress;
}// ! malloc

//------------------------------------------------------------
void free(void* pointer){
    //найти объект по указателю
    int status=0;
    int i=0;
    for( ; i<count; i++ ){
        if(objects[i]._adress==pointer){
            //нашли
            status=1;
            break;
        }
    }

    //нашли
    if(status){
        count=count-1;
        for( ; i<count; i++ ){
            //переиндексация
            objects[i]._adress=objects[i+1]._adress;
            objects[i]._size=objects[i+1]._size;
            status=1;
            break;
        }

    }
    
}
//---------------------------------------------------------------
/* Set N bytes of S to C.  */
void* memset (char *__s, int __c, uint32_t __n){
    for (int i=0; i<__n; i++){
        __s[i]=__c;
    }
    return __s;
}

