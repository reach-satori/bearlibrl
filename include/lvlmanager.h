#pragma once
#include <set>
#include <map>
#include <memory>
#include <cassert>

#include "entity.h"
#include "level.h"
#include "typedefs.h"
#include "consts.h"


class LevelManager {
    std::set<std::shared_ptr<Entity>> all_entities;
    std::map<uint, std::set<std::shared_ptr<Entity>>> tagged_entities;
    std::map<uint, std::unique_ptr<Level>> all_levels;
    uint current_tag = 0;

    public:
        LevelManager();
        std::set<std::shared_ptr<Entity>> const &get_current_entities(void) const;
        Level &get_currlvl(void);
        bool entity_check (std::shared_ptr<Entity> const &) const;
        bool level_check (uint tag) const;
        void add_entity_to_currlvl(const std::shared_ptr<Entity>& ent);
        void add_entity_to_lvl(const std::shared_ptr<Entity>& ent, uint lvl);
        uint add_lvl(std::unique_ptr<Level> lvl);
        void clear_lvl (uint tag);
        void move_to_lvl (uint tag);

        template <typename T>
        std::vector<T*> get_current_components(COMPONENT_TAG tag) const {
            auto out = std::vector<T*>();
            for (const auto& e : get_current_entities()) {
                T* ptr = e->get_component<T>(tag);
                if (!ptr) continue; else out.push_back(ptr);
            }
            return out;
        }

};
