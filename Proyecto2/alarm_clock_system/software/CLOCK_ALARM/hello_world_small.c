#include "sys/alt_stdio.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include <stddef.h>
#include <stdlib.h>
#include <system.h>

#define INC_SEC		      0x1
#define	INC_MIN		      0x2
#define INC_HOUR		  0x3
#define SET_TIME_MODE     0x4
#define SET_ALARM_MODE    0x5
#define TIMER_MODE        0x6

#define MIN_IN_SECS        60
#define HOUR_IN_SECS     3600
#define DAY_IN_SECS     86400

volatile unsigned char *H_1 = (unsigned char *) H_1_BASE;
volatile unsigned char *H_2 = (unsigned char *) H_2_BASE;
volatile unsigned char *M_1 = (unsigned char *) M_1_BASE;
volatile unsigned char *M_2 = (unsigned char *) M_2_BASE;
volatile unsigned char *S_1 = (unsigned char *) S_1_BASE;
volatile unsigned char *S_2 = (unsigned char *) S_2_BASE;

volatile unsigned char *SET      = (unsigned char *)(SET_BASE);
volatile unsigned char *SET_MASK = (unsigned char *)(SET_BASE + 8);
volatile unsigned char *SET_EDGE = (unsigned char *)(SET_BASE + 12);

volatile unsigned char *TIMER         = (unsigned char *)(TIMER_BASE);
volatile unsigned char *TIMER_CONTROL = (unsigned char *)(TIMER_BASE + 4);

volatile unsigned int time_counter = 0;
volatile unsigned int time_alarm   = 0;

volatile unsigned int mode = 0;


void assign_time(void)
{
	*(S_2) = ((time_counter)         % 10);
	*(S_1) = ((time_counter / 10)    %  6);
	*(M_2) = ((time_counter / 60)    % 10);
	*(M_1) = ((time_counter / 600)   %  6);
	*(H_2) = ((time_counter / 3600)  % 10);
	*(H_1) = ((time_counter / 36000) %  3);
}


void interrupt_handler(void *context)
{
	alt_putstr("Button interrupt...\n");

	//Sets the execution mode based on the input register value
	switch (*(SET))
	{
		case SET_TIME_MODE:
			alt_putstr("Set time mode: ON.\n");
        	mode = SET_TIME_MODE;
        	break;

		case SET_ALARM_MODE:
		    alt_putstr("Set alarm mode: ON.\n");
		    mode = SET_ALARM_MODE;
        	break;

		case TIMER_MODE:
		    alt_putstr("Set mode: OFF.\n Timer mode: ON.\n");
		    mode = TIMER_MODE;
        	break;

        default:
        	break;
	}
//
	if (mode == SET_TIME_MODE)
	{
		switch (*(SET))
		{
			case INC_SEC:
				time_counter += 1;
   				alt_putstr("Time increase: 1 sec.\n");
   				break;

			case INC_MIN:
				time_counter += MIN_IN_SECS;
	   			alt_putstr("Time increase: 1 min.\n");
   				break;

 			case INC_HOUR:
				time_counter += HOUR_IN_SECS;
	   			alt_putstr("Time increase: 1 hour.\n");
   				break;

   			default:
   				break;
		}
		//Assigns the time's value to the output registers
		assign_time();
	}
//
	else if (mode == SET_ALARM_MODE)
	{
		switch (*(SET))
		{
			case INC_SEC:
				time_alarm += 1;
		  		alt_putstr("Alarm increase: 1 sec.\n");
   				break;

			case INC_MIN:
				time_alarm += MIN_IN_SECS;
		  		alt_putstr("Alarm increase: 1 min.\n");
   				break;

 			case INC_HOUR:
				time_alarm += HOUR_IN_SECS;
		  		alt_putstr("Alarm increase: 1 hour.\n");
   				break;

   			default:
   				break;
		}
	}

    //Resets the interrupt
    *SET_EDGE = 0x00;
}


void increment_time(void *context)
{
	 //If we are not in set time or alarm mode
	if (mode == TIMER_MODE)
	{
		alt_putstr("Tic tac...\n");
		time_counter++;
	}

	//If the time counter reaches a day in seconds
	if (time_counter > DAY_IN_SECS)
		time_counter = 0;

	//Assigns the time's value to the output registers
	assign_time();

	//If the timer counter reaches the alarm time
	if (time_counter == time_alarm)
		alt_putstr("Beep Beep! Beep Beep!\n");
    //Resets the interrupt
	*(TIMER) = 0x00;

}


void system_set_up(void)
{
	alt_putstr("Initializing system ...\n");

	*(SET_MASK) = 0x07; //Writes to IRQ mask
	*(SET_EDGE) = 0x00; //Clears the interrupt

	//Registers the input interrupt
	alt_ic_isr_register(SET_IRQ_INTERRUPT_CONTROLLER_ID,
						SET_IRQ,
						interrupt_handler,
						0,
						0x0);

	//Registers the timer interrupt
	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID,
						TIMER_IRQ,
						increment_time,
						0,
						0x0);

	//Enables the interrupt and starts the timers
	*(TIMER_CONTROL) = 0x07;

	//Sets current mode as a timer
	mode = TIMER_MODE;

	alt_putstr("Done.\n");
}

int main()
{ 
	alt_putstr("Alarm Clock System!\n");

	system_set_up();

	/* Event loop never exits. */
	while (1);

	return 0;
}
