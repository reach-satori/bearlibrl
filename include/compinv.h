#pragma once
#include "compbase.h"
#include "comptags.h"
#include "entity.h"
#include "compcarr.h"
#include <memory>
#include <set>
#include <cassert>

struct Inventorial : public BaseComponent {
    float maxweight;
    float currload = 0;
    std::set<std::shared_ptr<Entity>> inventory = std::set<std::shared_ptr<Entity>>();

    int add_to_inventory(std::shared_ptr<Entity> picked_up);
    int remove_from_inventory(std::shared_ptr<Entity> item);
    Inventorial(void);
    Inventorial(float maxweight);
};
