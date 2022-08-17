#include "st7735.h"

static  spi_device_handle_t spi;
static bool command_0_data_1 = 0;

void st7735_init(void){
    st7735_gpio_init();
    st7735_spi_init();
    //st7735_reset();
    st7735_lcd_init();
}


void st7735_reset(void){
    gpio_clear(ST7735_RST);
    delay_ms(200);
    gpio_set(ST7735_RST);
    delay_ms(100);
}


void st7735_gpio_init(void){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<ST7735_DC) | (1ULL<<ST7735_RST) );
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    gpio_set(ST7735_RST);
}

//This function is called (in irq context!) just before a transmission starts. It will
//set the D/C line to the value indicated in the user field.
void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    gpio_set_level(ST7735_DC, command_0_data_1);
}

void st7735_spi_init(void){
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=-1,
        .mosi_io_num=ST7735_SDA,
        .sclk_io_num=ST7735_SCK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=PARALLEL_LINES*320*2+8,
        .flags=SPICOMMON_BUSFLAG_MASTER,
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=20*1000*1000,           //Clock out at 10 MHz
        .mode=0,                                //SPI mode 0
        .spics_io_num=-1,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
        //.flags=SPI_DEVICE_BIT_LSBFIRST,
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
    //Initialize the LCD
}

void st7735_lcd_init(void){

    //gpio_clear(ST7735_CS);

    st7735_write_command(0x11);//睡眠退出
	delay_ms(500);
	
	//ST7735R 帧速率
	st7735_write_command(0xB1); 
	st7735_write_data_8(0x01); 
	st7735_write_data_8(0x2C); 
	st7735_write_data_8(0x2D); 

	st7735_write_command(0xB2); 
	st7735_write_data_8(0x01); 
	st7735_write_data_8(0x2C); 
	st7735_write_data_8(0x2D); 

	st7735_write_command(0xB3); 
	st7735_write_data_8(0x01); 
	st7735_write_data_8(0x2C); 
	st7735_write_data_8(0x2D); 
	st7735_write_data_8(0x01); 
	st7735_write_data_8(0x2C); 
	st7735_write_data_8(0x2D); 
	
	st7735_write_command(0xB4);//列反转
	st7735_write_data_8(0x07); 
	
	//ST7735R Power Sequence
	st7735_write_command(0xC0); 
	st7735_write_data_8(0xA2); 
	st7735_write_data_8(0x02); 
	st7735_write_data_8(0x84); 
	st7735_write_command(0xC1); 
	st7735_write_data_8(0xC5); 

	st7735_write_command(0xC2); 
	st7735_write_data_8(0x0A); 
	st7735_write_data_8(0x00); 

	st7735_write_command(0xC3); 
	st7735_write_data_8(0x8A); 
	st7735_write_data_8(0x2A); 
	st7735_write_command(0xC4); 
	st7735_write_data_8(0x8A); 
	st7735_write_data_8(0xEE); 
	
	st7735_write_command(0xC5);//VCOM 
    st7735_write_data_8(0x0E); 
	
    st7735_write_command(0x36);//MX,MY,RGB mode 
	
	switch (DISPLAY_DIRECTION)//显示的方向(竖屏:0,横屏:1,竖屏旋转180度:2,横屏旋转180度:3)
	{
		case	0:  st7735_write_data_8(0xC0);break;//竖屏
		case	1:  st7735_write_data_8(0xA0);break;//横屏
		case    2:  st7735_write_data_8(0x00);break;//竖屏翻转180度
		default	 :  st7735_write_data_8(0x60);break;//横屏翻转180度
	}

	//ST7735R Gamma Sequence
    st7735_write_command(0xE0); 
    st7735_write_data_8(0x0F); 
    st7735_write_data_8(0x1A); 
    st7735_write_data_8(0x0F); 
    st7735_write_data_8(0x18); 
    st7735_write_data_8(0x2F); 
    st7735_write_data_8(0x28); 
    st7735_write_data_8(0x20); 
    st7735_write_data_8(0x22); 
    st7735_write_data_8(0x1F); 
    st7735_write_data_8(0x1B); 
    st7735_write_data_8(0x23); 
    st7735_write_data_8(0x37); 
    st7735_write_data_8(0x00); 	
    st7735_write_data_8(0x07); 
    st7735_write_data_8(0x02); 
    st7735_write_data_8(0x10); 

    st7735_write_command(0xE1); 
    st7735_write_data_8(0x0F); 
    st7735_write_data_8(0x1B); 
    st7735_write_data_8(0x0F); 
    st7735_write_data_8(0x17); 
    st7735_write_data_8(0x33); 
    st7735_write_data_8(0x2C); 
    st7735_write_data_8(0x29); 
    st7735_write_data_8(0x2E); 
    st7735_write_data_8(0x30); 
    st7735_write_data_8(0x30); 
    st7735_write_data_8(0x39); 
    st7735_write_data_8(0x3F); 
    st7735_write_data_8(0x00); 
    st7735_write_data_8(0x07); 
    st7735_write_data_8(0x03); 
    st7735_write_data_8(0x10);  
	
    st7735_write_command(0xF0);//启动测试命令
    st7735_write_data_8(0x01); 
    st7735_write_command(0xF6);//禁用ram省电模式
    st7735_write_data_8(0x00); 
	
    st7735_write_command(0x3A);//65k mode 
    st7735_write_data_8(0x05); 
    st7735_write_command(0x29);//开启显示
}


void st7735_write_byte(uint8_t byte){
    uint8_t buf = byte;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=&buf;               //Data
    spi_device_polling_transmit(spi, &t);  //Transmit!
}


void st7735_write_halfword(uint16_t halfword){
    
    uint16_t buf = SPI_SWAP_DATA_TX(halfword ,16);
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=16;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=&buf;               //Data
    spi_device_polling_transmit(spi, &t);  //Transmit!
}

void st7735_write_word(uint32_t word){
    uint32_t buf = word;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=32;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=&buf;               //Data
    spi_device_polling_transmit(spi, &t);  //Transmit!
}

void st7735_write_buffer(uint8_t *buffer, size_t len){
    uint8_t * buf = buffer;
    while (len > 0)
    {
        if(len >= 1024){
            len -= 1024;
            
            spi_transaction_t t;
            memset(&t, 0, sizeof(t));       //Zero out the transaction
            t.length=1024*8;                 //Len is in bytes, transaction length is in bits.
            t.tx_buffer=buf;               //Data
            spi_device_polling_transmit(spi, &t);  //Transmit!

            buf += 1024;
        }else{
            spi_transaction_t t;
            memset(&t, 0, sizeof(t));       //Zero out the transaction
            t.length=len*8;                 //Len is in bytes, transaction length is in bits.
            t.tx_buffer=buf;               //Data
            spi_device_polling_transmit(spi, &t);  //Transmit!

            len = 0;
        }
    }
    
}

void st7735_write_command(uint8_t command){
    st7735_for_command();
    st7735_write_byte(command);
}


void st7735_write_data_8(uint8_t data8){
    st7735_for_data();
    st7735_write_byte(data8);
}


void st7735_write_data_16(uint16_t data16){
    st7735_for_data();
    st7735_write_halfword(data16);
}

void st7735_write_data_32(uint32_t data32){
    st7735_for_data();
    st7735_write_word(data32);
}

void st7735_write_data_buffer(uint8_t *data, size_t len){
    st7735_for_data();
    uint8_t * buf = data;
    st7735_write_buffer(buf,len);
}

void st7735_write_color_buffer(uint16_t *colorbuf, size_t len){
    st7735_for_data();
    for(int i=0;i<len;i++){
        colorbuf[i] = SPI_SWAP_DATA_TX(colorbuf[i],16);
    }
    st7735_write_buffer(colorbuf,len*2);
}


void st7735_set_window(uint16_t x, uint16_t y, uint16_t w, uint16_t h){
    st7735_write_command(0x2A);
    st7735_write_data_16(x);
    st7735_write_data_16(x+w-1);
    st7735_write_command(0x2B);
    st7735_write_data_16(y);
    st7735_write_data_16(y+h-1);
    st7735_write_command(0x2C);
}

void st7735_clear(uint16_t color){
    st7735_set_window(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    st7735_for_data();
    for(int i=0;i<DISPLAY_HEIGHT*DISPLAY_WIDTH;i++){
        st7735_write_halfword(color);
    }
}

void st7735_point(uint16_t x, uint16_t y, uint16_t color){
    st7735_set_window(x,y,1,1);
    st7735_write_data_16(color);
}