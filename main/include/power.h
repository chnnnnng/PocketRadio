#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/adc.h"

#include "esp_log.h"
#include "esp_err.h"
#include "esp_adc_cal.h"
#include "esp_sleep.h"

#include "ui.h"
#include "st7735.h"
#include "ec11.h"

#define POWER_RADIO_IO 0
#define POWER_DISPLAY_IO 1

#define POWER_BATTERY_ADC ADC1_CHANNEL_3
#define POWER_CHARGING_IO 5

extern bool battery_low;
extern bool sleep_mode;
extern uint32_t sleep_mode_time;

void power_init();
void power_radio(bool onoff);
void power_display(bool onoff);

void power_enter_low_power_mode();
void power_exit_low_power_mode();
void power_enter_sleep_mode();
void power_refresh_sleep_mode_timer();
void power_exit_sleep_mode();
void power_off();
uint32_t power_voltage(void);
void power_task(void);