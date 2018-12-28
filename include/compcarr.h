#pragma once
#include "compbase.h"
#include "comptags.h"
#include "slottags.h"


//items never begin inside inventories
//stuff initialization will have to include "picking up"
struct Carrial : BaseComponent {
    float weight;
    std::weak_ptr<Entity> invptr = std::weak_ptr<Entity>();

    Carrial(void);
    Carrial(float weight);
    Carrial(float weight, COMPONENT_SUBTAG subtag);
};

struct EquipCarrial : Carrial {
    EQUIP_SLOT_TAG slot;
    EquipCarrial(float weight);
    bool equipped = false;

    EquipCarrial();
};
