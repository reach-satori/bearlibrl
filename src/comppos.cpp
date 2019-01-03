#include "comppos.h"
#include "globals.h"

Positional::Positional(uint x, uint y, uint codepoint) : BaseComponent(C_POSITIONAL), pos{x, y}, codepoint(codepoint) {
    setpos(x, y);
}

Positional::Positional(void) : Positional(5, 5, 0xBF) {}

void Positional::setpos(int x, int y) {
    x = clamp(x, 0, 10000);
    y = clamp(y, 0, 10000);
    auto& lvl = levelmanager->get_change_currlvl();
    lvl.tiles[pos[0]][pos[1]].ents.erase(parent.lock());
    pos[0] = x;
    pos[1] = y;
    lvl.tiles[x][y].ents.insert(parent.lock());
}

Positional::~Positional(void) {}

uint Positional::x(void) const {
    return pos[0];
}

uint Positional::y(void) const {
    return pos[1];
}



