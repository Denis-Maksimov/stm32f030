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


        char* ret_buf=(char*)u_malloc(i_max+1);

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
/*****************************************************
 *  Используется алгоритм Бойера-Мура	             *
 * ------------------------------------------------- */
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
char* strstr(const char* __haystack, const char* __needle){
    
    int len = strlen(__needle); //длина запроса
    char* end_adress = (char*)(len + (size_t)__needle); //адрес конца
    char* table =(char*) u_malloc(len); //table
    

    //======================
    //--1) Составляем таблицу --
	//======================
    for (int i=1; i<=len;i++){
        
        //-- Присваиваем позицию последнего вхождения
        table[len-i] = end_adress - strrchr(__needle, __needle[len-i]);

        //-- исключение завершающий символ:
        if (table[len-i]==0){

			//-- если такой символ есть, то присваеваем ему его индекс
            if(strrevchr(__needle+len-1,len-1,__needle[len-i])) 
			{
                table[len-i] = end_adress - strrevchr(__needle+len-1,len-1,__needle[len-i]);
			} 
			 //-- иначе равным длинне строки
			 else 
			{
                table[len-i]=len;
			}

		}
    }// = Таблица готова =

    //======================
    //--2) поиск в строке
	//======================
    int counter=len;                  // <- начинаем с конца слова
    int text_len=strlen(__haystack);  // инициализация длинны массива, в котором ищем
    char* tmp_res=0;

    while(counter<=text_len){

        //-- Проверяем, нашли ли мы то, что искали
        if(strncmp(__haystack+counter-len, __needle, len)==0)
        {   
            u_free (table);
            return (char*)((size_t)__haystack+counter-len);
        }
        //-- если нет, то уточнаем, есть ли такой символ в поисковом запросе
        tmp_res = strchr(__needle, __haystack[counter]);
        if(tmp_res){

            //-- если есть, то ищем индекс в таблице, и ищем уже на индексном расстоянии от места поиска
            counter += (table[(tmp_res-__needle)]);
  
            
        }else{
			//-- иначе можно пропустить слово и искать на расстояни len
            counter=counter+len;
        }
        
    }
    //-- если не нашли, то возвращаем указатель на нуль
    u_free (table);
    return 0;
    
}


//-------------------------------------------------------


//обратный поиск
char* strrevchr(const char* line, int len , const char chr){
    line= line - len;
    
    int i=len;
    while(i>0){
        if (line[i-len]==chr)return (char*)((size_t)line+i-len);
        i--;
    }
    return 0;
}

//----------------------------------------------------------

/* Find the first occurrence of C in S.  */
char* strchr (const char *__s, const char __c){
	for(int i=0;i<strlen(__s);i++){
		if(__s[i]==__c) return (char*)((size_t)__s + i);
	}
	return 0;
}

//----------------------------------------------------------

/* Find the last occurrence of C in S.  */
char *strrchr(const char *__s, const char __c){
	for(int i=strlen(__s);i>=0;i--){
		if(__s[i]==__c) return (char*)((size_t)__s + i);
	}
	return 0;

}

//-----------------------------------------------------------

/* Compare N characters of S1 and S2.  */
size_t strncmp(const char* __str1, const char* __str2, size_t __n){

	for(int i; i < __n; i++)
	{
		if(__str1[i]!=__str2[i])
		{
			return (__str1[i] - __str2[i]);
		}

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
