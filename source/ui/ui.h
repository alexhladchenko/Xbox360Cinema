#pragma once
#include "widget.h"

#define UI_MAX_WIDGETS 32

void ui_init(void);
void ui_add(UIWidget *w);
void ui_draw(void);
void ui_update(void);

