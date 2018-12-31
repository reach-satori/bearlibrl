#pragma once
#include "BearLibTerminal.h"
#include "consts.h"
#include "typedefs.h"
#include "compinv.h"
#include <stdio.h>
#include <assert.h>
#include <string>
#include <stdarg.h>
#include <queue>

class txtlog {
    std::vector<std::string> txt = std::vector<std::string>(1000);
    const int maxsize = 10000;
    public:
        void log(std::string);
        std::string const * retrieve_last_n(int n) const;
};


void draw_outline(uint x, uint y, uint w, uint h, color_t color);
void text_center_popup(const char* str, int align, color_t outline_color);
void outlined_textbox(uint x, uint y, uint w, uint h, int align, const char* str, color_t outline_color);
void draw_menus();
void logbox();
void current_menu();
std::string txt(const char* fmt, ...);
void You(const char* in);
void tolog(const char* in);
void item_menu();
void pickup_menu();
void inventory_menu();

