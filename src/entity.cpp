#include "entity.h"

Entity::Entity() : components(std::map<uint, std::shared_ptr<BaseComponent>>()) {}

void Entity::add_component(std::shared_ptr<BaseComponent> comp) {
    //parent is weak_ptr
    comp->parent = std::make_shared<Entity>(*this);
    //add component
    auto compin = std::make_pair(comp->tag, comp);
    components.insert(compin);
    //add tag to taglist
    //add parent weak_ptr to component "parent" field
}

std::shared_ptr<Positional> Entity::get_positional(void){
    std::shared_ptr<Positional> out;
    out = std::dynamic_pointer_cast<Positional>(search_tags_for(C_POSITIONAL));
    return out;
}

std::shared_ptr<Actional> Entity::get_action(void) {
    std::shared_ptr<Actional> out;
    out = std::dynamic_pointer_cast<Actional>(search_tags_for(C_ACT));
    return out;
}

std::shared_ptr<BaseComponent> Entity::search_tags_for(uint tag) {
    auto it = components.find(tag);
    std::shared_ptr<BaseComponent> out;
    if (it == components.end()) {
        out = nullptr;
    } else {
        //it is iterator to pair
        //pair is <uint, shared_ptr<bcomp>
        out = std::shared_ptr<BaseComponent>(it->second);
    }
    return out;
}


std::set<uint> Entity::get_tags(void)  {
    std::set<uint> out;
    if (components.size() == 0) {
        out.insert(0);
        return out;
    }
    for (auto it = components.begin(); it != components.end(); it++) {
        out.insert(it->first);
    }
    return out;
}
