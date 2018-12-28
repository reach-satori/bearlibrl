#pragma once
#include <memory>
#include "typedefs.h"
#include "fdecs.h"
#include "comptags.h"


struct BaseComponent {
    COMPONENT_TAG tag;
    COMPONENT_SUBTAG subtag;
    std::weak_ptr<Entity> parent;

    BaseComponent(COMPONENT_TAG tag, COMPONENT_SUBTAG subtag);
    virtual ~BaseComponent() = default;
};

