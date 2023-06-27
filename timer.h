#ifndef __timer_h
#define __timer_h

#include "../main.h"

#include "hal/timer_hal.h"
#include "esp_intr_alloc.h"

typedef struct {

    timer_hal_context_t hal;
    timer_group_t group;
    timer_idx_t idx;
    uint32_t timerCount;

    bool (*timer_isr_callback)(void);

}hal_timer_t;
extern hal_timer_t stepTimer;


void timerInit(hal_timer_t *timer, bool alarm_en);
void timerStart(hal_timer_t *timer, uint64_t alarm_value);
void timerStop(hal_timer_t *timer);
void timerIntrInit(hal_timer_t *timer, intr_handler_t handler);
void timerClearIntrStatus(hal_timer_t *timer);
void timerAlarmEnable(hal_timer_t *timer);
void timerAlarmSetVal(hal_timer_t *timer, uint64_t tick);
#endif