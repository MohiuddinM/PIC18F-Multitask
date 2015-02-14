#define NUM_OF_THREADS    4

#define LOCK()                   threadLock = 1
#define UNLOCK()                 threadLock = 0
#define isLOCKED                   threadLock
#define startThread()            __asm RETFIE 0
#define continueSameThread()     __asm RETFIE 1

#define thread_delay_ms(msec)    threadDelay[currentThread] = msec;   \
                                 while(threadDelay[currentThread])

#define ON        1
#define OFF       0
extern unsigned int  miliseconds;

typedef struct
{
   unsigned short PCU, PCH, PCL;
   unsigned short STATUS, PCLATH, BSR;
   //unsigned int   delay;      //this way of delay is too slow
} thread;

void multitaskingInit(void);
void threadInit(long);
unsigned int thread_ADC_Read(unsigned short);