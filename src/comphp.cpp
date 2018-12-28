#include "comphp.h"

Vital::Vital(uint maxhp) : BaseComponent(C_VITAL, C_EMPTY), maxhp(maxhp) {}
Vital::Vital(void) : Vital(100) {}
Vital::~Vital(void) {};
