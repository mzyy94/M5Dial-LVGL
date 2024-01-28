// SPDX-License-Identifier: MIT

#include <M5Unified.hpp>
#include <lvgl.h>
#include "M5Dial-LVGL.h"

static void arc_event_cb(lv_event_t *e)
{
    lv_indev_t *indev = lv_indev_active();
    if (indev == nullptr)
        return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *arc = (lv_obj_t *)lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *label = lv_obj_get_child(arc, 0);
        lv_label_set_text_fmt(label, "%" LV_PRId32, lv_arc_get_value(arc));
    }
    else if (code == LV_EVENT_RELEASED || indev_type == LV_INDEV_TYPE_POINTER)
    {
        // Re-enable editing mode after touch input
        lv_group_t *group = lv_obj_get_group(arc);
        lv_group_set_editing(group, true);
    }
}

void dial_arc(void)
{
    lv_obj_t *arc = lv_arc_create(lv_screen_active());
    lv_obj_set_size(arc, 200, 200);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_range(arc, 0, 10);
    lv_arc_set_value(arc, 4);
    lv_obj_center(arc);

    lv_obj_t *label = lv_label_create(arc);
    lv_label_set_text_fmt(label, "%" LV_PRId32, lv_arc_get_value(arc));
    lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
    // lv_obj_set_style_transform_scale(label, 512, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_group_t *group = lv_group_create();
    // lv_group_set_default(group);
    lv_group_add_obj(group, arc);
    lv_group_set_editing(group, true);

    for (lv_indev_t *indev = lv_indev_get_next(nullptr); indev != nullptr; indev = lv_indev_get_next(indev))
    {
        if (lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER)
        {
            lv_indev_set_group(indev, group);
            break;
        }
    }

    lv_obj_add_event_cb(arc, arc_event_cb, LV_EVENT_ALL, nullptr);
}

int main_task(bool *running)
{
    m5dial_lvgl_init();
    dial_arc();

    for (; *running;)
    {
        m5dial_lvgl_next();
    }
    return 0;
}

int main(int, char **)
{
    return lgfx::Panel_sdl::main(main_task, 128);
}
