#include "ui.h"

lv_obj_t * ui_batterylow;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Label6;

void ui_batterylow_screen_init(void)
{

    // ui_batterylow

    ui_batterylow = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_batterylow, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_batterylow, lv_color_hex(0xF09939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batterylow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_batterylow, lv_color_hex(0xEB6505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_batterylow, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image3

    ui_Image3 = lv_img_create(ui_batterylow);
    lv_img_set_src(ui_Image3, &ui_img_battery_low_png);

    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image3, 0);
    lv_obj_set_y(ui_Image3, 0);

    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_img_recolor(ui_Image3, lv_color_hex(0xFBB09E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Image3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label6

    ui_Label6 = lv_label_create(ui_batterylow);

    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label6, 1);
    lv_obj_set_y(ui_Label6, 40);

    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label6, "battery low");

}