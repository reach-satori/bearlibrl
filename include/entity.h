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

        //thanks c++
        template <typename T>
        T *get_component(COMPONENT_TAG tag) {
            return dynamic_cast<T*>(get_base_component(tag));;
        };

    private:
        BaseComponent *get_base_component(COMPONENT_TAG tag);
};
