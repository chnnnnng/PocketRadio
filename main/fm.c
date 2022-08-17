#include "fm.h"


tea5767_write_buffer_t fm_wbuf;
tea5767_read_buffer_t fm_rbuf;

tea5767_channel_t* saved_channels[MAX_SAVED_CHANNELS];
size_t saved_channels_index;
size_t saved_channels_count;

void fm_set_channel_freq(float freq, bool isMute)
{
    uint16_t pll = tea5767_freq_to_pll(freq);
    fm_wbuf.prePLL = GET_PREPLL_FROM_PLL(pll);
    fm_wbuf.postPLL = GET_POSTPLL_FROM_PLL(pll);
    if(isMute) fm_wbuf.isMute = 1;
    tea5767_i2c_write(&fm_wbuf);
}

void fm_set_channel(tea5767_channel_t *channel, bool isMute)
{
    tea5767_write_buffer_default(&fm_wbuf);
    fm_wbuf.prePLL = channel->pllh;
    fm_wbuf.postPLL = channel->plll;
    if(isMute) fm_wbuf.isMute = 1;
    tea5767_i2c_write(&fm_wbuf);
}

float fm_current_channel(tea5767_channel_t * ch)
{
    tea5767_i2c_read(&fm_rbuf);
    ch->pllh = (uint8_t)fm_rbuf.prePLL & 0x3F;
    ch->plll = (uint8_t)fm_rbuf.postPLL & 0xFF;
    ch->level = ((uint8_t)fm_rbuf.RFADClevel) & 0xF;
    ch->ifc = ((uint8_t)fm_rbuf.intermediateFrequency) & 0x7F;
    ch->stereo = fm_rbuf.isStereo;
    uint16_t pll = ((uint16_t)(fm_rbuf.prePLL & 0x3F)) << 8 | (uint8_t)fm_rbuf.postPLL;
    return tea5767_pll_to_freq(pll);
}


void fm_search_channels()
{
    tea5767_write_buffer_default(&fm_wbuf);
    tea5767_channel_t channel;
    uint16_t freq_int = 8750;
    float freq;
    float freq_read = 0;
    while (freq_int <= 10800)
    {   
        freq = freq_int / 100.0f;
        fm_set_channel_freq(freq, false);
        printf("FM set: %d.%d\n", (int)freq,((int)(freq*1000))%1000);
        delay_ms(30);
        freq_read = fm_current_channel(&channel);
        if((int)channel.level >= FM_LEVEL_THRES && (int)channel.ifc >= 50){/* && channel.ifc >= 0x31 && channel.ifc <= 0x3e*/
            saved_channels_count++;
            tea5767_channel_t * ch = malloc(sizeof(tea5767_channel_t));
            memcpy(ch,&channel,sizeof(tea5767_channel_t));
            saved_channels[saved_channels_index] = ch;
            //更新已搜到的台数
            char *txt = malloc(20);
            if(saved_channels_count == 1) sprintf(txt,"find 1 channel");
            else sprintf(txt,"find %d channels", saved_channels_count);
            //lv_label_set_text(ui_channelcountlabel,txt);
            free(txt);
            if(++saved_channels_index == MAX_SAVED_CHANNELS){
                saved_channels_index = 0;
                break;
            }
        }
        freq_int+=10;
        if(freq_int % 200 == 0){
            //更新进度条
            int progress = 100 * (freq_int - 8750) / 2150;
            char *txt = malloc(10);
            sprintf(txt,"%d%%", progress);
            //lv_label_set_text(ui_scanprogresslabel,txt);
            free(txt);
        }
    }  
    printf("FM search done, saved %d channels\n",saved_channels_count);
    char *roller = malloc(10*MAX_SAVED_CHANNELS);
    memset(roller,0,10*MAX_SAVED_CHANNELS);
    char *temp = malloc(10);
    uint16_t pll;
    for(int i=0;i<saved_channels_count;i++){
        pll = ((uint16_t)(saved_channels[i]->pllh & 0x3F)) << 8 | (uint8_t)saved_channels[i]->plll;
        freq = tea5767_pll_to_freq(pll);
        sprintf(temp,"FM %d.%d\n", (int)freq,((int)(freq*10))%10);
        strcat(roller,temp);
    }
    //lv_roller_set_options(ui_fmroller, roller, LV_ROLLER_MODE_NORMAL);
    free(temp);
    free(roller);
    //if(saved_channels_count != 0) lv_disp_load_scr(ui_fmscreen);
}

void fm_init()
{
    tea5767_i2c_init(FM_SDA, FM_SCL);
    tea5767_write_buffer_default(&fm_wbuf);
}

void fm_on_channel_change_handler(int channel)
{
    float freq =  (channel + 875*2)/20.0f;
    fm_set_channel_freq(freq, false);
    char txt[20];
    sprintf(txt,"FM %d.%2d", (int)freq,((int)(freq*100))%100);
    lv_label_set_text(ui_Label1, txt);
}