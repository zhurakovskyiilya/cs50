#include <cs50.h>
#include <stdio.h>

int main(void)
{int h;

 
  do
  {
      h = get_int(" Height: ");
  }
  while (h > 8 || h < 1);
  for ( int line = 0; line < h; line++ )
  {
     
      
      for(int dot = 1; dot < h-line; dot++)
      
      {
          printf(" ");
      }
      
      for (int hash = 0; hash < line + 1 ; hash++)  
      {  
          printf("#"); 
      }
      
       for ( int space = 0 ; space < 2; space ++)
       {
            printf(" "); 
       }
    
      for (int hash = 0; hash < line + 1 ; hash++)  
      {  
          printf("#"); 
      }
      printf("\n");
    }

}