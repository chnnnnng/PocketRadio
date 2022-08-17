// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: PocketRadio

#include "ui.h"

lv_indev_t * my_indev;

static const char *TAG = "GUI";

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void JumpIn_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}


void ui_init(void)
{
    //lv_disp_t * dispp = lv_disp_get_default();
    //lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
    //                                           true, LV_FONT_DEFAULT);
    //lv_disp_set_theme(dispp, theme);

    ui_menu_screen_init();
    ui_home_screen_init();
    ui_settings_screen_init();
    ui_wifi_screen_init();
    ui_batterylow_screen_init();

    load_page(ui_home,group_home);
}

#define page_stack_max 10
static page_stack_item page_stack[page_stack_max];
static int page_stack_index = 0;

void load_page(lv_obj_t * page, lv_group_t * group)
{
    if(page_stack_index > 1 && page == page_stack[page_stack_index-2].page){
        close_page();
        return;
    }
    if(page_stack_index < page_stack_max){
        ESP_LOGI(TAG, "load page %d", page_stack_index);
        page_stack[page_stack_index].page = page;
        page_stack[page_stack_index].group = group;
        page_stack_index++;
        lv_disp_load_scr(page);
        lv_indev_set_group(my_indev, group);
    }
}

void close_page(void)
{
    if(page_stack_index > 1){
        ESP_LOGI(TAG, "close page %d", page_stack_index);
        page_stack_index-=2;
        lv_disp_load_scr(page_stack[page_stack_index].page);
        lv_indev_set_group(my_indev, page_stack[page_stack_index].group);
    }
}