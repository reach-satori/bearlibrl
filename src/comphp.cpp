#include "comphp.h"

Vital::Vital(uint maxhp) : BaseComponent(C_VITAL), maxhp(maxhp) {}
Vital::Vital(void) : Vital(100) {}
Vital::~Vital(void) {};
