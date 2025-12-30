#include "node.h"
#include <stdlib.h>
#include <string.h>

UI_Node* ui_node_create() {
    UI_Node* n = malloc(sizeof(UI_Node));
    memset(n, 0, sizeof(UI_Node));

    n->visible = 1;
    n->enabled = 1;

    return n;
}

void ui_node_add_child(UI_Node* parent, UI_Node* child) {
    if (!parent || !child) return;

    child->parent = parent;

    if (!parent->first_child) {
        parent->first_child = child;
    } else {
        UI_Node* n = parent->first_child;
        while (n->next_sibling)
            n = n->next_sibling;
        n->next_sibling = child;
    }
}

void ui_node_update(UI_Node* n, float dt) {
    if (!n || !n->enabled) return;

    if (n->update)
        n->update(n, dt);

    for (UI_Node* c = n->first_child; c; c = c->next_sibling)
        ui_node_update(c, dt);
}

void ui_node_draw(UI_Node* n) {
    if (!n || !n->visible) return;

    if (n->draw)
        n->draw(n);

    for (UI_Node* c = n->first_child; c; c = c->next_sibling)
        ui_node_draw(c);
}

