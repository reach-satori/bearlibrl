#include "lvlmanager.h"


LevelManager::LevelManager() {
    auto lvl0 = std::make_unique<Level>(200, 200);
    all_levels.insert(std::make_pair(current_tag, std::move(lvl0)));
    tagged_entities.insert(std::make_pair(current_tag, std::set<std::shared_ptr<Entity>>()));
}

std::set<std::shared_ptr<Entity>> const &LevelManager::get_current_entities() const {
    assert(tagged_entities.find(current_tag) != tagged_entities.end() &&  "attempted to check nonexisting current level for entities: current level should always exist, so something has gone wrong!");
    return tagged_entities.find(current_tag)->second;
}

Level const &LevelManager::get_const_currlvl(void) const {

    assert(all_levels.find(current_tag) != all_levels.end() && "Unique_ptr to current map not found where it should be \n or perhaps it has the incorrect tag");
    Level const& out = *all_levels.find(current_tag)->second.get();
    return out;
}

Level &LevelManager::get_change_currlvl(void) const {
    assert(all_levels.find(current_tag) != all_levels.end() && "Unique_ptr to current map not found where it should be \n or perhaps it has the incorrect tag");
    Level& out = *all_levels.find(current_tag)->second.get();
    return out;
}

void LevelManager::add_entity_to_lvl(std::shared_ptr<Entity>& ent, uint lvl){

    if (!level_check(lvl)){
        printf("attempted to add entity to non-existing lebel");
        return;
    }

    if (entity_check(ent)) {
        printf("attempted to add an already existing entity");
        return;
    }

    all_entities.insert(ent);
    tagged_entities.find(lvl)->second.insert(ent);
}

void LevelManager::add_entity_to_currlvl(std::shared_ptr<Entity>& ent){
    add_entity_to_lvl(ent, current_tag);
}

uint LevelManager::add_lvl(std::unique_ptr<Level> lvl) {

    //unique ptr makes things easier here
    auto newtag = (all_levels.rbegin()->first) + 1;
    assert(level_check(newtag) == false); // this will never return false
    auto pair = std::make_pair( newtag, std::move(lvl));
    assert(all_levels.insert(std::move(pair)).second == true);
    tagged_entities.emplace(newtag, std::set<std::shared_ptr<Entity>>());

    return newtag;
}

void LevelManager::clear_lvl (uint tag) {
    if (tag == current_tag){
        printf("attempted to clear current level");
        return;
    }

    if (!level_check(tag)){
        printf("attempted to clear a level that didn't exist");
        return;
    }

    for (auto& ent: tagged_entities.find(tag)->second) {
        all_entities.erase(ent);
    }
    tagged_entities.erase(tag);
    all_levels.erase(tag);
}

//this can only move to an existing level
void LevelManager::move_to_lvl (uint tag) {
    if (level_check(tag))
        current_tag=tag;
    //something tells me i'll be back to this function often
}

bool LevelManager::entity_check (std::shared_ptr<Entity> const & ent) const {
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

bool LevelManager::level_check (uint tag) const {
    bool in_all_lvls = (all_levels.find(tag) != all_levels.end());
    bool in_tag_lvls = (tagged_entities.find(tag) != tagged_entities.end());

    assert(! (in_tag_lvls && !in_all_lvls));
    assert(! (!in_tag_lvls && in_all_lvls));

    return in_tag_lvls;
}

