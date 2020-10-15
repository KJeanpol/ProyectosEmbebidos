#include <stdio.h>
#include <stdlib.h>
#include <gpio.h>

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define MIN_ARGS 3

#define LIGHTS_NUM 5
#define DOORS_NUM  4

static const int lights[] = {26, 19, 13, 6, 5};
static const int doors[] = {22, 27, 17, 4};

void init_lights_pins();
void init_doors_pins();

int main(int argc, char const *argv[])
{
	if(atoi(argv[1]) != 0 && argc < MIN_ARGS)
	{
		printf("%s\n", "Error: you must write at least 2 arguments, function id an one element id.");
		exit(1);
	}
	
	//Function to perform
	switch (atoi(argv[1])) 
	{
		//Initialize system pins
		case 0:
			printf(" Initializing systems pins....\n");
			init_lights_pins();
			init_doors_pins();
			printf(" Done.\n");
			break;

		//Turn on lights
		case 1:
			for (int i = MIN_ARGS - 1; i < argc; i++)
			{
				printf(" Encender luz %i de la casa (gpio %i).\n", atoi(argv[i]), lights[atoi(argv[i]) - 1]);
				digitalWrite(lights[atoi(argv[i]) - 1], HIGH);
			}
			break;

		//Turn off lights
		case 2:
			for (int i = MIN_ARGS - 1; i < argc; i++)
			{
				printf(" Apagar luz %i de la casa (gpio %i).\n", atoi(argv[i]), lights[atoi(argv[i]) - 1]);
				digitalWrite(lights[atoi(argv[i]) -1 ], LOW);
			}
			break;

		//Read light status
		case 3:
			printf(" Leer estado de la luz %i : %i\n", atoi(argv[2]), digitalRead(lights[atoi(argv[2])]));
			return digitalRead(lights[atoi(argv[2])]);
			break;

		//Read door status
		case 3:
			printf(" Leer estado de la puerta %i : %i\n", atoi(argv[2]), digitalRead(doors[atoi(argv[2])]));
			return digitalRead(doors[atoi(argv[2])]);
			break;

		default:
			break;
	}

	return 0;
}

void init_lights_pins()
{
	for (int i = 0; i < LIGHTS_NUM; i++)
		pinMode(lights[i], OUT);
}

void init_doors_pins()
{
	for (int i = 0; i < DOORS_NUM; i++)
		pinMode(doors[i], IN);
}
