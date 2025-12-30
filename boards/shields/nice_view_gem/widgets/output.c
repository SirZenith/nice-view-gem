#include <zephyr/kernel.h>
#include "output.h"
#include "../assets/custom_fonts.h"
#include "draw/lv_draw_rect.h"

LV_IMG_DECLARE(bt_no_signal);
LV_IMG_DECLARE(bt_unbonded);
LV_IMG_DECLARE(bt);
LV_IMG_DECLARE(usb);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) { draw_image(canvas, usb, 45, 2); }

static void draw_ble_unbonded(lv_obj_t *canvas) { draw_image(canvas, bt_unbonded, 44, 0); }
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) { draw_image(canvas, bt_no_signal, 49, 0); }

static void draw_ble_connected(lv_obj_t *canvas) { draw_image(canvas, bt, 49, 0); }

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    draw_label(canvas, &label_dsc, "SIG", 0, 1);
    // lv_canvas_draw_text(canvas, 0, 1, 25, &label_dsc, "SIG");

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    lv_area_t rect = {43, 0, 24, 15};
    lv_draw_rect(&layer, &rect_white_dsc, &rect);
    // lv_canvas_draw_rect(canvas, 43, 0, 24, 15, &rect_white_dsc);
    lv_canvas_finish_layer(canvas, &layer);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    switch (state->selected_endpoint.transport) {
    case ZMK_TRANSPORT_USB:
        draw_usb_connected(canvas);
        break;

    case ZMK_TRANSPORT_BLE:
        if (state->active_profile_bonded) {
            if (state->active_profile_connected) {
                draw_ble_connected(canvas);
            } else {
                draw_ble_disconnected(canvas);
            }
        } else {
            draw_ble_unbonded(canvas);
        }
        break;
    }
#else
    if (state->connected) {
        draw_ble_connected(canvas);
    } else {
        draw_ble_disconnected(canvas);
    }
#endif
}