#pragma once
#include <set>
#include <memory>
#include <map>
#include "typedefs.h"
#include "compbase.h"
#include "comptags.h"
#include "comppos.h"
#include "compact.h"


struct Entity : public std::enable_shared_from_this<Entity> {
        std::map<UNIQUE_COMPONENT_TAG, std::unique_ptr<BaseComponent>> components;

        Entity(void);
        void add_component(std::unique_ptr<BaseComponent> comp);
        std::set<UNIQUE_COMPONENT_TAG> get_tags(void);

        //returns pointer to constant component (or nullptr)
        //used when there is no intention to change entity, just look at it
        BaseComponent const *get_const_component(UNIQUE_COMPONENT_TAG tag);
        BaseComponent *get_change_component(UNIQUE_COMPONENT_TAG tag);
        void annihilate(void);
};
