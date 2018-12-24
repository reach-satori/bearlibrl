#pragma once
#include <vector>
#include <memory>
#include "basecomp.h"


struct Entity {
        std::vector<unsigned int> tags;
        std::vector<std::shared_ptr<BaseComponent>> components;

        void add_component(std::shared_ptr<BaseComponent> comp);
};
