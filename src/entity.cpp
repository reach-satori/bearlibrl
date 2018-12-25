#include "entity.h"

Entity::Entity() : components(std::map<uint, BCptr>()) {}

void Entity::add_component(BCptr comp) {
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
    auto tags = get_tags();
    auto ptag = tags.find(C_POSITIONAL);
    if (ptag != tags.end()) {
        out = std::dynamic_pointer_cast<Positional>(components.find(*ptag)->second);
    } else {
        out = nullptr;
    }
    return out;
}

uint* Entity::get_pos(void) {
    uint* out = nullptr;
    auto tags = get_tags();
    auto ptag = tags.find(C_POSITIONAL);
    if (ptag != tags.end()) {
        out = get_positional()->pos;
    }
    return out;

}

std::shared_ptr<Actional> Entity::get_action(void) {
    std::shared_ptr<Actional> out;
    auto tags = get_tags();
    auto ptag = tags.find(C_ACT);
    if (ptag != tags.end()) {
        out = std::dynamic_pointer_cast<Actional>(components.find(*ptag)->second);
    } else {
        out = nullptr;
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
