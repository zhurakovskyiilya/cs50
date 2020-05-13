#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int shift(char c);

int main(int argc, string argv[]) 
{

if (argc != 2) 
  {
      printf("Usage key %s\n",argv[0]);
      return 1;
  }
else
  {
 
    for (int i = 0, n = strlen(argv[1]); i < n; i++) 
    {
          if ( isdigit (argv[1] [i]))
          {
              printf("Usage: ./vigenere keyword %s\n",argv[0]);
              return 0;
          } 
         
    }   
    
      
       string plain = get_string("plaintext: ");
       string k = argv[1];
       int key_len = strlen(k);
       
       printf("ciphertext: ");
       for (int i = 0, j = 0, result = 0, n = strlen(plain); i < n;  i++)
       { 
       char letter = plain[i]; // чистый текст переводим в тип данных char
       // перводим любые буквы, до 0 значения A - 0 B - 1
       
       int pi = plain[i] ; // отнимаем АСКИИ значения    
       char key = argv [1] [ (j) % key_len ] ; // ключ к следуюшему олфавитному символу
       int keys = shift(key) ; // переводим ключ через фукцыю, для удаления АСКИИ значени 
        if(islower (letter))// сохраняем регистр, добавляем ключ 
                 {
                     result = (letter+keys-97)%26+97;
                     j++;
                 }
       
              else if (isupper (letter))
                 {
                     result = (letter+keys-65)%26+65;
                     j++;
                 }
              else
                 {
                    result = letter;
                 }   
           
           
             
             
             
             printf("%c", result);
      
 
       }
    printf("\n");
    
   }
}    
    int shift(char c) // перводим любые буквы, до 0 значения A - 0 B - 1
    {   int k = 0;
        if(isupper(c))
        {
            k = c - 65;
        }
        else if(islower(c))
        {
            k = c - 97;
        }
        return  k;
    }    