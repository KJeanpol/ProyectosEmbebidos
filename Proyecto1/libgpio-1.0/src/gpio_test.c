#include<gpio.h>
#include<stdio.h> 

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

int	main(int argc, char const *argv[])
{
	int value = 1;

	pinMode(26, OUT);
	pinMode(19, IN);

	digitalWrite(26, HIGH);

	value = digitalRead(19);
	printf("Value pin 19: %d\n", value);

	blink(26, 1, 10);

	return 0;
}
