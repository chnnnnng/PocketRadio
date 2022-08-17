#ifndef __TEA5767_H__
#define __TEA5767_H__


#include <stdio.h>
#include "memory.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "gpio_struct.h"

#include "driver/i2c.h"

#define I2C_PORT        I2C_NUM_0
#define ACK_CHECK_EN    0
#define TEA5767_ADDR_W  0b11000000
#define TEA5767_ADDR_R  0b11000001
#define I2C_MASTER_FREQ_HZ          400000
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000


#define GET_PREPLL_FROM_PLL(pll) ((pll & 0x3f00) >> 8)

#define GET_POSTPLL_FROM_PLL(pll) ( pll & 0xFF )

typedef struct {
    uint8_t isMute                  : 1; // 静音 = TRUE，正常 = FALSE
    uint8_t isSearchMode            : 1; // 搜索模式 = TRUE，放音模式 = FALSE
    uint8_t  prePLL                  : 6; // 频率PLL值的前6bits
    uint8_t  postPLL                 : 8; // 频率PLL值的后8bits
    uint8_t  searchDirection         : 1; // 向前搜索 = 0，向后搜索 = 1
    uint8_t  stopSearchLevel         : 2; // 搜索模式不自动停止 = 0，搜索到微弱信号（信号强度ADC输出5）时中断搜索 = 1，搜索到中等信号（信号强度ADC输出7）时中断搜索 = 2，搜索到强烈信号（信号强度ADC输出10）时中断搜索 = 3
    uint8_t  sideBand                : 1; // 上边带接收 = 1，下边带接收 = 0
    uint8_t isMono                  : 1; // 强制单声道输出 = TRUE，立体声输出 = FALSE
    uint8_t isMuteLeft              : 1; // 立体声合成到右声道 = TRUE，正常声道输出 = FALSE
    uint8_t isMuteRight             : 1; // 立体声合成到左声道 = TRUE，正常声道输出 = FALSE
    uint8_t  softwarePort1Output     : 1; // SWP1作为可编程端口使用，SWP1口输出高电平 = 1，SWP1口输出低电平 = 0
    uint8_t  softwarePort2Output     : 1; // SWP2作为可编程端口使用，SWP2口输出高电平 = 1，SWP2口输出低电平=0
    uint8_t isStandby               : 1; // 待机模式 = TRUE，工作模式 = FALSE
    uint8_t  bandLimit               : 1; // 日本调频制式 = 1，欧美调频制式 = 0
    uint8_t  xtal                    : 1; // 使用外置13MHz晶振 = 1，使用外置32.768kHz晶振 = 0
    uint8_t isSoftwareMute          : 1; // 开启软件静音 = TRUE，关闭软件静音 = FALSE
    uint8_t isHighCutControl        : 1; // 开启高频旁路 = TRUE，关闭高频旁路 = FALSE
    uint8_t isStereoNoiseCanceling  : 1; // 开启立体声噪音消除 = TRUE，关闭立体声噪音消除 = FALSE
    uint8_t isEnableSearchIndicator : 1; // 搜索到频道是SWP1输出高电平 = TRUE，SWP1作为可编程端口使用 = FALSE
    uint8_t isEnablePLLReference    : 1; // 启动6.5MHz锁相环参考频率 = TRUE，关闭6.5MHz锁相环参考频率 = FALSE
    uint8_t  DTC                     : 1; // 美国制去加重时间75μs = 1，其他国家去加重时间 50μs = 0
    uint8_t  NC                      : 6; // not used; position is don’t care
} tea5767_write_buffer_t;


typedef struct {
    bool isReady               : 1; // 已搜索到频道或搜索到波段边界 = TRUE，否则 = FALSE
    bool isBandLimit           : 1; // 已搜索到波段边界 = TRUE，否则 = FALSE
    int  prePLL                : 6; // 当前频率的PLL值的前6bits
    int  postPLL               : 8; // 当前频率的PLL值的后8bits
    bool isStereo              : 1; // 当前信号为立体声 = TRUE，否则 = FALSE
    int  intermediateFrequency : 7; // 当前中频，正确调谐时在0x31~0x3E之间
    int  RFADClevel            : 4; // ADC输出的RF信号等级
    int  chipID                : 4; // 芯片ID
    int  rsv                   : 8; // reserved for future extensions
} tea5767_read_buffer_t;

typedef struct
{
    uint8_t pllh;
    uint8_t plll;
    uint8_t level;
    uint8_t ifc;
    bool stereo;
} tea5767_channel_t;


void tea5767_i2c_init(gpio_num_t SDA, gpio_num_t SCL);

void tea5767_i2c_write(tea5767_write_buffer_t * buf);

void tea5767_i2c_read(tea5767_read_buffer_t * buf);

void tea5767_write_buffer_default(tea5767_write_buffer_t * buf);

float tea5767_pll_to_freq(uint16_t pll);
uint16_t tea5767_freq_to_pll(float freq);

#endif
