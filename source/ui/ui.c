#include "ui.h"

static UIWidget *widgets[UI_MAX_WIDGETS];
static int widget_count = 0;

void ui_init(void) {
    widget_count = 0;
}

void ui_add(UIWidget *w) {
    if (widget_count < UI_MAX_WIDGETS)
        widgets[widget_count++] = w;
}

void ui_draw(void) {
    for (int i = 0; i < widget_count; i++)
        widgets[i]->draw(widgets[i]);
}

void ui_update(void) {
    for (int i = 0; i < widget_count; i++)
        widgets[i]->update(widgets[i]);
}

