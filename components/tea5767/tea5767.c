#include "tea5767.h"

void tea5767_i2c_init(gpio_num_t SDA, gpio_num_t SCL)
{
    int i2c_master_port = I2C_PORT;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA,
        .scl_io_num = SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);

}


void tea5767_i2c_write(tea5767_write_buffer_t * buf)
{

    uint8_t t[5] = {0x00,0x00,0x00,0x00,0x00};
    t[0] |= buf->isMute << 7;
    t[0] |= buf->isSearchMode << 6;
    t[0] |= buf->prePLL;
    t[1] |= buf->postPLL;
    t[2] |= buf->searchDirection << 7;
    t[2] |= buf->stopSearchLevel << 5;
    t[2] |= buf->sideBand << 4;
    t[2] |= buf->isMono << 3;
    t[2] |= buf->isMuteLeft << 2;
    t[2] |= buf->isMuteRight << 1;
    t[2] |= buf->softwarePort1Output;
    t[3] |= buf->softwarePort2Output << 7;
    t[3] |= buf->isStandby << 6;
    t[3] |= buf->bandLimit << 5;
    t[3] |= buf->xtal << 4;
    t[3] |= buf->isSoftwareMute << 3;
    t[3] |= buf->isHighCutControl << 2;
    t[3] |= buf->isStereoNoiseCanceling << 1;
    t[3] |= buf->isEnableSearchIndicator;
    t[4] |= buf->isEnablePLLReference << 7;
    t[4] |= buf->DTC << 6;
    t[4] |= buf->NC;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, TEA5767_ADDR_W, ACK_CHECK_EN);
    i2c_master_write(cmd, &t, sizeof(tea5767_write_buffer_t), ACK_CHECK_EN);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void tea5767_i2c_read(tea5767_read_buffer_t * buf)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, TEA5767_ADDR_R, ACK_CHECK_EN);
    
    uint8_t t[5]= {0x00,0x00,0x00,0x00,0x00};
    i2c_master_read(cmd, &t, sizeof(tea5767_read_buffer_t), I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    buf->isReady = t[0] >> 7;
    buf->isBandLimit = t[0] >> 6;
    buf->prePLL = t[0];
    buf->postPLL = t[1];
    buf->isStereo = t[2] >> 7;
    buf->intermediateFrequency = t[2];
    buf->RFADClevel = t[3] >> 4;
    buf->chipID = t[4];
    buf->rsv = t[5];
}

void tea5767_write_buffer_default(tea5767_write_buffer_t * buf)
{
    buf->isMute = 0;            //不静音
    buf->isSearchMode = 0;      //非搜索模式
    buf->prePLL = 0;

    buf->postPLL = 0;

    buf->searchDirection = 1;   //向后搜索
    buf->stopSearchLevel = 1;       //搜索到LOW信号时，停止搜索
    buf->sideBand = 1;              //上边带接收
    buf->isMono = 0;            //立体声输出
    buf->isMuteRight = 0;       //右声道不静音
    buf->isMuteLeft = 0;        //左声道不静音
    buf->softwarePort1Output = 0;

    buf->softwarePort2Output = 0;
    buf->isStandby = 0;         //待机模式关
    buf->bandLimit = 0;
    buf->xtal = 1;              //
    buf->isSoftwareMute = 0;     //关闭软静音
    buf->isHighCutControl = 0;  //关闭高频旁路
    buf->isStereoNoiseCanceling = 1; //开启立体声降噪
    buf->isEnableSearchIndicator = 0;
   
    buf->isEnablePLLReference = 0;//xtal = 1 && PLLREF = 0 : 32.768kHZ
    buf->DTC = 0;
    buf->NC = 0;
}

float tea5767_pll_to_freq(uint16_t pll)
{
    return ( pll / 4.0 * 32768.0 - 225000 ) / 1000000.0f;
}

uint16_t tea5767_freq_to_pll(float freq){
    return 4 * (freq * 1000000 + 225000) / 32768;
}