
#ifndef __gpio_h
#define __gpio_h

#include "../main.h"



void IRAM_ATTR gpioPinInit(uint8_t pin, const gpio_config_t *config);
void IRAM_ATTR gpioWrite(uint8_t pin, uint32_t level);
int IRAM_ATTR gpioRead(uint8_t pin);

#endif