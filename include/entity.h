#pragma once
#include <set>
#include <memory>
#include <map>
#include "typedefs.h"
#include "compbase.h"
#include "comptags.h"
#include "comppos.h"

std::set<COMPONENT_TAG> get_inheritors(COMPONENT_TAG);

struct Entity : public std::enable_shared_from_this<Entity> {
        std::map<COMPONENT_TAG, std::unique_ptr<BaseComponent>> components;

        Entity(void);
        void add_component(std::unique_ptr<BaseComponent> comp);
        std::set<COMPONENT_TAG> get_tags(void);

        //returns pointer to constant component (or nullptr)
        //used when there is no intention to change entity, just look at it
        BaseComponent *get_base_component(COMPONENT_TAG tag);

        //thanks c++
        template <typename T>
        T *get_component(COMPONENT_TAG tag) {
            return dynamic_cast<T*>(get_base_component(tag));;
        };

        void annihilate(void);
};
