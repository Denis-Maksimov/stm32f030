#include "string.h"


/****************************************
 *  Функция декодирования числа в формат строки
 * integer - число
 * возвращает массив
 * *********************************/
void* itoa(int integer){


	char buf[]={'0','0','0','0','0',   '0','0','0','0','0',  '\0'};
  	int flag_minus=0, 
	  	i=0,
	  	carry=0,
	  	i_max=0;

	  	//для отрицательных чисел нужен "-"
    	if(integer<0)
		{
        	integer*=-1;
        	flag_minus=1;
    	}
		

		// по методу инкрементирования набираем наше число
		// для больших чисел - очень долго!!! но зато без деления
		while(integer)
		{
            (i_max<i)?(i_max=i):(i_max);
			i=0;
			carry=1;

			while (carry&1)
			{
                buf[i]++;
				if(buf[i]==58) {
					buf[i]='0';
					i++;
					carry=1;	
				}else carry = 0;
			}
			integer--;
		}
    
        
		//для отрицательных чисел нужен "-"
        if(flag_minus){
            i_max++;
            buf[i_max]='-';
        }


        char* ret_buf=(char*)malloc(i_max+1);

		//разворачиваем массив и убираем лишние нули
        for(int i=0;i<i_max+1;i++){
            ret_buf[i]=buf[i_max-i];
        }

	return ret_buf;

}//itoa

//---------------------------------------------------------

void intToStr(int integer,char* baf){
	/* Функция декодирования числа в формат строки
	integer - число
	buf - возвразаемая строка */
	char buf[11]={0};
  	int i=0;
	int flag=0;
    	if(integer<0){
        	flag=1;
        	integer*=-1;
        	i++;
    	}//if если отрицательное
    	int b=10;
    	while(1){
        	buf[i]=((integer%b)-(integer%(b/10)))/(b/10);
        	buf[i]+=48;
        	if(integer%b==integer)
			break;
        	b*=10;
        	i++;
    	}//while

	int qw=0;
	if(flag){i++;buf[i]='-';}
	while(i>=0){
		baf[qw]=buf[i];
		i--;
		qw++;
	}

    	baf[qw]='\0';
	return;
}//intToStr

//----------------------------------------------------------

/* Return the length of S.  */
int strlen (const char *__s){
	int i=0;
	while(1){
		if(__s[i]=='\0')break;
		i++;
	}
	return i;
}

//----------------------------------------------------------

/* Find the first occurrence of NEEDLE in HAYSTACK.  */
char *strstr (const char *__haystack, const char *__needle){
	///TODO:
	return 0;
}

//----------------------------------------------------------

/* Find the first occurrence of C in S.  */
char *strchr (char *__s, char __c){
	for(int i=0;i<strlen(__s);i++){
		if(__s[i]==__c) return __s + i;
	}
	return 0;
}







// -----------------------------------------------------------------
/* Чёрная магия с просторов хабра, красиво, как по мне
u8 CountOnes3 (u8 n) {
  if (n == 0)  return 0;  // Единственный случай, когда ответ 0.
  if (n == 0xFF)  return 8;  // Единственный случай, когда ответ 8.
  n = (0x010101*n & 0x249249) % 7;  // Считаем число бит по модулю 7.
  if (n == 0)  return 7;  // Гарантированно имеем 7 единичных битов.
  return n;  // Случай, когда в числе от 1 до 6 единичных битов.
}
*/
