#include <cs50.h>
#include <stdio.h>
#include <math.h>

    
int main(void)
{  float f; 
 do
 {
     f = get_float("Change: ");
     
       
 }
 while ( f<=0  ); 
 
    
 
     int Totall = round(f* 100);
 
     int ostatokMOD = 0; 
     int ostatokCents = 0; 
     int Coins = 0; 
     int Num = 0;
     
     int result = 0;
     
     int e; int l;     
     
     
        if ( Totall>=25 )
        {
           ostatokMOD = Totall%25; 
           Num= Totall - ostatokMOD;
               
           Coins= Num/25;                                      
           Totall = Totall-( Coins*25); 
           result = result + Coins;
        }
        if (Totall>=10) 
        {
           ostatokMOD = Totall%10; 
           Num = Totall - ostatokMOD;
           Coins = Num/10;                             
           Totall =  Totall - ( Coins*10); 
           result=result+Coins;
        }                                 
     
       if (Totall>=5) 
        {
          ostatokMOD = Totall%5; 
           Num = Totall - ostatokMOD;
           Coins = Num/5;                           
           Totall =  Totall - ( Coins*5);  
           result=result+Coins;
        }
        if (Totall>=1) 
        {
           ostatokMOD = Totall%1; 
           Num = Totall - ostatokMOD;
           Coins = Num/1;                             
           Totall =  Totall - ( Coins*1);  
            result=result+Coins;
        }
 
  printf("%i\n", result);
 
}