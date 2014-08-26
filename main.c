/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>

int g;
long i;
bit a,b;

void start_stop(void)
{
  if(!a)
    {
       PORTC.5=1;       //turn on motor by s3 pressing.
       a=1;
    }
    else
    {
       PORTC.5=0;      //turn off motor by s3 pressing.
       a=0;
    }
}//start_stop.

void main(void)
{

// Port C initialization
// Func7=In Func6=Out Func5=Out Func4=In Func3=Out Func2=Out Func1=In Func0=In 
// State7=T State6=0 State5=0 State4=T State3=0 State2=1 State1=P State0=P 
PORTC=0x07;
DDRC=0x6C;

while (1)
      {
         if(PINC.0==0 && g!=2)    //initial mark up pinc.0 if s3 pressed.
         {
            g=1;
         }
         if(PINC.1==0 && g!=1 && a)    //initial mark up pinc.1 if s6 pressed.
         {
            g=2;
         }//if pin pushed.

         if(PINC.0==1 && g==1)   //implement key detection if s3 was released (start--stop motor key).
         {
            start_stop();
            g=0;
         }//if pin release.
         
         if(PINC.1==1 && g==2)   //implement key detection if s6 was released (change motor aim key).
         {
            b=PINC.2;
            PORTC.5=0;
            PORTC.2=0;
            PORTC.3=0;
            for(i=0;i<50000;i++);
            PORTC.2=~b;
            PORTC.3=b;
            PORTC.5=1;
            g=0;
         }//if pin release.
      }
}
