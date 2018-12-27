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
        std::map<uint, std::unique_ptr<BaseComponent>> components;

        Entity(void);
        void add_component(std::unique_ptr<BaseComponent> comp);
        std::set<uint> get_tags(void);

        BaseComponent *search_tags_for(uint tag);
};
