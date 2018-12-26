#pragma once
#include "basecomp.h"
#include "comptags.h"
#include "entity.h"
#include "carrcomp.h"
#include <memory>
#include <vector>


struct Inventorial : public BaseComponent {
    float maxweight;
    float currload = 0;
    std::vector<std::shared_ptr<Entity>> inventory = std::vector<std::shared_ptr<Entity>>();

    void pickup(std::shared_ptr<Entity> picked_up);
    Inventorial(void);
    Inventorial(float maxweight);
};
