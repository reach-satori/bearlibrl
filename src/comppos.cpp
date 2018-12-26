#include "comppos.h"
#include "globals.h"


Positional::Positional(uint x, uint y, uint codepoint) : BaseComponent(C_POSITIONAL), pos{x, y}, codepoint(codepoint) {}

Positional::Positional(void) : Positional(5, 5, 0xBF) {}

Positional::~Positional(void) {}

uint Positional::x(void) {
    return pos[0];
}

uint Positional::y(void) {
    return pos[1];
}

void Positional::move(uint x, uint y) {
    if (cmap->is_passable(x, y)) {
        pos[0] = x;
        pos[1] = y;
    }
}

void Positional::draw() {
    terminal_put(pos[0], pos[1], codepoint);
}


