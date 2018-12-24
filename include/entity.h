#pragma once
#include <vector>
#include <memory>
#include "basecomp.h"


struct Entity {
        std::vector<std::shared_ptr<BaseComponent>> components;
};
