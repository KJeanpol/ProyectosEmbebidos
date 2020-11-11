#include "sys/alt_stdio.h"
#include <stddef.h>
#include <stdlib.h>

#ifndef NULL
#define NULL   ((void *) 0)
#endif


volatile unsigned char *H_1 = (unsigned char *) 0x30d0;
volatile unsigned char *H_2 = (unsigned char *) 0x30c0;
volatile unsigned char *M_1 = (unsigned char *) 0x30b0;
volatile unsigned char *M_2 = (unsigned char *) 0x30a0;
volatile unsigned char *S_1 = (unsigned char *) 0x3090;
volatile unsigned char *S_2 = (unsigned char *) 0x3080;




volatile unsigned char *SYS_CLK_TIMER_BASE = (unsigned char *)  0x3100;
volatile unsigned char *SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID = (unsigned char *) 0;
volatile unsigned char *SYS_CLK_TIMER_IRQ = (unsigned char *) 1;

unsigned int alarm_H_1;
unsigned int alarm_H_2;
unsigned int alarm_M_1;
unsigned int alarm_M_2;
unsigned int alarm_S_1;
unsigned int alarm_S_2;

void init_time();
void increment_time();
void increment_minutes();
void increment_hours();



static void HandlerTimerCoreInterrupt(void);
static void SetupTimerCore(void);

int main()
{ 
  alt_putstr("Alarm clock system\n");

  init_time();

  /* Event loop never exits. */
  while (1)
  {
	  increment_time();
  }

  return 0;
}

void init_time()
{
	*H_1 = 0;
	*H_2 = 0;
	*M_1 = 0;
	*M_2 = 0;
	*S_1 = 0;
	*S_2 = 0;
}

void increment_time()
{
	if ((unsigned int)(*S_2) < 9)
		//Increases seconds's least significant digit
		*S_2 = *S_2 + 1;
	//The seconds's least significant digit reached the limit
	//Time to increase seconds's most significant digit
	else
	{
		if ((unsigned int)(*S_1) < 5)
		{
			//Increases seconds's most significant digit
			*S_1 = *S_1 + 1;
			*S_2 = 0;
		}
		else
		{
			*S_2 = 0;
			*S_1 = 0;
			increment_minutes();
		}
	}
}

void increment_minutes()
{
	if ((unsigned int)(*M_2) < 9)
		//Increases minutes's least significant digit
		*M_2 = *M_2 + 1;
	//The minutes's least significant digit reached the limit
	//Time to increase minutes's most significant digit
	else
	{
		if ((unsigned int)(*M_1) < 5)
		{
			//Increases minutes's most significant digit
			*M_1 = *M_1 + 1;
			*M_2 = 0;
		}
		else
		{
			*M_2 = 0;
			*M_1 = 0;
			increment_hours();
		}
	}
}

void increment_hours()
{
	if ((unsigned int)(*H_1) < 2)
	{
		if ((unsigned int)(*H_2) < 9)
			//Increases hours's least significant digit
			*H_2 = *H_2 + 1;
		//The hours's least significant digit reached the limit
		//Time to increase hour's most significant digit
		else
		{
			*H_1 = *H_1 + 1;
			*H_2 = 0;
		}
	}
	else
	{
		if ((unsigned int)(*H_2) < 3)
			//Increases hours's least significant digit
			*H_2 = *H_2 + 1;
		//The hours's digits reached the limit
		else
		{
			*H_2 = 0;
			*H_1 = 0;
		}
		SetupTimerCore();
	}
}



static void HandlerTimerCoreInterrupt(void) {
   //*timerCoreStatus = 0; // Resets the status
}


static void SetupTimerCore(void) {

   unsigned char *timerCoreControl = (unsigned char *) (SYS_CLK_TIMER_BASE + 0x4);
   unsigned char *timerCoreMask = (unsigned char *) (SYS_CLK_TIMER_BASE + 0x8);
   unsigned char *timerCoreEdgeCap = (unsigned char *) (SYS_CLK_TIMER_BASE + 0xC);

   alt_ic_isr_register(SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID,
   SYS_CLK_TIMER_IRQ, HandlerTimerCoreInterrupt, NULL, 0x0);

   *timerCoreMask = 0x0;
   *timerCoreEdgeCap = 0x4;
   *timerCoreControl = 0x0007;
  // *timerCoreStatus = 0;

}
