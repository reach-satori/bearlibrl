#include "actcomp.h"
#include "comptags.h"


Action::Action(int spd) : BaseComponent(C_ACT), base_speed(spd), speed(spd), tick(spd) {}
Action::Action() : Action(1000) {}

