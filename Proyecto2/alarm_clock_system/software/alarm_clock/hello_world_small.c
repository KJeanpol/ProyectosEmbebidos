#include "sys/alt_stdio.h"

volatile unsigned char *H_1 = (unsigned char *) 0x30d0;
volatile unsigned char *H_2 = (unsigned char *) 0x30c0;
volatile unsigned char *M_1 = (unsigned char *) 0x30b0;
volatile unsigned char *M_2 = (unsigned char *) 0x30a0;
volatile unsigned char *S_1 = (unsigned char *) 0x3090;
volatile unsigned char *S_2 = (unsigned char *) 0x3080;

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
		*S_2++;
	//The seconds's least significant digit reached the limit
	//Time to increase seconds's most significant digit
	else
	{
		*S_2 = 0;
		if ((unsigned int)(*S_1) < 5)
			//Increases seconds's most significant digit
			*S_1++;
		else
		{
			*S_1 = 0;
			increment_minutes();
		}
	}
}

void increment_minutes()
{
	if ((unsigned int)(*M_2) < 9)
		//Increases minutes's least significant digit
		*M_2++;
	//The minutes's least significant digit reached the limit
	//Time to increase minutes's most significant digit
	else
	{
		*M_2 = 0;
		if ((unsigned int)(*M_1) < 5)
			//Increases minutes's most significant digit
			*M_1++;
		else
		{
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
			*H_2++;
		//The hours's least significant digit reached the limit
		//Time to increase hour's most significant digit
		else
		{
			*H_2 = 0;
			*H_1++;
		}
	}
	else
	{
		if ((unsigned int)(*H_2) < 3)
			//Increases hours's least significant digit
			*H_2++;
		//The hours's digits reached the limit
		else
		{
			*H_2 = 0;
			*H_1 = 0;
		}
	}
}