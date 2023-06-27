#include "timer.h"


 hal_timer_t IRAM_ATTR stepTimer;


void timerInit(hal_timer_t *timer, bool alarm_en) {

    timer_hal_init(&timer->hal, timer->group, timer->idx);

    timer_hal_reset_periph(&timer->hal);

    timer_ll_set_divider((timer->hal).dev, (timer->hal).idx, fTimers / timer->timerCount);
    timer_ll_set_counter_increase((timer->hal).dev, (timer->hal).idx, true);
    timer_ll_intr_disable((timer->hal).dev, (timer->hal).idx);
    timer_ll_clear_intr_status((timer->hal).dev, (timer->hal).idx);
    timer_ll_set_alarm_enable((timer->hal).dev, (timer->hal).idx, alarm_en);
    timer_ll_set_auto_reload((timer->hal).dev, (timer->hal).idx, true);         // 使能自动重装载值
    timer_ll_set_counter_enable((timer->hal).dev, (timer->hal).idx, false);
    timer_ll_set_counter_value((timer->hal).dev, (timer->hal).idx, 0);
} 

void timerStart(hal_timer_t *timer, uint64_t alarm_value) {

    timer_ll_set_alarm_value((timer->hal).dev, (timer->hal).idx, alarm_value);
    timer_ll_set_alarm_enable((timer->hal).dev, (timer->hal).idx, true);
    timer_ll_set_counter_enable((timer->hal).dev, (timer->hal).idx, true);
}

void timerStop(hal_timer_t *timer) {
    timer_ll_set_counter_enable((timer->hal).dev, (timer->hal).idx, false);
    timer_ll_set_alarm_enable(timer->hal.dev, timer->hal.idx, false);
}

void timerIntrInit(hal_timer_t *timer, intr_handler_t handler) {

    esp_intr_alloc_intrstatus(timer_group_periph_signals.groups[timer->group].t0_irq_id,
                              ESP_INTR_FLAG_IRAM,
                              (uint32_t)timer_hal_get_intr_status_reg(&timer->hal),
                              1 << timer->idx,
                              handler,
                              NULL,
                              NULL);
}

void timerClearIntrStatus(hal_timer_t *timer) {

    timer_hal_clear_intr_status(&timer->hal);
}

void timerAlarmEnable(hal_timer_t *timer) {

    timer_hal_set_alarm_enable(&timer->hal, true);
}

void timerAlarmSetVal(hal_timer_t *timer, uint64_t tick) {

    timer_hal_set_alarm_value(&timer->hal, (uint64_t)tick);
}
