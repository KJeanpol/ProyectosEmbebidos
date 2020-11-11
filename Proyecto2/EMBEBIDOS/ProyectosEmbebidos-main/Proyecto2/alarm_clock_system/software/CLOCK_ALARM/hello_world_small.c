#include "sys/alt_stdio.h"
#include "system.h"
#include "priv/alt_legacy_irq.h"
#include "sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

volatile unsigned char *H_1 = (unsigned char *) 0x30d0;
volatile unsigned char *H_2 = (unsigned char *) 0x30c0;
volatile unsigned char *M_1 = (unsigned char *) 0x30b0;
volatile unsigned char *M_2 = (unsigned char *) 0x30a0;
volatile unsigned char *S_1 = (unsigned char *) 0x3090;
volatile unsigned char *S_2 = (unsigned char *) 0x3080;


//Timer
volatile unsigned char* STATUS;
volatile unsigned char* CONTROL;

//Set
volatile unsigned char* MASK;
volatile unsigned char* EDGE;
volatile unsigned char* SET;


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
void increment_time(void *context);
void increment_minutes();
void increment_hours();

void increment_time(void *context)
{
	 alt_putstr("CLOCK!");

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
	}
}


void init_time()
{
	*H_1 = 1;
	*H_2 = 2;
	*M_1 = 0;
	*M_2 = 0;
	*S_1 = 0;
	*S_2 = 0;
}

int main()
{
	alt_putstr("Alarm System!\n");
	init_time();
	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_IRQ, increment_time, NULL, 0x0);
	volatile int captureEdge;
	SET = (unsigned char*)0x30a0;
	MASK = (unsigned char*)0x30a8;
	EDGE = (unsigned char*)0x30ac;
	*CONTROL = 0x0007; //Sets the start, cont and ito bits to 1
	*MASK = 0xf;
	*EDGE = 0x0;
	/* Event loop never exits. */
	while (1);
	return 0;
}

