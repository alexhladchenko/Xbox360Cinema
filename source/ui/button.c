#include "button.h"
#include <stdio.h>
#include <stdlib.h>

static void button_draw(UIWidget *w) {
    UIButton *btn = (UIButton*)w;
    printf("[BUTTON] %s at %d,%d (%dx%d)\n",
           btn->text, w->x, w->y, w->w, w->h);
}

static void button_update(UIWidget *w) {
    // пока пусто
}

UIButton* ui_button_create(
    int x, int y, int w, int h,
    const char *text,
    void (*on_click)(void)
) {
    UIButton *btn = calloc(1, sizeof(UIButton));

    btn->base.type = UI_WIDGET_BUTTON;
    btn->base.x = x;
    btn->base.y = y;
    btn->base.w = w;
    btn->base.h = h;
    btn->base.draw = button_draw;
    btn->base.update = button_update;

    btn->text = text;
    btn->on_click = on_click;

    return btn;
}

