#include "menus.h"
#include "globals.h"

static txtlog glog;
static ItemMenu imenu;

void item_menu_update(std::vector<Carrial const *> items, int max, int curr) {
    imenu.items = items;
    imenu.p_maxweight = max;
    imenu.p_currload = curr;
}

void txtlog::log(std::string str) {
    if (txt.size() > maxsize) {
        txt.erase(txt.begin(), txt.begin()+1000);
    }
    txt.push_back(str);
}

std::string const * txtlog::retrieve_last_n(int n) const {
    return &txt.at(txt.size()-n);
}

std::string txt( const char* fmt, ... ) {
    char buf[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buf, 1024, fmt, argptr);
    va_end(argptr);
    return std::string(buf);
}

void tolog(const char* in) {
    glog.log(in);
}

void You(const char* in) {
    tolog(txt("%s %s", "You", in).c_str());
}

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

void text_center_popup(const char* str, int align, color_t outline_color) {
    dimensions_t textsize = terminal_measure(str);
    assert(CONSOLE_WIDTH > 10);
    assert(CONSOLE_HEIGHT > 4);
    if (textsize.width > CONSOLE_WIDTH - 10) {
        textsize = terminal_measure_ext(CONSOLE_WIDTH - 10, CONSOLE_HEIGHT-4, str);
    }
    int w = textsize.width, h = textsize.height;
    int x = (CONSOLE_WIDTH/2 - w/2)-1;
    int y = (CONSOLE_HEIGHT/2 - h/2)-1;

    outlined_textbox(x, y, w+2, h+2, align, str, outline_color);
}

//attn: width and height include outline space!
void outlined_textbox(uint x, uint y, uint w, uint h, int align, const char* str, color_t outline_color) {
    terminal_clear_area(x, y, w, h);
    draw_outline(x, y, w, h, outline_color);
    terminal_print_ext(x+1, y+1, w-2, h-2, align, str);
}

void pickup_menu() {
    constexpr int w = 80, h = 20;
    constexpr int x = (CONSOLE_WIDTH/2 - w/2)-1;
    constexpr int y = (CONSOLE_HEIGHT/2 - h/2)-1;
    terminal_clear_area(x, y, w, h);
    draw_outline(x, y, w, h, 0xffffffff);
}

void inventory_menu() {

}

void current_menu() {
    switch (input.domainstack.top()) {
        case CMD_PICKUP:
            pickup_menu();
            break;
    }
}

void logbox() {
    static constexpr auto boxheight = 8;
    static constexpr auto startheight = CONSOLE_HEIGHT-boxheight;
    std::string const *t = glog.retrieve_last_n(boxheight - 2);
    terminal_clear_area(0, startheight, CONSOLE_WIDTH, boxheight);
    for (int i = 0; i < boxheight-2 ; i++) {
        terminal_print(3, startheight + 1 + i, (t+i)->c_str());
    }
    draw_outline(0, startheight, CONSOLE_WIDTH, 8, 0xffffffff);
}

void draw_menus() {
    logbox();
    /* statbox(); */
    current_menu();
}

