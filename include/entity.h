#pragma once
#include <set>
#include <vector>
#include <memory>
#include <map>
#include "typedefs.h"
#include "compbase.h"
#include "comptags.h"
#include "comppos.h"
#include "enttags.h"


struct Entity : public std::enable_shared_from_this<Entity> {

        ENTITY_TAG etag;
        std::map<COMPONENT_TAG, std::unique_ptr<BaseComponent>> components;
        std::string name = "";

        Entity(ENTITY_TAG etag);
        void add_component(std::unique_ptr<BaseComponent> comp);
        std::set<COMPONENT_TAG> get_tags(void) const;
        std::shared_ptr<Entity> get_shared();
        /* void unghost(COMPONENT_TAG tag); */

        //thanks c++
        template <typename T>
        T *get_component(COMPONENT_TAG tag) {
            BaseComponent* out = get_base_component(tag);
            if (out == nullptr || out->ghosted) return nullptr;
            else return dynamic_cast<T*>(out);;
        };

    private:
        BaseComponent *get_base_component(COMPONENT_TAG tag) const;
};
