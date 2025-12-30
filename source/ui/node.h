#pragma once
#include <stdint.h>

typedef struct UI_Node UI_Node;

typedef void (*UI_DrawFn)(UI_Node*);
typedef void (*UI_UpdateFn)(UI_Node*, float);

struct UI_Node {
    float x, y;
    float w, h;

    UI_Node* parent;
    UI_Node* first_child;
    UI_Node* next_sibling;

    UI_DrawFn draw;
    UI_UpdateFn update;

    uint32_t visible;
    uint32_t enabled;

    void* userdata;
};

UI_Node* ui_node_create();
void ui_node_add_child(UI_Node* parent, UI_Node* child);
void ui_node_update(UI_Node* node, float dt);
void ui_node_draw(UI_Node* node);

