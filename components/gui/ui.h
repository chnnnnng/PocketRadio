// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: PocketRadio

#ifndef _POCKETRADIO_UI_H
#define _POCKETRADIO_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "ui_helpers.h"
#include "stdio.h"
#include "esp_log.h"
#include "fm.h"
#include "string.h"
#include "power.h"

//Globle ui handlers
extern lv_obj_t * ui_home;
extern lv_obj_t * ui_charge;
extern lv_obj_t * ui_battery;
extern lv_obj_t * ui_batterybar;
extern lv_obj_t * ui_batteryborder;
extern lv_obj_t * ui_time;
extern lv_obj_t * ui_Slider1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Image2;

extern lv_obj_t * ui_menu;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_ImgButton2;
extern lv_obj_t * ui_ImgButton1;
extern lv_obj_t * ui_ImgButton3;
extern lv_obj_t * ui_Label2;

extern lv_obj_t * ui_wifi;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_ddwifissid;
extern lv_obj_t * ui_tewifipasswd;
extern lv_obj_t * ui_btnwificancel;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_btnwificonnect;
extern lv_obj_t * ui_Label5;

extern lv_obj_t * ui_settings;
extern lv_obj_t * ui_listsettings;

extern lv_obj_t * ui_batterylow;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Label6;

//Globle input device handler
extern lv_indev_t * my_indev;

//globle group handler
extern lv_group_t * group_home;
extern lv_group_t * group_menu;
extern lv_group_t * group_settings;
extern lv_group_t * group_wifi;

//globle ui initializer
extern void ui_home_screen_init(void);
extern void ui_menu_screen_init(void);
extern void ui_settings_screen_init(void);
extern void ui_wifi_screen_init(void);
extern void ui_batterylow_screen_init(void);

//globle animation
extern void JumpIn_Animation(lv_obj_t * TargetObject, int delay);

//functions
void ui_init(void);
void load_page(lv_obj_t * page, lv_group_t * group);
void close_page(void);

typedef struct __page_stack_item{
    lv_obj_t * page;
    lv_group_t * group
} page_stack_item;


//resource declare
LV_IMG_DECLARE(ui_img_ic_charge_png);    // assets/ic_charge.png
LV_IMG_DECLARE(ui_img_battery_png);    // assets/battery.png
LV_IMG_DECLARE(ui_img_scansion_png);    // assets/scansion.png
LV_IMG_DECLARE(ui_img_radio_png);    // assets/Radio.png
LV_IMG_DECLARE(ui_img_collection_png);    // assets/collection.png
LV_IMG_DECLARE(ui_img_settings_png);    // assets/settings.png
LV_IMG_DECLARE(ui_img_love_png);    // assets/love.png
LV_IMG_DECLARE(ui_img_menu_png);    // assets/menu.png
LV_IMG_DECLARE(ui_img_battery_low_png);    // assets/battery_low.png

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
