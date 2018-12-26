#include "carrcomp.h"



Carrial::Carrial(float weight, std::weak_ptr<Inventorial> invptr ) : BaseComponent(C_CARR), weight(weight), invptr(invptr) {}

Carrial::Carrial(void) : Carrial(1.f, std::weak_ptr<Inventorial>()) {}




