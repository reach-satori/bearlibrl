#include "poscomp.h"
#include "comptags.h"
#include "typedefs.h"


Positional::Positional(uint x, uint y, uint codepoint) : BaseComponent(C_POSITIONAL), pos{x, y}, codepoint(codepoint) {}

Positional::Positional(void) : Positional(5, 5, 0xB0) {}

Positional::~Positional(void) {}

uint Positional::x(void) {
    return pos[0];
}

uint Positional::y(void) {
    return pos[1];
}

void Positional::move(uint x, uint y) {

}


