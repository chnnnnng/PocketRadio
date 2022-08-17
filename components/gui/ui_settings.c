#include "ui.h"

lv_obj_t * ui_settings;
lv_obj_t * ui_listsettings;

lv_group_t * group_settings;

static const char *TAG = "GUI_Settings";

static void ui_settings_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        char * txt = lv_list_get_btn_text(ui_listsettings, obj);
        //printf("Clicked: %s", txt);
        if(strcmp(txt,"Wi-Fi")==0){
            load_page(ui_wifi, group_wifi);
        }else if(strcmp(txt,"Apply")==0){
            close_page();
        }else if(strcmp(txt,"Close")==0){
            close_page();
        }else if(strcmp(txt,"Power OFF")==0){
            power_off();
        }
    }
}

void ui_settings_screen_init(void)
{

    // ui_settings

    ui_settings = lv_obj_create(NULL);

    group_settings = lv_group_create();

    lv_obj_clear_flag(ui_settings, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_settings, lv_color_hex(0xF09939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_settings, lv_color_hex(0xEB6505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_settings, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);


     /*Create a list*/
    lv_obj_t * list1 = lv_list_create(ui_settings);
    lv_obj_set_size(list1, 160, 128);
    lv_obj_center(list1);

    /*Add buttons to the list*/
    //lv_list_add_text(list1, "File");
    // btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "New");
    // lv_obj_add_event_cb(btn, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    // btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Open");
    // lv_obj_add_event_cb(btn, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    // btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save");
    // lv_obj_add_event_cb(btn, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    // btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete");
    // lv_obj_add_event_cb(btn, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    // btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit");
    // lv_obj_add_event_cb(btn, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);

    lv_list_add_text(list1, "Connectivity");
    lv_obj_t * btn_wifi = lv_list_add_btn(list1, LV_SYMBOL_WIFI, "Wi-Fi");
    lv_obj_add_event_cb(btn_wifi, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group_settings, btn_wifi);

    lv_list_add_text(list1, "Power");
    lv_obj_t * btn_poweroff = lv_list_add_btn(list1, LV_SYMBOL_POWER, "Power OFF");
    lv_obj_add_event_cb(btn_poweroff, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group_settings, btn_poweroff);

    lv_list_add_text(list1, "Exit");
    lv_obj_t * btn_apply = lv_list_add_btn(list1, LV_SYMBOL_OK, "Apply");
    lv_obj_add_event_cb(btn_apply, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group_settings, btn_apply);
    lv_obj_t * btn_exit = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Close");
    lv_obj_add_event_cb(btn_exit, ui_settings_event_handler, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group_settings, btn_exit);

}