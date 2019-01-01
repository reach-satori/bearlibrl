#pragma once
#include <memory>
#include "typedefs.h"
#include "fdecs.h"
#include "comptags.h"


struct BaseComponent {
    COMPONENT_TAG tag;
    std::weak_ptr<Entity> parent;
    bool ghosted = false;


    void ghost();
    BaseComponent(COMPONENT_TAG tag);
    virtual ~BaseComponent() = default;
};

