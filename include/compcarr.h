#pragma once
#include "compbase.h"
#include "comptags.h"
#include "fdecs.h"


//items never begin inside inventories
//stuff initialization will have to include "picking up"
struct Carrial : BaseComponent {
    float weight;
    std::weak_ptr<Entity> invptr = std::weak_ptr<Entity>();

    Carrial(void);
    Carrial(float weight);
};
