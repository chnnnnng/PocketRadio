#ifndef __ST7735_H__
#define __ST7735_H__

#include <stdio.h>
#include "memory.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#define ST7735_SDA            7 // SDA
#define ST7735_SCK            6 // SCL
#define ST7735_DC             10 // D/C
#define ST7735_RST            4  // rst
#define ST7735_CS             -1 // cs

#define DISPLAY_DIRECTION       3
#define DISPLAY_WIDTH           162
#define DISPLAY_HEIGHT          132

#define LCD_HOST    SPI2_HOST
#define PARALLEL_LINES 16

#define delay_ms(ms)\
        vTaskDelay(pdMS_TO_TICKS(ms))

#define gpio_set(pin)\
        gpio_set_level(pin, 1)

#define gpio_clear(pin)\
        gpio_set_level(pin, 0)

#define st7735_for_command()\
        command_0_data_1 = 0

#define st7735_for_data()\
        command_0_data_1 = 1


void st7735_init(void);
void st7735_reset(void);
void st7735_gpio_init(void);
void st7735_spi_init(void);
void st7735_lcd_init(void);
void st7735_write_byte(uint8_t byte);
void st7735_write_halfword(uint16_t halfword);
void st7735_write_word(uint32_t word);
void st7735_write_command(uint8_t command);
void st7735_write_data_8(uint8_t data8);
void st7735_write_data_16(uint16_t data16);
void st7735_write_data_32(uint32_t data32);
void st7735_write_data_buffer(uint8_t *data, size_t len);
void st7735_write_color_buffer(uint16_t *colorbuf, size_t len);
void st7735_set_window(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7735_clear(uint16_t color);
void st7735_point(uint16_t x, uint16_t y, uint16_t color);


#endif
