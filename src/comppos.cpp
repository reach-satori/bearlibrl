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
    if (levelmanager->get_const_currlvl()->is_passable(x, y)) {
        pos[0] = x;
        pos[1] = y;
    }
}

std::pair<int, int> Positional::get_pos(void) const {
    return std::make_pair(pos[0], pos[1]);
}


