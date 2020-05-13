#include <cs50.h>
#include <stdio.h>

int main(void)
{ long l;
  long num;
  long roz;
 do
 {
      l = get_long("Number: ");
 }
 while ( l <=0 );
 long visa = 400000000000000;
 long amex = 340000000000000;
 long mastercard = 5100000000000000;

 int finish = 0;
 num = 0;
 roz = 0;
 long mnojeniya = 0;                  int desatki = 0;         int tusachidwa = 0;  int stotusachmilionov = 0;   int kvadrilliondwa = 0;
                                      int desatkidwa = 0;      int stotusach  = 0;  int stotusachmilionovdwa = 0;
 long negative = 0;
 long totall = 0;                      int tusachi = 0;         int stotusachdwa = 0;int desattrilionow = 0;
                                      int desatmilionov = 0;   int meliard = 0;     int desattrilionowdwa = 0;
                                      int desatmilionovdwa = 0;int meliarddwa = 0;  int kvadrillion = 0;
 if ( l >= visa || l < 5500000000000000)
 {
    long one  = l/10%10;
    mnojeniya = one*2;
    if ( mnojeniya >= 10)
    {
        desatki = mnojeniya%10;
        desatkidwa = mnojeniya/10;
    }
     else
     {
          desatkidwa =  mnojeniya;
     }
 }
     roz= roz + (desatki + desatkidwa);

  long two  = l/1000%10;
  mnojeniya = two*2;
    if ( mnojeniya >= 10)
    {
        tusachi = mnojeniya%10;
        tusachidwa = mnojeniya/10;
    }
   else
     {
         tusachidwa =  mnojeniya;
     }

     roz= roz + (tusachi+tusachidwa);


  long thre = l/100000%10;
   mnojeniya = thre*2;
    if ( mnojeniya >= 10)
    {
       stotusach = mnojeniya%10;
       stotusachdwa = mnojeniya/10;
    }
  else
     {
         stotusachdwa =  mnojeniya;
     }


     roz= roz + ( stotusach+stotusachdwa);


long four = l/10000000%10;
mnojeniya = four*2;
 if ( mnojeniya >= 10)
    {
       desatmilionov= mnojeniya%10;
       desatmilionovdwa = mnojeniya/10;
    }
  else
     {
        desatmilionovdwa =  mnojeniya;
     }


     roz= roz + ( desatmilionov+desatmilionovdwa);


 long five = l/1000000000%10;
 mnojeniya = five*2;
  if ( mnojeniya >= 10)
    {
       meliard= mnojeniya%10;
       meliarddwa = mnojeniya/10;
    }
  else
     {
         meliarddwa =  mnojeniya;
     }


     roz= roz + ( meliarddwa + meliard);



 long six  = l/100000000000%10;
 mnojeniya = six*2;
 if ( mnojeniya >= 10)
    {
       stotusachmilionov = mnojeniya%10;
       stotusachmilionovdwa = mnojeniya/10;
    }
  else
     {
        stotusachmilionovdwa =  mnojeniya;
     }


     roz= roz + ( stotusachmilionov  + stotusachmilionovdwa);


 long seven= l/10000000000000%10;
 mnojeniya = seven*2;
 if ( mnojeniya >= 10)
    {
       desattrilionow = mnojeniya%10;
       desattrilionowdwa = mnojeniya/10;
    }
  else
     {
       desattrilionowdwa =  mnojeniya;
     }


     roz= roz + ( desattrilionow  + desattrilionowdwa);

long eight= l/1000000000000000%10;
 mnojeniya = eight*2;
 if ( mnojeniya >= 10)
    {
       kvadrillion= mnojeniya%10;
       kvadrilliondwa = mnojeniya/10;
    }
  else
     {
       kvadrilliondwa =  mnojeniya;
     }


     roz= roz + ( kvadrillion + kvadrilliondwa);

   long negtiveone = l%10;
   long negativesothni = l/100%10;
   long negativedesattus =l/10000%10;
   long negativemilion =  l/1000000%10;
   long negativestomilionov =l/100000000%10;
   long negativedesatmiliardov=l/10000000000%10;
   long negativetrilion =      l/1000000000000%10;
   long negativekvadrilion =   l/100000000000000%10;
   negative = negative+(negtiveone+negativesothni+negativedesattus+negativemilion+negativestomilionov+negativedesatmiliardov+negativetrilion+negativekvadrilion);
 totall = totall + ( negative + roz);
  finish = totall%10;
 if ( totall % 10 == 0)
 {
     if ( (l < 350000000000000 && l > 340000000000000) || (l < 3800000000000000 && l > 370000000000000 ) )
 {
      printf("AMEX\n");
 }


 else if ( l < 5600000000000000 && l > 5100000000000000 )
 {
    printf("MASTERCARD\n");
 }


else if ( (l < 5000000000000 && l > 4000000000000) ||  (l > 400000000000000 && l < 5000000000000000) )

 {
       printf("VISA\n");
 }
  else

   {
       printf("INVALID\n");
   }

 }
 else
 {
     printf("INVALID\n");
 }

}