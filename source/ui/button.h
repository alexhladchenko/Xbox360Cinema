#pragma once
#include "widget.h"

typedef struct UIButton {
    UIWidget base;
    const char *text;

    void (*on_click)(void);
} UIButton;

UIButton* ui_button_create(
    int x, int y, int w, int h,
    const char *text,
    void (*on_click)(void)
);

