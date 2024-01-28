// SPDX-License-Identifier: MIT

#include <M5Unified.hpp>
#include <freertos/FreeRTOS.h>
#include <lvgl.h>
#include "M5Dial-LVGL.h"

void hello_world(void)
{
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_white(), LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello M5Dial");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_black(), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void main_task(void *)
{
    m5dial_lvgl_init();
    hello_world();

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
