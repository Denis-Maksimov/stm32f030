typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

#include "u_mallocat.h"
#define uHEAP_SIZE  MY_HEAP_SIZE

struct memory_block{
    u16 is_available:1;
	u16 size:15;
};//_head_mcb={1,uHEAP_SIZE-sizeof(struct memory_block)};

static u8 heap[uHEAP_SIZE]={1|(((uHEAP_SIZE-sizeof(struct memory_block))<<1)&0xff),(((uHEAP_SIZE-sizeof(struct memory_block))<<1)&0xff00)>>8};

// void first_init(){
//     ((struct memory_block*)((void*)heap))->is_available=1;
//     ((struct memory_block*)((void*)heap))->size=uHEAP_SIZE-sizeof(struct memory_block);
// }


static void* process_alloc(struct memory_block* heap_mb,u16 size){
    heap_mb->is_available=0;
    u16 old = heap_mb->size;
    heap_mb->size=size;

    if(old-size>0){
        struct memory_block* new = ((struct memory_block*)(((u8*)(void*)heap_mb)+size+sizeof(struct memory_block)));
        new->is_available=1;
        new->size=old-size-sizeof(struct memory_block);
    }
    return &heap_mb[1];
}

void* u_malloc(size_t size){
    u16 aval_size=uHEAP_SIZE;
    struct memory_block* heap_ptr=((struct memory_block*)((void*)heap));
    while (aval_size>0)
    {
        aval_size=aval_size-sizeof(struct memory_block);
        if(heap_ptr->is_available&&heap_ptr->size-size>=0)
        {
            return process_alloc(heap_ptr,(u16)size);
        }

        //если в блоке нет памяти или он занят, прыгаем в следующий блок
        // if(!heap_ptr->is_available||heap_ptr->size-size<0){
            aval_size=aval_size-heap_ptr->size;
            heap_ptr=( struct memory_block*)((u8*)heap_ptr+heap_ptr->size+sizeof(struct memory_block));
            // continue;
        // }

    }
    return 0;
    
}

static void merge_heap(void)
{
    //TODO
    //указатель на начало
    struct memory_block* heap_mb=((struct memory_block*)((void*)heap));
    //указатель на следующий для шагания
    struct memory_block* heap_mb_next;

    //когда это значение == 0, значит память кончилась
    u16 aval_size=uHEAP_SIZE-sizeof(struct memory_block)-heap_mb->size;

    while(aval_size>0){
        //ищем где следующий блок
        heap_mb_next=(struct memory_block*)((u8*)heap_mb+heap_mb->size+sizeof(struct memory_block));

        //если текущий и следующий свободные, то мержим их
        if(heap_mb->is_available&&heap_mb_next->is_available)
        {
            //увеличиваем размер 1-го на размер 2-го+размер заголовка
            heap_mb->size+=heap_mb_next->size;
            //и показываем, что проверили
            aval_size-=heap_mb_next->size;

        }else{//иначе шагаем дальше
            heap_mb=heap_mb_next;
            aval_size-=heap_mb_next->size;
            aval_size-=sizeof(struct memory_block);
            /* code */
        }
        
    }
}

void u_free(void* ptr)
{

    struct memory_block* heap_mb=(struct memory_block*)ptr-1;
    heap_mb->is_available=1;
    merge_heap();
    
    //Шаг назад, говорим, что свободны, и мержим смежные блоки в хипе
}


void* u_memset(void *__s, u8 __c, size_t __n)
{
    for(int i=0;i<__n;i++)
    {
        ((u8*)__s)[i]=__c;
    }
    return __s;
}

void* u_memcpy(void *__dest, const void *__src, size_t __n)
{
    for(int i=0;i<__n;i++)
    {
        ((u8*)__dest)[i]=((u8*)__src)[i];
    }
    return __dest;
}

