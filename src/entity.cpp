#include "entity.h"
#include "globals.h"


std::set<COMPONENT_TAG> get_inheritors (COMPONENT_TAG t){
    std::set<COMPONENT_TAG> out{t};
    switch (t){
        case C_ACT:
            out.insert(C_ACT_PLAYER);
            out.insert(C_ACT_EMPTY);
            break;
        case C_INV:
            out.insert(C_INV_EQUIP);
            break;
        case C_CARR:
            out.insert(C_CARR_EQUIP);
            break;
        default:
            ;
    }
    return out;
}

Entity::Entity() : components(std::map<COMPONENT_TAG, std::unique_ptr<BaseComponent>>()) {
}

void Entity::add_component(std::unique_ptr<BaseComponent> comp) {
    //parent is weak ptr (implictly converted)
    comp->parent = shared_from_this();
    //add component
    components.insert(std::make_pair(comp->tag, std::move(comp)));
}


BaseComponent *Entity::get_base_component(COMPONENT_TAG tag) {
    auto ent_tags = get_tags();
    auto tags_to_check = get_inheritors(tag);
    COMPONENT_TAG right_tag = C_EMPTY;

    for (const auto& t : tags_to_check) {
        auto a = ent_tags.find(t);
        if (a != ent_tags.end()) return components.find(*a)->second.get();
    }
    return nullptr;
}


std::set<COMPONENT_TAG> Entity::get_tags(void)  {
    std::set<COMPONENT_TAG> out;
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
