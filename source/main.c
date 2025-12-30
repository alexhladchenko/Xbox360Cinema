#include <stdio.h>
#include "ui/ui.h"
#include "ui/button.h"

void on_play(void) {
    printf("PLAY pressed!\n");
}

int main(void) {
    printf("MovieCore GUI test\n");

    ui_init();

    UIButton *play = ui_button_create(
        540, 260, 200, 60,
        "Play",
        on_play
    );

    ui_add((UIWidget*)play);

    // эмуляция main loop
    for (int i = 0; i < 1; i++) {
        ui_update();
        ui_draw();
    }

    return 0;
}

