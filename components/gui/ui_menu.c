#include "ui.h"

lv_obj_t * ui_menu;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_ImgButton2;
lv_obj_t * ui_ImgButton1;
lv_obj_t * ui_ImgButton3;
lv_obj_t * ui_ImgButton4;
lv_obj_t * ui_Label2;

lv_group_t * group_menu;

static const char *TAG = "GUI_Menu";

void ui_menu_screen_init(void);
static void ui_event_menu(lv_event_t * e);
static void ui_menu_tile_event_cb(lv_event_t * e);


static void ui_event_menu(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        lv_label_set_text(ui_Label2, "Menu\n");
        JumpIn_Animation(ui_Label2, 0);
    }
}


lv_obj_t * tv;
lv_obj_t * tile1;
lv_obj_t * tile2;
lv_obj_t * tile3;
lv_obj_t * tile4;
void ui_menu_screen_init(void)
{
    // ui_menu
    ui_menu = lv_obj_create(NULL);

    group_menu = lv_group_create();

    tv = lv_tileview_create(ui_menu);
    lv_obj_set_style_bg_color(tv, lv_color_hex(0xF09939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tv, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(tv, lv_color_hex(0xEB6505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(tv, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
    ui_ImgButton1 = lv_btn_create(tile1);
    lv_obj_center(ui_ImgButton1);
    lv_obj_remove_style_all(ui_ImgButton1);
    lv_group_add_obj(group_menu,ui_ImgButton1);
    lv_obj_t * img1 = lv_img_create(tile1);
    lv_img_set_src(img1, &ui_img_radio_png);
    lv_obj_set_height(img1, 64);
    lv_obj_set_width(img1, LV_SIZE_CONTENT);
    lv_obj_center(img1);

    tile2 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP | LV_DIR_BOTTOM);
    ui_ImgButton2 = lv_btn_create(tile2);
    lv_obj_center(ui_ImgButton2);
    lv_obj_remove_style_all(ui_ImgButton2);
    lv_group_add_obj(group_menu,ui_ImgButton2);
    lv_obj_t * img2 = lv_img_create(tile2);
    lv_img_set_src(img2, &ui_img_scansion_png);
    lv_obj_set_height(img2, 64);
    lv_obj_set_width(img2, LV_SIZE_CONTENT);
    lv_obj_center(img2);

    tile3 = lv_tileview_add_tile(tv, 0, 2, LV_DIR_TOP | LV_DIR_BOTTOM);
    ui_ImgButton3 = lv_btn_create(tile3);
    lv_obj_center(ui_ImgButton3);
    lv_obj_remove_style_all(ui_ImgButton3);
    lv_group_add_obj(group_menu,ui_ImgButton3);
    lv_obj_t * img3 = lv_img_create(tile3);
    lv_img_set_src(img3, &ui_img_collection_png);
    lv_obj_set_height(img3, 64);
    lv_obj_set_width(img3, LV_SIZE_CONTENT);
    lv_obj_center(img3);

    tile4 = lv_tileview_add_tile(tv, 0, 3, LV_DIR_TOP);
    ui_ImgButton4 = lv_btn_create(tile4);
    lv_obj_center(ui_ImgButton4);
    lv_obj_remove_style_all(ui_ImgButton4);
    lv_group_add_obj(group_menu,ui_ImgButton4);
    lv_obj_t * img4 = lv_img_create(tile4);
    lv_img_set_src(img4, &ui_img_settings_png);
    lv_obj_set_height(img4, 64);
    lv_obj_set_width(img4, LV_SIZE_CONTENT);
    lv_obj_center(img4);

    lv_obj_add_event_cb(ui_ImgButton1, ui_menu_tile_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButton2, ui_menu_tile_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButton3, ui_menu_tile_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButton4, ui_menu_tile_event_cb, LV_EVENT_ALL, NULL);

    // ui_Label2
    ui_Label2 = lv_label_create(ui_menu);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_Label2, -57);
    lv_obj_set_y(ui_Label2, -46);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_menu, ui_event_menu, LV_EVENT_ALL, NULL);
}


void ui_menu_tile_event_cb(lv_event_t * e)
{
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_ImgButton1) lv_obj_set_tile(tv, tile1, LV_ANIM_ON);
        if(ta == ui_ImgButton2) lv_obj_set_tile(tv, tile2, LV_ANIM_ON);
        if(ta == ui_ImgButton3) lv_obj_set_tile(tv, tile3, LV_ANIM_ON);
        if(ta == ui_ImgButton4) lv_obj_set_tile(tv, tile4, LV_ANIM_ON);
    }
    
    if(code == LV_EVENT_CLICKED && indev_type == LV_INDEV_TYPE_ENCODER) {
        if(ta == ui_ImgButton1) {
            load_page(ui_home, group_home);
        }
        if(ta == ui_ImgButton2)  {
            load_page(ui_home, group_home);
        }
        if(ta == ui_ImgButton3)  {
            load_page(ui_home, group_home);
        }
        if(ta == ui_ImgButton4)  {
            load_page(ui_settings, group_settings);
        }
    }
}