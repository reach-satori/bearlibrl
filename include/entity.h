#pragma once
#include <set>
#include <memory>
#include <map>
#include "basecomp.h"
#include "comptags.h"
#include "typedefs.h"
#include "poscomp.h"
#include "actcomp.h"


struct Entity {
        std::map<uint, BCptr> components;

        Entity(void);
        void add_component(BCptr comp);
        std::set<uint> get_tags(void);
        std::shared_ptr<Positional> get_positional(void);
        uint* get_pos(void);
        std::shared_ptr<Action> get_action(void);
};
