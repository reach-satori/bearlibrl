#include "entity.h"

Entity::Entity() : components(std::map<uint, std::unique_ptr<BaseComponent>>()) {
}

void Entity::add_component(std::unique_ptr<BaseComponent> comp) {
    //parent is weak ptr (implictly converted)
    comp->parent = shared_from_this();
    //add component
    components.insert(std::make_pair(comp->tag, std::move(comp)));
}


BaseComponent *Entity::get_change_component(uint tag) {
    auto it = components.find(tag);
    BaseComponent *out;
    if (it == components.end()) {
        out = nullptr;
    } else {
        //it is iterator to pair
        //pair is <uint, shared_ptr<bcomp>
        out = it->second.get();
    }
    return out;
}
BaseComponent const *Entity::get_const_component(uint tag) {
    auto it = components.find(tag);
    BaseComponent *out;
    if (it == components.end()) {
        out = nullptr;
    } else {
        //it is iterator to pair
        //pair is <uint, shared_ptr<bcomp>
        out = it->second.get();
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
