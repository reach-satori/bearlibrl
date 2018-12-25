#include "poscomp.h"
#include "comptags.h"
#include "typedefs.h"


Positional::Positional(uint x, uint y) : BaseComponent(C_POSITIONAL), pos{x, y} {}

Positional::Positional(void) : BaseComponent(C_POSITIONAL), pos{5, 5} {}

Positional::~Positional(void) {};

uint Positional::x(void) {
    return pos[0];
}

uint Positional::y(void) {
    return pos[1];
}

void Positional::move(uint x, uint y) {

}


