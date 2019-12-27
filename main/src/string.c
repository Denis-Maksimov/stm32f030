#include "string.h"

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