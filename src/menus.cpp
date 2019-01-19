#include "menus.h"
#include "globals.h"

static txtlog glog;
static ItemMenu imenu;
static CActMenu cactmenu;

void item_menu_update(std::set<std::shared_ptr<Entity>> const &items, int maxw, int currw) {
    std::vector<std::weak_ptr<Entity>> wkptrs;
    for (auto i: items) {
        if (i->get_component<Carrial>(C_CARR) != nullptr)
            wkptrs.push_back(std::weak_ptr<Entity>(i));
    }
    imenu.items = wkptrs;
    imenu.p_maxweight = maxw;
    imenu.p_currload = currw;
    imenu.currpos = 0;
}

void menu_scroll(int in) {
    imenu.currpos = clamp(imenu.currpos + in, 0, imenu.items.size() - 1);
    cactmenu.currpos = clamp(cactmenu.currpos + in, 0, cactmenu.opts.size() - 1);
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

std::string txt( std::string fmt, ... ) {
    char buf[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buf, 1024, fmt.c_str(), argptr);
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
    constexpr int w = 3 * CONSOLE_WIDTH/4, h = 3 * SCREEN_HEIGHT / 4;
    constexpr int x = (CONSOLE_WIDTH/2 - w/2)-1;
    constexpr int y = (SCREEN_HEIGHT/2 - h/2)-1;
    terminal_clear_area(x, y, w, h);
    draw_outline(x, y, w, h, 0xffffffff);
    auto &items = imenu.items;
    auto lim = items.size();

    for (int i = 0; i < lim; i++) {
        auto iname = items[i].lock()->name.c_str();
        auto toprint = i == imenu.currpos ? txt("[color=yellow]%s[/color]", iname) : txt(iname);
        terminal_print(x+1, y+i+1, toprint.c_str());
    }
}

void inventory_menu() {
        constexpr int w = 3 * CONSOLE_WIDTH/4, h = 3 * SCREEN_HEIGHT / 4;
        constexpr int x = (CONSOLE_WIDTH/2 - w/2)-1;
        constexpr int y = (SCREEN_HEIGHT/2 - h/2)-1;
        terminal_clear_area(x, y, w, h);
        draw_outline(x, y, w, h, 0xffffffff);
        auto &items = imenu.items;
        auto lim = items.size();
        for (int i = 0; i < lim; i++) {
            auto iname = items[i].lock()->name.c_str();
            auto toprint = i == imenu.currpos ? txt("[color=yellow]%s[/color]", iname) : txt(iname);
            terminal_print(x+1, y+i+1, toprint.c_str());
    }
}

void common_action_menu() {
        constexpr int w = 3 * CONSOLE_WIDTH/4, h = 3 * SCREEN_HEIGHT / 4;
        constexpr int x = (CONSOLE_WIDTH/2 - w/2)-1;
        constexpr int y = (SCREEN_HEIGHT/2 - h/2)-1;
        terminal_clear_area(x, y, w, h);
        draw_outline(x, y, w, h, 0xffffffff);
        for (int i = 0; i < cactmenu.opts.size(); i++) {
            auto toprint = i == cactmenu.currpos ? txt("[color=yellow]%s[/color]", cactmenu.opts[i]) : txt(cactmenu.opts[i]);
            terminal_print(x+1, y+i+1, toprint.c_str());
    }
}

void current_menu() {
    switch (input.domainstack.top()) {
        case CMD_PICKUP:
            pickup_menu();
            break;
        case CMD_INVENTORY:
            inventory_menu();
            break;
        case CMD_COMMON_ACTION:
            common_action_menu();
            break;
        default:
            break;
    }
}

void logbox() {
    static constexpr auto boxheight = LOGBOX_HEIGHT;
    static constexpr auto startheight = CONSOLE_HEIGHT-boxheight;
    std::string const *t = glog.retrieve_last_n(boxheight - 2);
    terminal_clear_area(0, startheight, CONSOLE_WIDTH, boxheight);
    for (int i = 0; i < boxheight-2 ; i++) {
        terminal_print(3, startheight + 1 + i, (t+i)->c_str());
    }
    draw_outline(0, startheight, CONSOLE_WIDTH, LOGBOX_HEIGHT, 0xffffffff);
}

void draw_menus() {
    logbox();
    /* statbox(); */
    current_menu();
}

std::shared_ptr<Entity> retrieve_chosen_item() {
    if (imenu.items.empty() || imenu.currpos > imenu.items.size()-1) return nullptr;
    auto chosen = imenu.items[imenu.currpos];
    return chosen.lock();
}

