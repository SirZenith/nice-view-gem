#include <zephyr/kernel.h>
#include "profile.h"

LV_IMG_DECLARE(profiles);

static void draw_inactive_profiles(lv_obj_t *canvas, const struct status_state *state) {
    draw_image(canvas, profiles, 18, 129 + BUFFER_OFFSET_BOTTOM);
}

static void draw_active_profile(lv_obj_t *canvas, const struct status_state *state) {
    int offset = state->active_profile_index * 7;
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    lv_area_t rect = {18 + offset, 129 + BUFFER_OFFSET_BOTTOM, 3, 3};
    lv_draw_rect(&layer, &rect_white_dsc, &rect);
    // lv_canvas_draw_rect(canvas, 18 + offset, 129 + BUFFER_OFFSET_BOTTOM, 3, 3, &rect_white_dsc);
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_inactive_profiles(canvas, state);
    draw_active_profile(canvas, state);
}