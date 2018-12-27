#include <set>
#include <map>
#include <memory>

#include "entity.h"
#include "level.h"
#include "typedefs.h"


class LevelManager {
    std::set<std::shared_ptr<Entity>> all_entities;
    std::map<uint, std::set<std::shared_ptr<Entity>>> tagged_entities;
    std::map<uint, std::unique_ptr<Level>> all_levels;
    uint current_tag = 0;

    public:
        LevelManager();
        std::set<std::shared_ptr<Entity>> const *get_current_entities(void) const;
        Level const *get_const_currlvl(void) const;
        Level *get_change_currlvl(void) const;
        void add_entity_to_currlvl(std::shared_ptr<Entity> ent);
        void add_entity_to_lvl(std::shared_ptr<Entity> ent, uint lvl);
        void add_lvl(std::unique_ptr<Level> lvl);
        void clear_lvl (uint tag);
        void switch_lvl (uint tag);

};
