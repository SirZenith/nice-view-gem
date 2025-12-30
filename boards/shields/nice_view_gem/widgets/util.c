#include <zephyr/kernel.h>
#include "util.h"
#include <ctype.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[]) {
    static lv_color_t cbuf_tmp[BUFFER_SIZE * BUFFER_SIZE];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));

    lv_image_dsc_t img;
    img.data = (void *)cbuf_tmp;
    img.header.cf = LV_COLOR_FORMAT_NATIVE;
    img.header.w = BUFFER_SIZE;
    img.header.h = BUFFER_SIZE;

    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);
    /* lv_canvas_transform(canvas, &img, 900, LV_ZOOM_NONE, -1, 0, BUFFER_SIZE / 2, BUFFER_SIZE / 2,
                        false); */
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.rotation = 900;
    img_dsc.src = &img;
    img_dsc.pivot.x = BUFFER_SIZE / 2;
    img_dsc.pivot.y = BUFFER_SIZE / 2;

    lv_area_t coords_img = {0, 0, BUFFER_SIZE - 1, BUFFER_SIZE - 1};
    lv_draw_image(&layer, &img_dsc, &coords_img);

    lv_canvas_finish_layer(canvas, &layer);
}

void fill_background(lv_obj_t *canvas) {
    // lv_draw_rect_dsc_t rect_black_dsc;
    // init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

    // lv_draw_rect(canvas, 0, 0, BUFFER_SIZE, BUFFER_SIZE, &rect_black_dsc);
    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font,
                    lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
}