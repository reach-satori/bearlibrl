#include "lvlmanager.h"


LevelManager::LevelManager() {
    auto lvl0 = std::make_unique<Level>(200, 200);
    all_levels.insert(std::make_pair(current_tag, std::move(lvl0)));
    tagged_entities.insert(std::make_pair(current_tag, std::set<std::shared_ptr<Entity>>()));
}

std::set<std::shared_ptr<Entity>> const *LevelManager::get_current_entities() const {
    assert(tagged_entities.find(current_tag) != tagged_entities.end() &&  "attempted to check nonexisting current level for entities: current level should always exist, so something has gone wrong!");
    return &tagged_entities.find(current_tag)->second;
}

Level const *LevelManager::get_const_currlvl(void) const {

    assert(all_levels.find(current_tag) != all_levels.end() && "Unique_ptr to current map not found where it should be \n or perhaps it has the incorrect tag");
    Level const * out = all_levels.find(current_tag)->second.get();
    return out;
}

Level *LevelManager::get_change_currlvl(void) const {
    assert(all_levels.find(current_tag) != all_levels.end() && "Unique_ptr to current map not found where it should be \n or perhaps it has the incorrect tag");
    Level *out = all_levels.find(current_tag)->second.get();
    return out;
}

void LevelManager::add_entity_to_lvl(std::shared_ptr<Entity> ent, uint lvl){
    //iterator to pair <uint, set<ptr<entity>>, or end() if not found
    //search: map find method return value
    auto lvl_entities = tagged_entities.find(lvl);
    if (lvl_entities == tagged_entities.end()){
        // no level matching the tag found
        // TODO: handle case?
        return;
    }

    bool in = entity_check(ent);
    if (in) {
        printf("attempted to add an already existing entity");
        return;
    }

    all_entities.insert(ent);
    lvl_entities->second.insert(ent);
}

void LevelManager::add_entity_to_currlvl(std::shared_ptr<Entity> ent){
    add_entity_to_lvl(ent, current_tag);
}

void LevelManager::add_lvl(std::unique_ptr<Level> lvl) {

    //unique ptr makes things easier here
    auto newtag = (all_levels.rbegin()->first) + 1;
    auto pair = std::make_pair( newtag, std::move(lvl));
    assert(all_levels.insert(std::move(pair)).second == true);
    tagged_entities.emplace(newtag, std::set<std::shared_ptr<Entity>>());

}

void LevelManager::clear_lvl (uint tag) {
    auto it = tagged_entities.find(tag);
    if (it == tagged_entities.end()){
        //tag not found
        //TODO: handle it
        return;
    }

    for (auto& ent: it->second) {
        all_entities.erase(ent);
    }
    tagged_entities.erase(tag);
    all_levels.erase(tag);
}

void LevelManager::switch_lvl (uint tag) {
    current_tag=tag;
    //something tells me i'll be back to this function often
}

bool LevelManager::entity_check (std::shared_ptr<Entity> ent) const {
    //check that the entity is either in neither entity set or in both
    //returns true if entity is in, false if not, asserts out if neither option
    bool in_all_entities = (all_entities.find(ent) != all_entities.end());

    bool in_tagged_entities = false;
    for (auto lvl = tagged_entities.rbegin(); lvl != tagged_entities.rend(); lvl++) {
        if (lvl->second.find(ent) != lvl->second.end()){
            in_tagged_entities = true;
            break;
        }
    }

    assert(! (in_tagged_entities && !in_all_entities));
    assert(! (!in_tagged_entities && in_all_entities));

    //due to the assertions above in_tagged_entities and in_all_entities are guaranteed to be the same
    //so we can return just one of em: true if it's in, false if it's not
    return (in_tagged_entities);
}

void LevelManager::annihilate_entity (std::shared_ptr<Entity> ent) {
}

