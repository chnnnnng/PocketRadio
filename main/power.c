#include "power.h"

static const char *TAG = "Power";
static bool cali_enable = false;
static esp_adc_cal_characteristics_t adc1_chars;
bool battery_low = false;
bool sleep_mode = false;
const uint32_t power_task_interval_s = 3;//power_task的循环周期，单位秒
uint32_t sleep_mode_time = 60;//进入休眠状态的时间，单位秒
uint32_t sleep_mode_counter = 0;

void power_init()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = ((1ULL<<POWER_RADIO_IO) | (1ULL<<POWER_DISPLAY_IO));
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1ULL<<POWER_CHARGING_IO);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    power_radio(false);
    power_display(false);
}


void power_radio(bool onoff)
{
    gpio_set_level(POWER_RADIO_IO, onoff);
}


void power_display(bool onoff)
{
    gpio_set_level(POWER_DISPLAY_IO, onoff);
}

static bool adc_calibration_init(void)
{
    esp_err_t ret;
    bool cali_enable = false;

    ret = esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
    } else {
        ESP_LOGE(TAG, "Invalid arg");
    }

    return cali_enable;
}


void power_voltage_init(void)
{
    cali_enable = adc_calibration_init();
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_12));
    ESP_ERROR_CHECK(adc1_config_channel_atten(POWER_BATTERY_ADC, ADC_ATTEN_DB_11));
}

uint32_t power_voltage(void)
{
    int raw = adc1_get_raw(POWER_BATTERY_ADC);
    static uint32_t voltage;
    //ESP_LOGI(TAG, "raw  data: %d", raw);
    if (cali_enable) {
        voltage = esp_adc_cal_raw_to_voltage(raw, &adc1_chars);
        //ESP_LOGI(TAG, "cali data: %d mV", voltage);
    }
    return voltage;
}

void power_task(void)
{
    power_voltage_init();
    uint32_t voltage = 0;
    uint8_t batt = 0;
    int charge = false;
    for(;;){
        voltage = 2.1 * power_voltage();
        char txt[20];
        sprintf(txt,"%d", (int)voltage);
        lv_label_set_text(ui_time, txt);

        //迟滞比较器判断电池电量低:thres_low=3600,thres_high=3700
        if(battery_low == false && voltage <= 3600){//进入低电量模式
            power_enter_low_power_mode();
        }else if(battery_low == true && voltage >= 3700){//退出低电量模式
            power_exit_low_power_mode();
        }
        if(battery_low == true){
            batt = 0;
        }else{
            batt = (voltage - 3600) / 6;
            if(batt >= 100) batt = 100;
        }
        lv_bar_set_value(ui_batterybar, batt, LV_ANIM_ON);

        charge = gpio_get_level(POWER_CHARGING_IO);
        if(charge == 0){//正在充电
            lv_obj_set_y(ui_charge, -50);
        }else{//不在充电
            lv_obj_set_y(ui_charge, -100);
        }
        if(sleep_mode == false && battery_low == false && ++sleep_mode_counter == sleep_mode_time/power_task_interval_s){
            power_enter_sleep_mode();
        }
        vTaskDelay(pdMS_TO_TICKS(power_task_interval_s*1000)); //每3秒检测一次
    }
}

void power_enter_sleep_mode()
{
    sleep_mode = true;
    power_display(false);
    ESP_LOGI(TAG,"Enter sleep mode");
}

void power_exit_sleep_mode()
{
    if(!battery_low){
        sleep_mode = false;
        sleep_mode_counter = 0;
        power_display(true);
        ESP_LOGI(TAG,"Resume from sleep mode");
    }else{
        power_display(true);
        ESP_LOGI(TAG,"Battery low mode show screen");
        vTaskDelay(pdMS_TO_TICKS(3000));
        power_display(false);
    }

}

void power_refresh_sleep_mode_timer()
{
    sleep_mode_counter = 0;
}

void power_enter_low_power_mode()
{
    battery_low = true;
    load_page(ui_batterylow,NULL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    power_radio(false);
    power_enter_sleep_mode();
}

void power_exit_low_power_mode()
{
    battery_low = false;
    esp_restart();
}

void power_off()
{
    power_radio(false);
    power_display(false);
    esp_deep_sleep_enable_gpio_wakeup(EC11_KEY_GPIO_INPUT_PIN_SEL,ESP_GPIO_WAKEUP_GPIO_LOW);
    esp_deep_sleep_start();
}