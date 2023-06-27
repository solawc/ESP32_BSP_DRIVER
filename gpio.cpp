#include "gpio.h"
#include <driver/gpio.h>


/************************************************
 * 注:
 * 当前文件是对ESP32 GPIO的控制做二次封装，抛弃原
 * 先Arduino的接口，提升可以很好提升GPIO的执行效率
 ************************************************/

void IRAM_ATTR gpioPinInit(uint8_t pin, const gpio_config_t *config) {
    gpio_reset_pin((gpio_num_t)pin);
    gpio_config(config);
}

void IRAM_ATTR gpioWrite(uint8_t pin, uint32_t level) {
    gpio_set_level((gpio_num_t) pin, level);
}

int IRAM_ATTR gpioRead(uint8_t pin) {
   return gpio_get_level((gpio_num_t)pin);
}

/*
 * example:
void IRAM_ATTR gpio_isr_handler(void *arg) {
    uint32_t gpio_num = (uint32_t)arg;
    // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}   

*/

void gpioIsrInit(uint8_t pin, gpio_isr_t isr_handler) {
    gpio_install_isr_service(0);
    gpio_isr_handler_add((gpio_num_t)pin, isr_handler, (void* )pin);
}

