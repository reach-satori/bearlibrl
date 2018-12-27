#pragma once
#include <memory>
#include "typedefs.h"
#include "fdecs.h"
#include "comptags.h"


struct BaseComponent {
    UNIQUE_COMPONENT_TAG tag;
    std::weak_ptr<Entity> parent;

    BaseComponent(UNIQUE_COMPONENT_TAG tag);
    virtual ~BaseComponent() = default;
};

