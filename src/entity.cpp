#include "entity.h"
#include "globals.h"

Entity::Entity() : components(std::map<UNIQUE_COMPONENT_TAG, std::unique_ptr<BaseComponent>>()) {
}

void Entity::add_component(std::unique_ptr<BaseComponent> comp) {
    //parent is weak ptr (implictly converted)
    comp->parent = shared_from_this();
    //add component
    components.insert(std::make_pair(comp->tag, std::move(comp)));
}


BaseComponent *Entity::get_change_component(UNIQUE_COMPONENT_TAG tag) {
    auto it = components.find(tag);
    BaseComponent *out;
    if (it == components.end()) {
        out = nullptr;
    } else {
        //it is iterator to pair
        //pair is <UNIQUE_COMPONENT_TAG, shared_ptr<bcomp>
        out = it->second.get();
    }
    return out;
}
BaseComponent const *Entity::get_const_component(UNIQUE_COMPONENT_TAG tag) {
    auto it = components.find(tag);
    BaseComponent *out;
    if (it == components.end()) {
        out = nullptr;
    } else {
        //it is iterator to pair
        //pair is <UNIQUE_COMPONENT_TAG, shared_ptr<bcomp>
        out = it->second.get();
    }
    return out;
}


std::set<UNIQUE_COMPONENT_TAG> Entity::get_tags(void)  {
    std::set<UNIQUE_COMPONENT_TAG> out;
    if (components.size() == 0) {
        return out;
    }
    for (auto it = components.begin(); it != components.end(); it++) {
        out.insert(it->first);
    }
    return out;
}

//to arbitrarily destroy an entity call this
//if it's getting cleared as part of a level clear etc this should not be used
void Entity::annihilate(void) {
    auto ptr = shared_from_this();
    levelmanager->annihilate_entity(ptr);

}
