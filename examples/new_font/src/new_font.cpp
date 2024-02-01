// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#include <M5Unified.hpp>
#include <freertos/FreeRTOS.h>
#include <lvgl.h>
#include "M5Dial-LVGL.h"

LV_FONT_DECLARE(BigShouldersStencilDisplay_40)

void new_font(void)
{
    lv_obj_set_style_bg_color(lv_screen_active(), lv_palette_darken(LV_PALETTE_ORANGE, 4), LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_font(label, &BigShouldersStencilDisplay_40, 0);
    lv_label_set_text(label, "M5Dial LVGL");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_white(), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void main_task(void *)
{
    m5dial_lvgl_init();
    new_font();

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
