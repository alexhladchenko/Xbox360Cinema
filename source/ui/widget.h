#pragma once

typedef enum {
    UI_WIDGET_NONE,
    UI_WIDGET_BUTTON
} UIWidgetType;

typedef struct UIWidget {
    UIWidgetType type;

    int x, y;
    int w, h;

    void (*draw)(struct UIWidget*);
    void (*update)(struct UIWidget*);

    void *userdata;
} UIWidget;

