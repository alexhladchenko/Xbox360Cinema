#include "widget.h"

void ui_widget_draw(UIWidget *w) {
    if (w && w->draw)
        w->draw(w);
}

void ui_widget_update(UIWidget *w) {
    if (w && w->update)
        w->update(w);
}

