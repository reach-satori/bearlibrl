#include "comppos.h"
#include "globals.h"

Positional::Positional(int f, int x, int y, uint codepoint) : BaseComponent(C_POSITIONAL), pos{f, x, y}, codepoint(codepoint) {
    setpos(f, x, y);
}

Positional::Positional(void) : Positional(0, 5, 5, 0xBF) {}

void Positional::setpos(int f, int x, int y) {
    Level& lvl = levelmanager->get_currlvl();
    auto pptr = parent.lock();
    x = clamp(x, 0, lvl.width-1);
    y = clamp(y, 0, lvl.height-1);
    f = clamp(f, 0, lvl.depth-1);
    lvl.tiles[pos[0]][pos[1]][pos[2]].ents.erase(pptr);
    pos[0] = f;
    pos[1] = x;
    pos[2] = y;
    lvl.at(f, x, y)->ents.insert(pptr);
}

Positional::~Positional(void) {}

uint Positional::x(void) const {
    return pos[1];
}

uint Positional::y(void) const {
    return pos[2];
}
uint Positional::f(void) const {
    return pos[0];
}



