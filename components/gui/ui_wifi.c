#include "ui.h"
#include "network.h"

lv_obj_t * ui_wifi;
lv_obj_t * ui_Label3;
lv_obj_t * ui_ddwifissid;
lv_obj_t * ui_tewifipasswd;
lv_obj_t * ui_btnwificancel;
lv_obj_t * ui_Label4;
lv_obj_t * ui_btnwificonnect;
lv_obj_t * ui_Label5;

static lv_obj_t * kb;

lv_group_t * group_wifi;

static const char *TAG = "GUI_Wifi";
static uint16_t selected_sta_index = -1;
static wifi_ap_record_t * records;

static void ui_event_wifi(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        JumpIn_Animation(ui_Label3, 0);
        records = malloc(WIFI_SCAN_LIST_SIZE * sizeof(wifi_ap_record_t));
        uint16_t ap_count = network_wifi_scan(records);
        ESP_LOGI(TAG,"ap_count:%d",ap_count);
        for (int i = 0; (i < WIFI_SCAN_LIST_SIZE) && (i < ap_count); i++) {
            //ESP_LOGI(TAG,"ssid:%s",records[i].ssid);
            lv_dropdown_add_option(ui_ddwifissid, (const char *)records[i].ssid, i);
        }
        free(records);
    }
    if(event == LV_EVENT_SCREEN_UNLOADED) {
        //free(records);
    }
    if(event == LV_EVENT_CLICKED) {
        if(ta == ui_btnwificancel){
            close_page();
        }
        if(ta == ui_btnwificonnect){
            //lv_dropdown_get_selected_str(ui_ddwifissid, ssid, 20);
            selected_sta_index = lv_dropdown_get_selected(ui_ddwifissid);
            char * passwd = lv_textarea_get_text(ui_tewifipasswd);
            ESP_LOGI(TAG, "WIFI Selected Index:%d",selected_sta_index);
            ESP_LOGI(TAG, "WIFI SSID:%s",records[selected_sta_index].ssid);
            ESP_LOGI(TAG, "WIFI PASSWD:%s",passwd);
            network_connect((uint8_t*)records[selected_sta_index].ssid,(uint8_t*)passwd,records[selected_sta_index].authmode);
            close_page();
        }
    }
    if(event == LV_EVENT_CLICKED){
        if(ta == ui_tewifipasswd){
            ESP_LOGI(TAG,"passwd clicked");
            lv_keyboard_set_textarea(kb, ui_tewifipasswd);
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_group_focus_obj(kb);
            lv_group_focus_freeze(group_wifi,true);
            lv_group_set_editing(group_wifi,true);
            lv_obj_set_y(ui_tewifipasswd, -27);
        }
    }
   
    if(event == LV_EVENT_READY){
        if(ta == kb){
            ESP_LOGI(TAG,"kb ready");
            lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_group_focus_freeze(group_wifi,false);
            lv_group_focus_obj(ui_tewifipasswd);
            lv_keyboard_set_textarea(kb, NULL);
            lv_obj_set_y(ui_tewifipasswd, 12);
        }
    }

    if(event == LV_EVENT_CANCEL){
        if(ta == kb){
            ESP_LOGI(TAG,"kb cancel");
            lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_group_focus_freeze(group_wifi,false);
            lv_group_focus_obj(ui_tewifipasswd);
            lv_keyboard_set_textarea(kb, NULL);
            lv_obj_set_y(ui_tewifipasswd, 12);
        }
    }

    if(event == LV_EVENT_VALUE_CHANGED){
        if(ta == ui_ddwifissid){
            lv_dropdown_set_text(ui_ddwifissid, NULL);
            selected_sta_index = lv_dropdown_get_selected(ui_ddwifissid);
        }
    }
}


void ui_wifi_screen_init(void)
{

    // ui_wifi

    ui_wifi = lv_obj_create(NULL);

    group_wifi = lv_group_create();
    lv_group_set_default(group_wifi);

    lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_wifi, ui_event_wifi, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_wifi, lv_color_hex(0xF09939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_wifi, lv_color_hex(0xEB6505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_wifi, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label3

    ui_Label3 = lv_label_create(ui_wifi);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, -57);
    lv_obj_set_y(ui_Label3, -46);

    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label3, "Wi-Fi\n");

    // ui_ddwifissid

    ui_ddwifissid = lv_dropdown_create(ui_wifi);
    //lv_dropdown_set_options(ui_ddwifissid, "ssid1\nssid2\nssid3");
    lv_dropdown_set_text(ui_ddwifissid, "");

    lv_obj_set_width(ui_ddwifissid, 150);
    lv_obj_set_height(ui_ddwifissid, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ddwifissid, 0);
    lv_obj_set_y(ui_ddwifissid, -27);

    lv_obj_set_align(ui_ddwifissid, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ddwifissid, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_set_style_bg_color(ui_ddwifissid, lv_color_hex(0xF09F49), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ddwifissid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ddwifissid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ddwifissid, ui_event_wifi, LV_EVENT_ALL, NULL);

    //lv_group_add_obj(group_wifi,ui_ddwifissid);

    // ui_tewifipasswd

    ui_tewifipasswd = lv_textarea_create(ui_wifi);

    lv_obj_set_width(ui_tewifipasswd, 150);
    lv_obj_set_height(ui_tewifipasswd, 35);

    lv_obj_set_x(ui_tewifipasswd, 0);
    lv_obj_set_y(ui_tewifipasswd, 12);

    lv_obj_set_align(ui_tewifipasswd, LV_ALIGN_CENTER);

    //if("" == "") lv_textarea_set_accepted_chars(ui_tewifipasswd, NULL);
    //else lv_textarea_set_accepted_chars(ui_tewifipasswd, "");
    lv_textarea_set_accepted_chars(ui_tewifipasswd, "");

    lv_textarea_set_text(ui_tewifipasswd, "");
    lv_textarea_set_placeholder_text(ui_tewifipasswd, "password");

    lv_obj_set_style_text_color(ui_tewifipasswd, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_tewifipasswd, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tewifipasswd, lv_color_hex(0xF09F49), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tewifipasswd, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_tewifipasswd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_tewifipasswd, lv_color_hex(0xF1BD86), LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_tewifipasswd, 255, LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);

    lv_textarea_set_one_line(ui_tewifipasswd, true);

    //lv_group_add_obj(group_wifi,ui_tewifipasswd);
    lv_obj_add_event_cb(ui_tewifipasswd, ui_event_wifi, LV_EVENT_ALL, NULL);

    // ui_btnwificancel

    ui_btnwificancel = lv_btn_create(ui_wifi);

    lv_obj_set_width(ui_btnwificancel, 69);
    lv_obj_set_height(ui_btnwificancel, 28);

    lv_obj_set_x(ui_btnwificancel, -42);
    lv_obj_set_y(ui_btnwificancel, 49);

    lv_obj_set_align(ui_btnwificancel, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_btnwificancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_btnwificancel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_btnwificancel, lv_color_hex(0xE0655C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnwificancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_group_add_obj(group_wifi,ui_btnwificancel);
    lv_obj_add_event_cb(ui_btnwificancel, ui_event_wifi, LV_EVENT_ALL, NULL);

    // ui_Label4

    ui_Label4 = lv_label_create(ui_btnwificancel);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, -2);
    lv_obj_set_y(ui_Label4, 0);

    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label4, "Cancel");
    lv_label_set_recolor(ui_Label4, "true");

    // ui_btnwificonnect

    ui_btnwificonnect = lv_btn_create(ui_wifi);

    lv_obj_set_width(ui_btnwificonnect, 74);
    lv_obj_set_height(ui_btnwificonnect, 28);

    lv_obj_set_x(ui_btnwificonnect, 37);
    lv_obj_set_y(ui_btnwificonnect, 49);

    lv_obj_set_align(ui_btnwificonnect, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_btnwificonnect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_btnwificonnect, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_btnwificonnect, lv_color_hex(0xA0CF78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnwificonnect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_group_add_obj(group_wifi,ui_btnwificonnect);
    lv_obj_add_event_cb(ui_btnwificonnect, ui_event_wifi, LV_EVENT_ALL, NULL);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_btnwificonnect);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label5, "Connect");
    lv_label_set_recolor(ui_Label5, "true");

    //keyboard 
    kb = lv_keyboard_create(ui_wifi);
    //lv_keyboard_set_textarea(kb, NULL);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(kb, ui_event_wifi, LV_EVENT_ALL, NULL);
}