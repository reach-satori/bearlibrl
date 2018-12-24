#pragma once
#include <vector>
#include <memory>
#include <map>
#include "basecomp.h"
#include "typedefs.h"



struct Entity {
        std::map<uint, BCptr> components;

        void add_component(BCptr comp);
        std::vector<uint> get_tags(void);
};
