#pragma once
#include <memory>
#include "typedefs.h"


struct BaseComponent {
    const uint tag;
    std::weak_ptr<Entity> parent;

    BaseComponent(uint tag);
    virtual ~BaseComponent() = default;
};
