#ifndef U_CHAIN_H
#define U_CHAIN_H
#include "u_stddef.h"

#define STDLIB_API  extern

//-------------
struct Array{
    void* data;
    size_t n;
};
//-------------

struct chain
{
  struct chain* prew_chain;
  struct chain* next_chain;
  struct Array array;

};

typedef struct chain u_list;

// extern struct chain* init_chain();
/**
 * @brief  создаёт двусвязный список и помещает данные в первый элемент
 * @note   Не теряйте указатель на первый элемент!
 * @param  _data: данные
 * @param  n: размер данных в байтах
 * @retval указатель
 */
u_list* u_new_chain(void* _data, size_t n);

u_list* u_find_last(u_list* ch);

u_list* u_find_first(u_list* ch);

/**
 * @brief  объединяет 2 цепи в одну
 * @note   
 * @param  first: 
 * @param  second: 
 * @retval 
 */
 int u_attach(u_list* first, u_list* second);

STDLIB_API u_list* u_insert_after(u_list* dest, void* data, size_t n);
STDLIB_API u_list* u_insert_after_ch(u_list* dest, u_list* ch);
STDLIB_API u_list* u_insert_before(u_list* dest, void* data, size_t n);
STDLIB_API void u_free_chain(u_list* ch);
STDLIB_API u_list* u_cut(u_list* ch);
STDLIB_API u_list* u_copy(u_list* ch);
STDLIB_API void u_rewrite_chain(u_list* ch,void* data, size_t n);

#undef STDLIB_API
#endif // !U_CHAIN_H
