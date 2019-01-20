#pragma once
#include "BearLibTerminal.h"
#include "consts.h"
#include "typedefs.h"
#include "compinv.h"
#include <stdio.h>
#include <assert.h>
#include <string>
#include <stdarg.h>

class txtlog {
    std::vector<std::string> txt = std::vector<std::string>(1000);
    const int maxsize = 10000;
    public:
        void log(std::string);
        std::string const * retrieve_last_n(int n) const;
};

struct ItemMenu {
    std::vector<std::weak_ptr<Entity>> items = std::vector<std::weak_ptr<Entity>>();
    int p_maxweight = 100;
    int p_currload = 0;
    int currpos = 0;
};

struct CActMenu {
    const std::vector<const char*> opts = {
        "Jump",
        "Do nothing"
    };
    int currpos = 0;
};


void draw_outline(uint x, uint y, uint w, uint h, color_t color);
void text_center_popup(const char* str, int align, color_t outline_color);
void outlined_textbox(uint x, uint y, uint w, uint h, int align, const char* str, color_t outline_color);
void draw_menus();
void logbox();
void current_menu();
std::string txt(std::string fmt, ...);
void You(const char* in);
void tolog(const char* in);
void item_menu();
void menu_scroll(int in);
void pickup_menu();
void inventory_menu();
void common_action_menu();
std::shared_ptr<Entity> retrieve_chosen_item();
void item_menu_update( std::set<std::shared_ptr<Entity>> const&, int, int );

