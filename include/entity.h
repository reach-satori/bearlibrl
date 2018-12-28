#pragma once
#include <set>
#include <memory>
#include <map>
#include "typedefs.h"
#include "compbase.h"
#include "comptags.h"
#include "comppos.h"


struct Entity : public std::enable_shared_from_this<Entity> {
        std::map<COMPONENT_TAG, std::unique_ptr<BaseComponent>> components;

        Entity(void);
        void add_component(std::unique_ptr<BaseComponent> comp);
        std::set<COMPONENT_TAG> get_tags(void);

        //returns pointer to constant component (or nullptr)
        //used when there is no intention to change entity, just look at it
        BaseComponent const *get_const_component(COMPONENT_TAG tag);
        BaseComponent *get_change_component(COMPONENT_TAG tag);

        //thanks c++
        template <typename T>
        T const *get_const_component(COMPONENT_TAG tag) {
            T const *ptr = dynamic_cast<T const *>(get_const_component(tag));
            return ptr;
        };

        template <typename T>
        T *get_change_component(COMPONENT_TAG tag) {
            T *ptr = dynamic_cast<T*>(get_change_component(tag));
            return ptr;
        };

        void annihilate(void);
};
