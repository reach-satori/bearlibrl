#include "entity.h"

void Entity::add_component(std::shared_ptr<BaseComponent> comp) {
    //add component
    components.push_back(comp);
    //add tag to taglist
    tags.push_back(comp->tag);
    //add parent weak_ptr to component "parent" field
    auto tempshared = std::make_shared<Entity>(*this);
    comp->parent = std::weak_ptr<Entity>(tempshared);
}
