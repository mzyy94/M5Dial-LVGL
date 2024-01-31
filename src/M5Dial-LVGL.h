// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#ifndef M5DIAL_LVGL_H
#define M5DIAL_LVGL_H

#ifndef LV_LVGL_H_INCLUDE_SIMPLE
#define LV_LVGL_H_INCLUDE_SIMPLE
#endif

#include <M5Unified.hpp>
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

inline void m5dial_lvgl_init()
{
    M5.begin();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
}

inline void m5dial_lvgl_next()
{
    M5.update();
    uint32_t wait_ms = lv_timer_handler();
    M5.delay(wait_ms);
    lv_tick_inc(wait_ms);
}

#endif
