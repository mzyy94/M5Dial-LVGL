// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#include <M5Unified.hpp>
#include <freertos/FreeRTOS.h>
#include <lvgl.h>
#include "M5Dial-LVGL.h"

void qr_code(void)
{
    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_GREY, 1);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_ORANGE, 4);

    lv_obj_set_style_bg_color(lv_screen_active(), bg_color, LV_PART_MAIN);

    lv_obj_t *qr = lv_qrcode_create(lv_screen_active());
    lv_qrcode_set_size(qr, 150);
    lv_qrcode_set_dark_color(qr, fg_color);
    lv_qrcode_set_light_color(qr, bg_color);

    const char *data = "https://github.com/mzyy94/M5Dial-LVGL";
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);

    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);
}

void main_task(void *)
{
    m5dial_lvgl_init();
    qr_code();

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
