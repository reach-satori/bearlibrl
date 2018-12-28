#include "compcarr.h"



Carrial::Carrial(float weight) : BaseComponent(C_CARR, C_EMPTY), weight(weight) {}
Carrial::Carrial(float weight, COMPONENT_SUBTAG subtag) : BaseComponent(C_CARR, subtag), weight(weight) {}

Carrial::Carrial(void) : Carrial(1.f) {}

/////////////

EquipCarrial::EquipCarrial(float weight) : Carrial(weight, C_CARR_EQUIP) {}




