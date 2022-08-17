/* spi_master example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_log.h"
#include "driver/adc.h"

#include "power.h"
#include "ui.h"
#include "ui_helpers.h"
#include "fm.h"
#include "st7735.h"
#include "ec11.h"
#include "time.h"
#include "network.h"

static const char *TAG = "PocketRadio";

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    size_t w = area->x2 - area->x1 + 1;
    size_t h = area->y2 - area->y1 + 1;
    st7735_set_window(area->x1,area->y1,w,h);
    st7735_write_color_buffer((uint16_t*)color_p, w*h);

    lv_disp_flush_ready(disp_drv);
}

void my_monitor_cb(lv_disp_drv_t * disp_drv, uint32_t time, uint32_t px)
{
  //printf("%d px refreshed in %d ms\n", px, time);
}

void encoder_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
    data->enc_diff = ec11_get_new_moves();
    //printf("%d\n",data->enc_diff);

    if(ec11_get_press()) data->state = LV_INDEV_STATE_PRESSED;
    else data->state = LV_INDEV_STATE_RELEASED;
}

void vApplicationTickHook(void)
{
    lv_tick_inc(10);
}


void ui_task()
{
    for(;;){
        lv_timer_handler();
        vTaskDelay(15/portTICK_PERIOD_MS);
    }
}


void ui_lvgl_init()
{
    lv_init();

    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;
    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[DISPLAY_WIDTH * 100];
    static lv_color_t buf_2[DISPLAY_WIDTH * 100];
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISPLAY_WIDTH*100);

    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
    disp_drv.monitor_cb = my_monitor_cb;
    disp_drv.hor_res = DISPLAY_WIDTH;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = DISPLAY_HEIGHT;                 /*Set the vertical resolution in pixels*/

    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    /*Register the driver in LVGL and save the created input device object*/
    my_indev = lv_indev_drv_register(&indev_drv);

}



void test_task(){
    while (1)
    {
        printf("hello\n");
        delay_ms(2000);

    }
    
}

bool ec11_change_callback(char val)//编码器事件处理，返回event_stop,若为true，禁止事件向下传递
{
    switch (val)
    {
        case EC11_CW:
            break;
        case EC11_CCW:
            break;
        case EC11_KEY_DOWN:
            break;
        default:
            break;
    }

    if(sleep_mode == true){//在睡眠模式有任何操作
        power_exit_sleep_mode();//就退出睡眠模式
        return true;//禁止事件向下传递
    }else{//在非睡眠模式有任何操作
        power_refresh_sleep_mode_timer();//重置“进入睡眠模式”计时器
        return false;//允许事件向下传递
    }
}

void time_task(void)
{
    time_t now;
    char strftime_buf[64];
    struct tm timeinfo;

    for(;;){
        time(&now);
        // Set timezone to China Standard Time
        setenv("TZ", "CST-8", 1);
        tzset();

        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
        ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);

        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    power_init();       //初始化电源模块

    power_display(1);   //启动显示模块电源
    st7735_init();      //初始化屏幕底层驱动
    ui_lvgl_init();     //初始化LVGL
    ui_init();          //初始化绘制UI

    power_radio(1);     //启动收音机模块电源
    fm_init();          //初始化调频收音机模块
    
    ec11_init();        //初始化编码器

    network_init();

    xTaskCreate(ui_task, "main_task", 4096, NULL, 3, NULL);   //启动主线程（UI线程) 
    //fm_search_channels();
    //xTaskCreate(test_task, "test_task", 4096, NULL, 6, NULL); 
    xTaskCreate(ec11_task, "ec11_task", 4096, NULL, 2, NULL); 
    xTaskCreate(power_task, "power_task", 4096, NULL, 4, NULL);
    xTaskCreate(time_task, "time_task", 4096, NULL, 4, NULL);
}
