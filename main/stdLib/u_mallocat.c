#include "u_mallocat.h"


struct chain
{
  struct chain* prew_chain;
  struct chain* next_chain;
  size_t n;
  u8* data;

};



static u8 _heap[MY_HEAP_SIZE]={0};
#define END_HEAP    ((&_heap[MY_HEAP_SIZE]))
// #define c_new(type) (type*)malloc(sizeof(type))

static struct chain* _start_chain=(struct chain*)_heap;

void* u_get_start_chain(void)
{
    return _start_chain;
}

//=============================================================
static void _attach2_chains(struct chain* first, struct chain* sec)
{
    struct chain* fn=0;
    if(first){
        fn=first->next_chain;
        first->next_chain=sec;
    }
    if(sec){    
        sec->prew_chain=first;
        sec->next_chain=fn;
    }
    if(fn){
        fn->prew_chain=sec;
    }
}


//!reserved
// static struct chain* _find_last(struct chain* ch)
// {

//     //----------------------------
//      //0-1-2-3-4
// 	struct chain* ch1=ch; //4
//     struct chain* ch2=ch1;

//     while(ch1->next_chain)
// 	{   
//         ch2=ch1;
// 		ch1=ch2->next_chain;
	
// 	}
// 	return ch1;
// }



static void* _find_free_memory(size_t n_bytes, struct chain** prew_ch)
{

    //----------------------------
     //0-1-2-3-4
	struct chain* ch1=_start_chain; //4
    struct chain* ch2=ch1;

    while(ch1->next_chain)
	{   
        // если хватает места перед следующим
        // printf(">>%u<</%d\n",(u8*)(ch1->next_chain) - (u8*)(ch1) , n_bytes  );
        if( (u8*)(ch1->next_chain) - (u8*)(ch1) >= n_bytes+sizeof(struct chain)-sizeof(u8*)){
            // printf("++%d++\n",(u8*)(ch1->next_chain) - (u8*)(ch1) - 24  );
            *prew_ch=ch1;

            u8** adr=&(ch1->data);
            return (u8*)adr+ch1->n;
        }

        ch2=ch1;
		ch1=ch2->next_chain;
	
	}

    *prew_ch=ch1;

    u8** adr=&(ch1->data);
	return (u8*)adr+(ch1->n);
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

void* u_malloc(size_t n_bytes)
{
    struct chain* prew_ch=0;
    struct chain* new_ch=_find_free_memory(n_bytes+sizeof(struct chain), &prew_ch); //find_last(_start_chain);
    
    // size_t nn=prew_ch->array.n;
    // new_ch=(&(prew_ch->array.data))+nn;
    if((u8*)(&new_ch->data)+n_bytes<(END_HEAP))
    {
        // printf("free:%d\n",END_HEAP-(u8*)(&new_ch->data)-n_bytes);
        // sleep(1);
        _attach2_chains(prew_ch, new_ch);
        // new_ch->next_chain=0;
        new_ch->n=n_bytes;
        // printf("**%d\n",new_ch+n_bytes-prew_ch);
        return &(new_ch->data);
    
    }
    // perror("cannot memory to u_malloc\n");
    return 0;
    
    
}

void u_free(void* ptr)
{
    //----------------------------
     //0-1-2-3-4
	struct chain* ch1=_start_chain; //4
    struct chain* ch2;

	// if(!ch1->prew_chain) {return ch;}

    while(ch1)
	{   
        ch2=ch1;
		ch1=ch2->next_chain;
        if(&(ch1->data)==ptr){
            // _attach2_chains(ch1->prew_chain, ch1->next_chain);
            ch1->prew_chain->next_chain=ch1->next_chain;
            if(ch1->next_chain){
                ch1->next_chain->prew_chain=ch1->prew_chain;
            }
            u_memset(ch1, 0, sizeof(struct chain)+ch1->n);
            return;
        }
        
	}
    // perror("no allocated ptr!\n");
	return;

}
//========================================================================================================================
//========================================================================================================================
//========================================================================================================================
//========================================================================================================================
//========================================================================================================================
#ifdef DEBUG



#include <stdio.h>
void print_chain()
{

    struct chain* first; 
    struct chain* nxt = _start_chain->next_chain;
    // int n=0;
    while (nxt)
    {
        // n++;
        first=nxt;
        nxt=first->next_chain;
        printf("0x%X:\n", first);
        printf("  prew:0x%X\n", first->prew_chain);
        printf("  next:0x%X\n", first->next_chain);
        printf("%s :%d bytes\n", (u8*)(&first->data), first->n);
        
        // printf("0x%X. %s %d/%d bytes\n",&first->data ,(u8*)(&(first->data)) , first->n, (&first->data[first->n])-(&first->data[0]));
        // sleep(1);
    }
    puts("_________________");
    
}



/**
 * @brief Тест на добавление и удаление 
 * @note   
 * @retval None
*/

void test1(){
    puts("==\\--test1--/==");
    char data[] = "Hello, my allocated world!";//28
    char data2[] = "Bye, my allocated world!";//26

    puts("адрес начала виртуальной кучи:");
    printf("0x%X\n",_heap);

    char* new=u_malloc(sizeof(data));
    u_memcpy(new,data,sizeof(data));
    puts("first+");
    print_chain();

    char* new1=u_malloc(sizeof(data2));   
    u_memcpy(new1,data2,sizeof(data2));
    puts("second+");
    print_chain();
    

    puts("удаляем первый добавленный элемент");
    u_free(new);
    // print_chain();

    puts("----------------------------\n");

    puts("снова добавляем и смотрим выделенный адрес:");
    new=u_malloc(sizeof(data));
    u_memcpy(new,data,sizeof(data));
    print_chain();

    puts("===========================\n\n");

}

/**
 * @brief  Тест на переполнение
 * @note   
 * @param  bytes: сколько байтов выделять зараз (до 16 сохранится в дампе)
 * @retval None
 */
void test2(u32 bytes)
{
    puts("==\\--test2--/==");
    int n=0;
    printf("Проверяем, сколько байтов %d-байтовой фигни залезет в %d байт кучи\n",bytes, MY_HEAP_SIZE);
    void* mem=(void*)1;
    while(mem)
    {   
        mem=u_malloc(bytes);
        if(mem)  u_memcpy(mem,"123456789abcdef",bytes);
        putc('.',stdout);
        n++;
    }
    puts("\nдамп кучковой цепочки:");
    print_chain();

    printf("\nТест завершён с результатом %d\n",n);
    puts("===========================\n\n");

}


void dump(char* file){
    FILE* fd= fopen(file,"wb");
    fwrite(_heap,MY_HEAP_SIZE,1,fd);
}


int main() {

    test1();
    test2(1);
    dump("./log");
    return 0;
}


#endif // DEBUG
