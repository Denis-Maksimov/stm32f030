#ifndef U_MATH_H
#define U_MATH_H

#include "u_stddef.h"

#define STDLIB_API  extern

/**
 * @brief  высчитывает 0xFFFF FFFF/2 * sin(deg)
 * @note   
 * @param  deg: 
 * @retval 
 */
STDLIB_API s32 u_sin(s32 deg);

/**
 * @brief  высчитывает 0xFFFF FFFF/2 * cos(deg)
 * @note   
 * @param  deg: 
 * @retval 
 */
STDLIB_API s32 u_cos(s32 deg);

/**
 * @brief  высчитывает квадратный корень
 * @note   используется итерационная формула Герона в 10 итераций
 * @param  A: 
 * @retval 
 */
STDLIB_API u32 u_sqrt(u32 A);
STDLIB_API u32 u_exp(u32 A, u32 n);

/*корень n-й степени*/
STDLIB_API u32 u_nth_root(u32 A, u32 n);




//!!! FIXME XXX TODO!!!
// STDLIB_API s32 u_tg(s32 deg);

//!!! FIXME XXX TODO!!!
// STDLIB_API s32 u_ctg(s32 deg);

#undef STDLIB_API
#endif // !U_MATH_H
