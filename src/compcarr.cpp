#include "compcarr.h"



Carrial::Carrial(float weight) : BaseComponent(C_CARR), weight(weight) {}
Carrial::Carrial(float weight, COMPONENT_TAG tag) : BaseComponent(tag), weight(weight) {}

Carrial::Carrial(void) : Carrial(1.f) {}

/////////////

EquipCarrial::EquipCarrial(float weight) : Carrial(weight, C_CARR_EQUIP) {}




