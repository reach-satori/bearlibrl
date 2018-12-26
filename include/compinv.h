#pragma once
#include "compbase.h"
#include "comptags.h"
#include "entity.h"
#include "compcarr.h"
#include <memory>
#include <vector>

struct Inventorial : public BaseComponent {
    float maxweight;
    float currload = 0;
    std::vector<std::shared_ptr<Entity>> inventory = std::vector<std::shared_ptr<Entity>>();

    int pickup(std::shared_ptr<Entity> picked_up);
    Inventorial(void);
    Inventorial(float maxweight);
};
