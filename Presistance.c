#include "multitask.h"

sbit LED1 at RD0_bit;
sbit LED2 at RD1_bit;
sbit LED3 at RD2_bit;
sbit LED4 at RD3_bit;

thread threads[NUM_OF_THREADS];
unsigned short  threadDelay[NUM_OF_THREADS] = {0};
const unsigned short DEC_LOOP_COUNT = NUM_OF_THREADS - 1;
unsigned short  currentThread = 0, threadLock = 0, i;

void idleThread(void);
void thread1(void);
void thread2(void);
void thread3(void);

void Interrupt()
{
    if (TMR0IF_bit)      // TODO: tick = 5ms
    {
        LED4       = ~LED4;
        TMR0IF_bit = 0;
        TMR0L      = 0x05;


        miliseconds++;
        for (i = DEC_LOOP_COUNT; i; i--)             //decrementing loop is faster,
        {
           --threadDelay[i];
        }
        if (isLOCKED)
        {
           continueSameThread();
        }

        threads[currentThread].PCU    = TOSU;
        threads[currentThread].PCH    = TOSH;
        threads[currentThread].PCL    = TOSL;
        threads[currentThread].STATUS = STATUS;
        threads[currentThread].BSR    = BSR;

        for (i = DEC_LOOP_COUNT, currentThread++; i; i--)
        {
              if(threadDelay[currentThread]) currentThread++;
              else break;
              if(currentThread > (NUM_OF_THREADS - 1)) currentThread = 1;
        }
        if(threadDelay[currentThread])
        {
           currentThread = 0;
        }

        TOSU   = threads[currentThread].PCU;
        TOSH   = threads[currentThread].PCH;
        TOSL   = threads[currentThread].PCL;
        STATUS = threads[currentThread].STATUS;
        BSR    = threads[currentThread].BSR;

        startThread();
    }
}

void idleThread(void)
{
    while(1)
    {
    }
}
void thread1(void)
{
    while (1)
    {
       LED1 = ~LED1;
       thread_delay_ms(10);
    }
}
void thread2(void)
{
    while (1)
    {
       LED2  = ~LED2;
       thread_delay_ms(20);
    }
}
void thread3(void)
{
    while (1)
    {
       LED3    = ~LED3;
       thread_delay_ms(50);
       thread_ADC_Read(0);
    }
}
void main()
{
    // Init Idle thread
    threadInit(&idleThread);
   
    TRISD = 0x00;
    PORTD = 0x00;
    
    // initializing the user threads
    threadInit(&thread1);
    threadInit(&thread2);
    threadInit(&thread3);


    multitaskingInit();
    
    //Won't run here, listed just to prevent getting optimized out
    idleThread();
    thread1();
    thread2();
    thread3();
}