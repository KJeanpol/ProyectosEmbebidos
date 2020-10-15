#ifndef _GPIO_H
#define _GPIO_H

int pinMode(int pin, int mode);
int digitalWrite(int pin, int value);
int digitalRead(int pin);
void blink(int pin, int freq, int duration);

#endif
