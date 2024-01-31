// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#include "lv_port_disp.h"
#include <stdbool.h>
#include <M5Unified.hpp>

#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 240

static void disp_init(void);
static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

void lv_port_disp_init(void)
{
    disp_init();

    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];
    lv_display_set_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void disp_init(void)
{
}

volatile bool disp_flush_enabled = true;

void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

static void disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map)
{
    if (disp_flush_enabled)
    {
        int32_t width = area->x2 - area->x1 + 1;
        int32_t height = area->y2 - area->y1 + 1;
        M5.Display.setAddrWindow(area->x1, area->y1, width, height);
        M5.Display.pushPixels((uint16_t *)px_map, width * height, true);
    }

    M5.Display.waitDisplay();
    lv_display_flush_ready(disp_drv);
}
