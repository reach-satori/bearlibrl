#include "lvlmanager.h"


LevelManager::LevelManager() {
    auto lvl0 = std::make_unique<Level>(200, 200);
    all_levels.insert(std::make_pair(current_tag, std::move(lvl0)));
    tagged_entities.insert(std::make_pair(current_tag, std::set<std::shared_ptr<Entity>>()));
}

std::set<std::shared_ptr<Entity>> const *LevelManager::get_current_entities() const {
    return &tagged_entities.find(current_tag)->second;
}

Level const *LevelManager::get_const_currlvl(void) const {
    Level const * out = all_levels.find(current_tag)->second.get();
    return out;
}

Level *LevelManager::get_change_currlvl(void) const {
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

    //pair <iterator<ptr<entity>>, bool>, bool false if there was a duplicate(and insertion failed)
    //search: set return value
    if (!all_entities.insert(ent).second) {
        //duplicate entity found in all_entities:
        //TODO: handle case
        return;
    }
    lvl_entities->second.insert(ent);// if above block doesn't return, duplicate tag not found in all_entities, therefore we're cleared to add it to tagged_entities
}

void LevelManager::add_entity_to_currlvl(std::shared_ptr<Entity> ent){
    add_entity_to_lvl(ent, current_tag);
}

void LevelManager::add_lvl(std::unique_ptr<Level> lvl) {

    //unique ptr makes things easier here
    auto newtag = (all_levels.rbegin()->first) + 1;
    auto pair = std::make_pair( newtag, std::move(lvl));
    all_levels.insert(std::move(pair));
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


