/*
 By Liyanboy74
 https://github.com/liyanboy74
*/

#include <mega16.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "key.h"

void main(void)
{
//Buffer
int sel=0,ln1=0,ln2=0;
char ch,fu=0;
long int n1=0,n2=0;
float ans=0;
char buffer[32];

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// Characters/line: 16
lcd_init(16);

//Debug LCD
lcd_puts("Starting...");
delay_ms(1000);
lcd_clear();

while (1)
      {
      //Read Key
      ch=getkey();
       
      //Get Number 1
      if(ch>='0'&&ch<='9'&&sel==0)
       {
       if(ln1<8)
        {
        n1=(n1*10)+(ch-0x30);
        if(n1!=0)lcd_putchar(ch);
        ln1++;
        }
       }
        
      //Get Operator 
       else if((ch=='*'||ch=='/'||ch=='+'||ch=='-')&&sel==0)
       {
        fu=ch;
        lcd_putchar(fu);
        sel=1;
       }
        
       //Get Number 2   
       else if(ch>='0'&&ch<='9'&&sel==1)
       {
       if(ln2<8)
        {
        n2=(n2*10)+(ch-0x30);
        if(n2!=0)lcd_putchar(ch);
        ln2++;
        }
       } 
       
       //Clear Buffer
       else if(ch=='c')
       {
       lcd_clear();
       sel=0; 
       n1=0;
       ln1=0;
       n2=0;
       ln2=0;
       }
        
       //Calculate
       else if(ch=='='&&sel==1)
       { 
       lcd_putchar(ch);
       sel=2;
       switch(fu)
        {
        case'+':ans=n1+n2;          sprintf(buffer,"%.0f",ans);break;
        case'-':ans=n1-n2;          sprintf(buffer,"%.0f",ans);break;
        case'*':ans=n1*n2;          sprintf(buffer,"%.0f",ans);break;
        case'/':ans=n1/(float)n2;   sprintf(buffer,"%f",ans);break;
        }
        
       //Size Error
       if(fu=='*'&&(ln1+ln2)>10)
        {
        //Print Error
        lcd_gotoxy(0,1);
        lcd_puts("Size Error");
        delay_ms(1500);
         
        //Clear Buffer  
        lcd_clear();
        sel=0; 
        n1=0;
        ln1=0;
        n2=0;
        ln2=0;
        }
        
       //Print Result
       else 
       lcd_puts(buffer); 
       }
      }
}
