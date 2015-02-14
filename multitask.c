#include "multitask.h"

extern thread         threadCurrent, threads[NUM_OF_THREADS];
extern char threadDelay[NUM_OF_THREADS];
extern volatile short currentThread;
extern volatile char  threadLock;


unsigned short threadStartCounter = 0;
volatile unsigned int  miliseconds;

volatile char isADCbusy;


void threadInit(long tempaddr)
{
   threads[threadStartCounter].PCU = tempaddr >> 16;
   threads[threadStartCounter].PCH = (tempaddr & 0xFF00) >> 8;
   threads[threadStartCounter].PCL = tempaddr & 0xFF;
   threadStartCounter++;
}


void multitaskingInit(void)
{
   T0CON      = 0xC2;
   TMR0L      = 0x05;
   GIE_bit    = 1;
   TMR0IE_bit = 1;
}


unsigned int thread_ADC_Read(unsigned short channel)
{
   unsigned int ADCval;

   while (isADCbusy)
   {
   }
   isADCbusy = 1;
   ADCval    = ADC_read(channel);
   isADCbusy = 0;
   return ADCval;
}