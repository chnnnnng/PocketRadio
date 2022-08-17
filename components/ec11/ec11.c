#include "ec11.h"
#define ESP_INTR_FLAG_DEFAULT 0

QueueHandle_t ec11_gpio_event_queue = NULL;   // 消息队列

#define TAG "ec11"

static int ec11_a_posedge_b_value = -1;
static int ec11_a_negedge_b_value = -1;
static int last_moves = 0;
static bool last_press = false;

static void IRAM_ATTR ec11_gpio_isr_handler(void * arg)
{
    
    uint32_t GPIO_Queue_Data = 0;       // Send queue variables 

    if(arg == (void *) EC11_A){
        int a_value = gpio_get_level(EC11_A);
        if(a_value == 0){ //A相下降沿
            ec11_a_negedge_b_value = gpio_get_level(EC11_B);
        }else{ //A相上升沿
            ec11_a_posedge_b_value = gpio_get_level(EC11_B);

            if(ec11_a_posedge_b_value == 0 && ec11_a_negedge_b_value == 1){
                //counter clockwose
                GPIO_Queue_Data = EC11_CCW;
            }else if(ec11_a_posedge_b_value == 1 && ec11_a_negedge_b_value == 0){
                //clockwise
                GPIO_Queue_Data = EC11_CW;
            }
        }
    }else if(arg == (void *) EC11_K){
        if(gpio_get_level(EC11_K) == 0){
            GPIO_Queue_Data = EC11_KEY_DOWN;
        }
    }
    if(GPIO_Queue_Data != 0){
        xQueueSendFromISR(ec11_gpio_event_queue, &GPIO_Queue_Data, NULL);  
    }
}


void ec11_init(void)
{
    //B相关闭中断
    gpio_config_t io_conf;                                  // To configure GPIO Structure 
    io_conf.intr_type = GPIO_INTR_DISABLE;                  // Do not enable GPIO interrupt 
    io_conf.mode = GPIO_MODE_INPUT;                         //GPIO The input mode 
    io_conf.pull_down_en = 0;                               // Pull down enable 
    io_conf.pull_up_en = 0;                                 // Pull up does not enable 
    io_conf.pin_bit_mask = EC11_CHB_GPIO_INPUT_PIN_SEL;  //GPIO Input pin selection 
    gpio_config(&io_conf);                                  // To configure IO Parameters 

    //A相开启中断，上升、下降沿触发
    io_conf.intr_type = GPIO_INTR_ANYEDGE;                  // Edge triggered interrupt 
    io_conf.pin_bit_mask = EC11_CHA_GPIO_INPUT_PIN_SEL;  //GPIO Input pin selection 
    gpio_config(&io_conf);                                  // To configure IO Parameters 

    //按键按下中断，下降沿触发
    io_conf.intr_type = GPIO_INTR_NEGEDGE;                  // Do not enable GPIO interrupt 
    io_conf.pin_bit_mask = EC11_KEY_GPIO_INPUT_PIN_SEL;  //GPIO Input pin selection 
    gpio_config(&io_conf);                                  // To configure IO Parameters 

    //加载中断服务
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    //添加中断处理程序
    gpio_isr_handler_add(EC11_A, ec11_gpio_isr_handler, (void * )EC11_A);// Add interrupt service  
    
    gpio_isr_handler_add(EC11_K, ec11_gpio_isr_handler, (void *)EC11_K);


    //创建消息队列
    ec11_gpio_event_queue = xQueueCreate(1,sizeof(uint32_t));
}

extern bool ec11_change_callback(char val);

void ec11_task(void)
{
    
    char Capure_Enconder_State = 0;
    bool event_stop = false;
    while(1){
    
        // Get queue information 
        if (pdTRUE == xQueueReceive(ec11_gpio_event_queue, & Capure_Enconder_State, (TickType_t)0)){
            event_stop = ec11_change_callback((char)Capure_Enconder_State);
            if(event_stop == false){
                switch (Capure_Enconder_State)
                {
                    case EC11_CW:
                        //printf("EC11 Clockwise\n\r");
                        last_moves++;
                        break;
                    case EC11_CCW:
                        //printf("EC11 Counter Clockwise\n\r");
                        last_moves--;
                        break;
                    case EC11_KEY_DOWN:
                        //printf("EC11 Key Down\n\r");
                        last_press = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        vTaskDelay(30/portTICK_PERIOD_MS);
    }   
}

int ec11_get_new_moves()
{
    int temp = last_moves;
    last_moves = 0;
    return temp;
}

bool ec11_get_press()
{
    return !gpio_get_level(EC11_K);
}