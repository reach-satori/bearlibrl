#include "comppos.h"
#include "globals.h"

Positional::Positional(uint x, uint y, uint codepoint) : BaseComponent(C_POSITIONAL), pos{x, y}, codepoint(codepoint) {}

Positional::Positional(void) : Positional(5, 5, 0xBF) {}

void Positional::setpos(int x, int y) {
    pos[0] = x;
    pos[1] = y;
}

Positional::~Positional(void) {}

uint Positional::x(void) const {
    return pos[0];
}

uint Positional::y(void) const {
    return pos[1];
}



