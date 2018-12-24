#include "poscomp.h"
#include "comptags.h"

Positional::Positional(void) : BaseComponent(C_POSITIONAL), pos{5, 5} {}

Positional::Positional(unsigned int x, unsigned int y) : BaseComponent(C_POSITIONAL), pos{x, y} {}

unsigned int Positional::x(void) {
    return pos[0];
}

unsigned int Positional::y(void) {
    return pos[1];
}
