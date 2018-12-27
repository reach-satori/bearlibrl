#include "compact.h"


Actional::Actional(int spd) : BaseComponent(C_ACT), base_speed(spd), speed(spd), tick(spd) {}
Actional::Actional() : Actional(1000) {}
void Actional::add_to_tick(int speedin) {
    tick += speedin;
}

