// SPDX-License-Identifier: MIT

#include <M5Unified.hpp>
#include <freertos/FreeRTOS.h>
#include <lvgl.h>
#include "M5Dial-LVGL.h"

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);

    static uint32_t cnt = 1;

    if (code == LV_EVENT_CLICKED)
    {
        lv_label_set_text_fmt(label, "%" LV_PRIu32, cnt);
        cnt++;
    }
    else if (code == LV_EVENT_LONG_PRESSED_REPEAT)
    {
        lv_label_set_text(label, "0");
        cnt = 0;
    }
}

void touch_button(void)
{
    lv_obj_t *btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 100, 50);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Touch me!");
    lv_obj_center(label);
}

void main_task(void *)
{
    m5dial_lvgl_init();
    touch_button();

    for (;;)
    {
        m5dial_lvgl_next();
    }
    vTaskDelete(nullptr);
}

extern "C"
{
    void app_main()
    {
        xTaskCreatePinnedToCore(main_task, "main_task", 8192, nullptr, 1, nullptr, 1);
    }
}
