#pragma once

#include <stdio.h>
#include "memory.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tea5767.h"
#include "ui.h"

#define FM_SDA GPIO_NUM_21
#define FM_SCL GPIO_NUM_20

#define MAX_SAVED_CHANNELS 50
#define FM_LEVEL_THRES 13



#define delay_ms(ms)\
        vTaskDelay(pdMS_TO_TICKS(ms))

void fm_set_channel_freq(float freq, bool isMute);

void fm_set_channel(tea5767_channel_t *channel, bool isMute);

float fm_current_channel(tea5767_channel_t * ch);

void fm_search_channels();

void fm_init();

void fm_on_channel_change_handler(int channel);

//TODO: 公用资源（setchannel\currentchannel）加入信号量