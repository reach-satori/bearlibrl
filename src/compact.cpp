#include "compact.h"


Actional::Actional(int spd) : BaseComponent(C_ACT), base_speed(spd), speed(spd), tick(spd) {}
Actional::Actional() : Actional(1000) {}

