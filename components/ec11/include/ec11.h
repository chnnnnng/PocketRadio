#ifndef _Encoder_H_
#define _Encoder_H_
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "sdkconfig.h"

#define EC11_A 8 // Encoder channel 1 
#define EC11_B 9 // Encoder channel 2 
#define EC11_K 2 // Encoder key channel 

#define EC11_CHA_GPIO_INPUT_PIN_SEL ((1ULL<<EC11_A))
#define EC11_CHB_GPIO_INPUT_PIN_SEL ((1ULL<<EC11_B))
#define EC11_KEY_GPIO_INPUT_PIN_SEL ((1ULL<<EC11_K))

#define EC11_CW 1
#define EC11_CCW 2
#define EC11_KEY_DOWN 3

extern QueueHandle_t ec11_gpio_event_queue;
void ec11_init(void);
void ec11_task(void);
int ec11_get_new_moves();
bool ec11_get_press();
#endif
