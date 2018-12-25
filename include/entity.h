#pragma once
#include <set>
#include <memory>
#include <map>
#include "basecomp.h"
#include "typedefs.h"



struct Entity {
        std::map<uint, BCptr> components;

        Entity(void);
        void add_component(BCptr comp);
        std::set<uint> get_tags(void);
};
