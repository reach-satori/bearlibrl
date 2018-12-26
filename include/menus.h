#include "BearLibTerminal.h"
#include "consts.h"
#include "typedefs.h"
#include <string>
#include <stdio.h>
#include <assert.h>

void draw_outline(uint x, uint y, uint w, uint h, color_t color);
void text_center_popup(const char* str, int align, color_t outline_color);
void outlined_textbox(uint x, uint y, uint w, uint h, int align, const char* str, color_t outline_color);
