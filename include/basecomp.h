#pragma once
#include <memory>

struct Entity; // avoid circular includes

struct BaseComponent {
    unsigned int tag;
    std::weak_ptr<Entity> parent;
};
