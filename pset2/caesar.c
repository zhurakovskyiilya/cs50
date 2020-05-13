#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



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
          if ( isalpha (argv[1] [i]))
          {
              printf("Usage key %s\n",argv[0]);
              return 1;
          }

    }
      int key = atoi(argv[1]);
      if ( key > 0)
      {
          string s = get_string("plaintext: ");
          printf("ciphertext: ");
          for (int j = 0; j < strlen(s); j++)
              {
              if(islower(s[j]))
                 {
                     printf("%c",(((s[j]+key)-97)%26)+97);
                 }

              else if (isupper(s[j]))
                 {
                     printf("%c",(((s[j]+key)-65)%26)+65);
                 }
              else
                 {
                     printf("%c", s[j]);
                 }
              }

          printf("\n");
      }
 }
}