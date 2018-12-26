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
        std::map<uint, std::shared_ptr<BaseComponent>> components;

        Entity(void);
        void add_component(std::shared_ptr<BaseComponent> comp);
        std::set<uint> get_tags(void);
        std::shared_ptr<Positional> get_positional(void);
        std::shared_ptr<Actional> get_action(void);

        std::shared_ptr<BaseComponent> search_tags_for(uint tag);
};
