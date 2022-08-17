#include "ui.h"

lv_obj_t * ui_home;
lv_obj_t * ui_charge;
lv_obj_t * ui_battery;
lv_obj_t * ui_batterybar;
lv_obj_t * ui_batteryborder;
lv_obj_t * ui_time;
lv_obj_t * ui_Slider1;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Image2;

lv_group_t * group_home;

static const char *TAG = "GUI_Home";

void ui_home_group_event_cb(lv_event_t * e);
void ui_home_screen_init(void);

void ui_home_screen_init(void)
{

    // ui_home

    ui_home = lv_obj_create(NULL);

    group_home = lv_group_create();

    lv_obj_clear_flag(ui_home, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_home, lv_color_hex(0xF09939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_home, lv_color_hex(0xEB6505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_home, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_charge

    ui_charge = lv_img_create(ui_home);
    lv_img_set_src(ui_charge, &ui_img_ic_charge_png);

    lv_obj_set_width(ui_charge, 32);
    lv_obj_set_height(ui_charge, 32);

    lv_obj_set_x(ui_charge, -27);
    lv_obj_set_y(ui_charge, -50);

    lv_obj_set_align(ui_charge, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_charge, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_charge, LV_OBJ_FLAG_SCROLLABLE);

    // ui_battery

    ui_battery = lv_obj_create(ui_home);

    lv_obj_set_width(ui_battery, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_battery, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_battery, -56);
    lv_obj_set_y(ui_battery, -51);

    lv_obj_set_align(ui_battery, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_battery, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_battery, lv_color_hex(0x1B82E9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_battery, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_batterybar

    ui_batterybar = lv_bar_create(ui_battery);
    lv_bar_set_range(ui_batterybar, 0, 100);
    lv_bar_set_value(ui_batterybar, 50, LV_ANIM_OFF);

    lv_obj_set_width(ui_batterybar, 20);
    lv_obj_set_height(ui_batterybar, 12);

    lv_obj_set_x(ui_batterybar, -2);
    lv_obj_set_y(ui_batterybar, 0);

    lv_obj_set_align(ui_batterybar, LV_ALIGN_CENTER);

    lv_obj_set_style_radius(ui_batterybar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_batterybar, lv_color_hex(0xEFAD69), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batterybar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_batterybar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_batterybar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batterybar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_batteryborder

    ui_batteryborder = lv_img_create(ui_battery);
    lv_img_set_src(ui_batteryborder, &ui_img_battery_png);

    lv_obj_set_width(ui_batteryborder, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_batteryborder, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_batteryborder, 0);
    lv_obj_set_y(ui_batteryborder, 0);

    lv_obj_set_align(ui_batteryborder, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_batteryborder, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_batteryborder, LV_OBJ_FLAG_SCROLLABLE);

     // ui_Slider1

    ui_Slider1 = lv_slider_create(ui_home);
    lv_slider_set_range(ui_Slider1, 0, 410);
    lv_slider_set_value(ui_Slider1, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Slider1) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Slider1, 0, LV_ANIM_OFF);

    lv_obj_set_width(ui_Slider1, 140);
    lv_obj_set_height(ui_Slider1, 50);

    lv_obj_set_x(ui_Slider1, 0);
    lv_obj_set_y(ui_Slider1, 30);

    lv_obj_set_align(ui_Slider1, LV_ALIGN_CENTER);

    lv_obj_set_style_radius(ui_Slider1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xEE9D4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Slider1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Slider1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Slider1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Slider1, lv_color_hex(0xE99C53), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Slider1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Slider1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Slider1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Slider1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Slider1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Slider1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xEE9D4A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Slider1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Slider1, lv_color_hex(0xF45020), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Slider1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Slider1, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Slider1, LV_BORDER_SIDE_RIGHT, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Slider1);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 0);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "FM 87.50");

    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_time

    ui_time = lv_label_create(ui_home);

    lv_obj_set_width(ui_time, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_time, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_time, 46);
    lv_obj_set_y(ui_time, -51);

    lv_obj_set_align(ui_time, LV_ALIGN_CENTER);

    lv_label_set_text(ui_time, "PM 9:50");

    // ui_Image1

    ui_Image1 = lv_img_create(ui_home);
    lv_img_set_src(ui_Image1, &ui_img_love_png);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 63);
    lv_obj_set_y(ui_Image1, -17);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_img_recolor(ui_Image1, lv_color_hex(0xF03B3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Image1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_home);
    lv_img_set_src(ui_Image2, &ui_img_menu_png);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, 42);
    lv_obj_set_y(ui_Image2, -17);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(group_home,ui_Image2);
    lv_group_add_obj(group_home,ui_Image1);
    lv_group_add_obj(group_home,ui_Slider1);

    lv_group_focus_obj(ui_Slider1);
    //lv_group_focus_freeze(group_home, true);
    lv_group_set_editing(group_home,true);

    lv_obj_add_event_cb(ui_Slider1, ui_home_group_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Image1, ui_home_group_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Image2, ui_home_group_event_cb, LV_EVENT_ALL, NULL);
}

void ui_home_group_event_cb(lv_event_t * e){
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_Image1){
            ESP_LOGI(TAG, "homepage love btn focus");
            lv_obj_set_style_border_color(ui_Image1, lv_color_hex(0x5fa9dc), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_Image1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui_Image1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        if(ta == ui_Image2){
            ESP_LOGI(TAG, "homepage menu btn focus");
            lv_obj_set_style_border_color(ui_Image2, lv_color_hex(0x5fa9dc), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_Image2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui_Image2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    if(code == LV_EVENT_DEFOCUSED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_Image1){
            ESP_LOGI(TAG, "homepage love btn defocus");
            lv_obj_set_style_border_color(ui_Image1, lv_color_hex(0x5fa9dc), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_Image1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui_Image1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        if(ta == ui_Image2){
            ESP_LOGI(TAG, "homepage menu btn defocus");
            lv_obj_set_style_border_color(ui_Image2, lv_color_hex(0x5fa9dc), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_Image2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui_Image2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    if(code == LV_EVENT_CLICKED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_Slider1){
            ESP_LOGI(TAG, "homepage slider clicked");
            lv_group_set_editing(group_home,true);
        }
        if(ta == ui_Image2){
            ESP_LOGI(TAG, "homepage menu btn clicked");
            load_page(ui_menu, group_menu);
        }
        if(ta == ui_Image1){
            ESP_LOGI(TAG, "homepage love btn clicked");
            
        }
    }

    if(code == LV_EVENT_VALUE_CHANGED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_Slider1){
            int v = (int)lv_slider_get_value(ui_Slider1);
            fm_on_channel_change_handler(v);
            ESP_LOGI(TAG, "bar value changed %d\n", v);
        }
    }
}