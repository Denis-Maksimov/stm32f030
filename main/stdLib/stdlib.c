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

#define _HEAP_MAX_N 50

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

void* u_realloc(void* ptr, int size){
    u_free(ptr);
    ptr = u_malloc(size);
    return ptr;
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
/*
void core_div(uint32_t delimoe, uint32_t delitel){
        uint32_t arg0=delimoe;
        uint32_t arg1=delitel;

        __asm__ volatile(
           "signed_divide \n\t"
Деление со знаком содержимого регистра %1 на %0: результат в %0, остаток в %1
Получить абсолютное значение %0 и разместить его в R3
    "ASR R2, %0, #31       \n\t" // Получить 0 или -1 в R2 в зависимости от знака %0
    "EOR %0, R2               \n\t" // EOR с -1 (0xFFFFFFFF), если минус
    "SUB R3, %0, R2           \n\t" // и выполнить ADD 1 (SUB -1) для получения asb значения
    "                         \n\t" // SUB всегда влияет на флаги CPSR:
   "BEQ divide_by_zero       \n\t" // если деление на ноль, то соообщить об этом.

Получить asb значение содержимого %1 выполняя EOR с 0xFFFFFFFF 
и дополнить единицей, если минус
    "ASR %0, %1, #31           \n\t" // Получить 0 или -1 в R3 в зависимости от знака %1
    "EOR %1, %0                \n\t" // EOR с -1 (0xFFFFFFFF), если минус
    "SUB %1, %0                \n\t" // и выполнить ADD 1 (SUB -1) для получения asb значения

Сохранить знаки (0 или -1 в %0 & R2) для последующего использования
    "PUSH {%0, R2}       \n\t" //

Выравнивание, сдвиг вправо на один бит до тех пор, пока делитель (содержимое %0)
меньше или равно, чем делимое (содержимое %1). 
    "LSR %0, %1, #1     \n\t" //
    "MOV R2, R3         \n\t" //
    "B %FT0             \n\t" //

"just_l                 \n\t" //
    "LSL R2, #1         \n\t" //
"0                      \n\t" //
    "CMP R2, %0         \n\t" //
    "BLS just_l         \n\t" //
    "MOV %0, #0         \n\t" // Очистить %0
    "B %FT0             \n\t" // Перейти к циклу деления

"div_l                  \n\t" //
    "LSR R2, #1         \n\t" //
"0                      \n\t" //    
    "CMP %1, R2         \n\t" // %1 > R2 ?
    "BCC %FT0           \n\t" //
    "SUB %1, R2         \n\t" // Выполнить обычное вычитание
"0                      \n\t" //
    "ADC %0, %0         \n\t" // Сдвиг результат и сложение с единицей
    "CMP R2, R3         \n\t" // Прервать, когда R2 равно R3
    "BNE div_l 	        \n\t" //

Откорректировать знак результата (%0) и остатка от деления (%1)
    "POP {R2, R3}       \n\t" // Извлечь из стека знаки делимого и делителя
    "EOR R3, R2         \n\t" // Знак результата
    "EOR %0, R3         \n\t" // Минус, если знак результата равен -1
    "SUB %0, R3         \n\t" //
    "EOR %1, R2         \n\t" // Инверсия остатка от деления, если знак делимого равен -1
    "SUB %1, R2         \n\t" //
          :
          :"r"(arg0),"r"(arg1)
          :"r2","r3"
            
        )    ;
            
            
    
    
    
}*/



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
