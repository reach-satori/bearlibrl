#include "menus.h"


void draw_outline(uint x, uint y, uint w, uint h, color_t color) {

    color_t cstorage = terminal_state(TK_COLOR);
    terminal_color(color);
    terminal_layer(TEXTBOXES_LAYER);

    terminal_put(x, y, 0x250f);
    terminal_put(x, y+h-1, 0x2517);
    terminal_put(x+w-1, y+h-1, 0x251b);
    terminal_put(x+w-1, y, 0x2513);
    for (uint i = 1; i <= w-2; i++) {
        terminal_put(x+i, y, 0x2501);
        terminal_put(x+i, y+h-1, 0x2501);
    }
    for (uint i = 1; i <= h-2; i++) {
        terminal_put(x, y+i, 0x2503);
        terminal_put(x+w-1, y+i, 0x2503);
    }

    terminal_color(cstorage);
    terminal_layer(DEFAULT_LAYER);
}

void text_center_popup(const char* str, int align) {
    dimensions_t textsize = terminal_measure(str);
    assert(CONSOLE_WIDTH > 10);
    assert(CONSOLE_HEIGHT > 4);
    if (textsize.width > CONSOLE_WIDTH - 10) {
        textsize = terminal_measure_ext(CONSOLE_WIDTH - 10, CONSOLE_HEIGHT-4, str);
    }
    int width = textsize.width, height = textsize.height;
    int x = (CONSOLE_WIDTH/2 - width/2)-1;
    int y = (CONSOLE_HEIGHT/2 - height/2)-1;
    terminal_clear_area(x, y, width+2, height+2);//+2 means it clears the outline area as well
    draw_outline(x, y, width+2, height+2, 0xffff0000);//same here
    terminal_print_ext(x+1, y+1, width, height, align, str);// +1 in x y so it doesn;t go on top of the outline, not sure why

}
