#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define NUMBER_MAX 3
#define DIRECTION_MAX 33
#define VALUE_MAX 29

int exportGPIO(int pin)
{
	char number[NUMBER_MAX];
	size_t bytes;
	int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) 
    {
        fprintf(stderr, "Unable to open /sys/class/gpio/export\n");
        exit(1);
    }

    bytes = snprintf(number, NUMBER_MAX, "%d", pin);

    write(fd, number, bytes);

    close(fd);

    return 0;
}

int unexportGPIO(int pin)
{
	char number[NUMBER_MAX];
	size_t bytes;
	int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) 
    {
        fprintf(stderr, "Unable to open /sys/class/gpio/unexport\n");
        exit(1);
    }

    bytes = snprintf(number, NUMBER_MAX, "%d", pin);

    write(fd, number, bytes);

    close(fd);

    return 0;
}

int pinMode(int pin, int mode)
{
	unexportGPIO(pin);
	exportGPIO(pin);

	const char in_str[] = "in";
	const char out_str[] = "out";

	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);

	fd = open(path, O_WRONLY);
	if (-1 == fd) 
	{
		fprintf(stderr, "Unable to open %s\n", path);
        exit(1);
	}

	if (-1 == write(fd, (mode == IN ? in_str : out_str), (mode == IN ? strlen(in_str) : strlen(out_str)))) 
	{	
        fprintf(stderr, "Error writing to %s\n", path);
        exit(1);
	}

	close(fd);

	return 0;
}

int digitalWrite(int pin, int value)
{
	const char low_value_str[] = "0";
	const char high_value_str[] = "1";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);

	fd = open(path, O_WRONLY);
	if (-1 == fd) 
	{
		fprintf(stderr, "Unable to open %s\n", path);
        exit(1);
	}

	if (1 != write(fd, (value == LOW ? low_value_str : high_value_str), 1)) 
	{
		fprintf(stderr, "Error writing to %s\n", path);
        exit(1);
	}

	close(fd);

	return 0;
}

int digitalRead(int pin)
{
	char path[VALUE_MAX];
	char value_str[2];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);

	fd = open(path, O_RDONLY);
	if (-1 == fd) 
	{
		fprintf(stderr, "Unable to open %s\n", path);
        exit(1);
	}

	if (-1 == read(fd, value_str, 2)) 
	{
		fprintf(stderr, "Error reading to %s\n", path);
        exit(1);
	}

	close(fd);

	return atoi(value_str);
}

void blink(int pin, int freq, int duration)
{
	float time_sleep = 2 / freq;

	for(int t = 0; t <= duration * freq; t++)
	{
		digitalWrite(pin, HIGH);
		sleep(time_sleep);
		digitalWrite(pin, LOW);
		sleep(time_sleep);
	}
}
