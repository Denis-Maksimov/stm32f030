/*********************************************
 * stdlib.h / stdlib.c
 * -----------------------------------------
 * Велосипед с треугльными колёсами
 * Привык к динамическому распределению памяти,
 * а за неимением стандартной библиотеки для МК
 * (+ просто хотелось с нуля всё сделать, тем более,
 * что и так даже без CMSIS пишу) пришлось написать 
 * этого монстра.
 * 
 * програмистам советую не смотреть реализацию - потекут глаза.
 * 
 * ------------------------------------------
 * 
 * 1) создаётся массив структур для хранения
 * адреса и размера выделенной памяти.
 * Так как я не сумел изъебнуться и рекурсивно
 * решить задачу, количество участков распределения
 * памяти задаётся статически через макрос:
 * 
 * _HEAP_MAX_N 
 * 
 * в конце я его ундефайню, чтобы больше нигде не выстрелил
 * ------------------------------------------
 * 2) u_malloc(__ЧИСЛО_БАЙТ__);
 * 
 *  эта функция разбита внутри на несколько частных случаев,
 * но по сути все они ищут свободный участок памяти внутри массива
 * __heap[], и записывают в массив структуры(1) 
 * новый адрес и память для нового дин. массива  
 * ------------------------------------------
 * 3) u_free() - ищет в структуре(1) адрес
 * и если он есть удаляет его и сдвигает на его
 * место следующие за ним элементы (в структуре а не в куче)
**********************************************/

#include "stdlib.h"

#define _HEAP_MAX_N 20

char __heap[256];


static struct _obj
{
    void* _adress; 
    int _size;
}objects[_HEAP_MAX_N];

static int uStd_count=0;


//------------------------------------------------------------

void blk_mov(struct _obj* parray,int size){
    while(size){
        parray[size]=parray[size-1];
        size--;
    }
}
//------------------------------------------------------------

void* u_malloc(int size){
    //-- ограничение по колличеству --
    if (uStd_count==_HEAP_MAX_N)
    {  
        return 0;
    }
    struct _obj tmp;
    //-- если ещё не выделяли память --    
    if (uStd_count==0){
        objects[0]._adress= &__heap[0];
        objects[0]._size=size;
        uStd_count++;
        return objects[0]._adress;
    }

    //-- если один элемент только --
    else if (uStd_count==1){
        //-- если можно впихнуть в начало
        if(   (objects[0]._adress - (void*)__heap)  >= size )
        {
            // 2 -> [_,1]
            // t=1  [_,2]
            //      [1,2]     
            

            tmp._adress = objects[0]._adress;
            tmp._size = objects[0]._size;

            objects[0]._adress = __heap;
            objects[0]._size   = size;

            objects[uStd_count]._adress = tmp._adress;
            objects[uStd_count]._size   = tmp._size;

            uStd_count++;
            return objects[uStd_count]._adress;

        //-- иначе пихаем в конец  
        }else{
            
            objects[uStd_count]._adress = objects[0]._adress + objects[0]._size;
            objects[uStd_count]._size   = size;
            uStd_count++;
            return objects[uStd_count-1]._adress;
        }


    }
    //-- если много элементов --
    else{
        
        //-- если можно впихнуть в самое начало
        if(   (objects[0]._adress - (void*)__heap)  >= size )
        {

            blk_mov(&objects[0], uStd_count);
            
            objects[0]._adress = __heap;
            objects[0]._size   = size;


            uStd_count++;
            return objects[0]._adress;
        }
        //-- для каждого проверяем:
        for(int i=0; i < uStd_count-1; i++){

            //-- если можно впихнуть между
            if( 
                (objects[i+1]._adress - (objects[i]._adress+objects[i]._size) ) >= size
              ){
                //то впихиваем его в конец первого
                //c=3   [12>4567]
                //c=3   [1234567]
                blk_mov(&objects[i], uStd_count-i);

                objects[i+1]._adress = (objects[i]._adress+objects[i]._size);
                objects[i+1]._size=size;
                uStd_count++;
                return objects[i+1]._adress;
                
            }
        }
        //ну не впихнуть между!
        objects[uStd_count]._adress = objects[uStd_count-1]._adress + objects[uStd_count-1]._size;
        objects[uStd_count]._size = size;
        uStd_count++;
        return objects[uStd_count-1]._adress;
        

    }

}// ! malloc


//------------------------------------------------------------

/** забываем про элемент **
* [1,2,(3),4,5,6]
* [1,2,   ,4,5,6]
* [1,2,   ,3,4,5] 
************************/
void u_free(void* pointer){
    //найти объект по указателю
    int status=0;
    int i=0;
    
    //проходим по элементам
    for( ; i<uStd_count; i++ ){
        if(objects[i]._adress==pointer){
            //нашли
            status=1;
            break;
        }
    }

    //нашли
    if(status){
        uStd_count=uStd_count-1;
        for( ; i<uStd_count; i++ ){
            //переиндексация
            objects[i]._adress = objects[i+1]._adress;
            objects[i]._size = objects[i+1]._size;
            //status=1;
            //break;
        }
        return;

    }
    
}
//---------------------------------------------------------------
/* Set N bytes of S to C.  */
void* u_memset (char *__s, int __c, uint32_t __n){
    for (int i=0; i<__n; i++){
        __s[i]=__c;
    }
    return __s;
}

#undef _HEAP_MAX_N


/******************** Test *****************************************

#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    //-- время между puts()
    int demo_time_s=1;
    _memset(__heap,'0',25);
    __heap[25]=0;
    puts("Memory before allocation");
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("malloc 5 bytes for 1 array");
    char* array=(char*)_malloc(5);
    _memset(array,'1',5);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("malloc 5 bytes for 2 array");
    char* array2=(char*)_malloc(5);
    _memset(array2,'2',5);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("malloc 5 bytes for 3 array");
    char* array3=(char*)_malloc(5);
    _memset(array3,'3',5);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("free 1 array");
    _free(array);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("malloc 3 bytes for 1 array");
    array=(char*)_malloc(3);
    _memset(array,'4',3);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("free 3 array");
    _free(array3);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    sleep(demo_time_s);
    puts("malloc 3 bytes for 3 array");
    array3=(char*)_malloc(3);
    _memset(array3,'5',3);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    
    sleep(demo_time_s);
    puts("malloc 2 bytes for 4 array");
    char* array4=(char*)_malloc(2);
    _memset(array4,'6',2);
    puts(__heap);
    printf("%u",uStd_count);
    puts("---------------------------\n");
    
    

}

*****************************************/