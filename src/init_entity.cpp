#include "init_entity.h"
#include "globals.h"


std::shared_ptr<Entity> init_entity(ENTITY_TAG tag) {
    std::shared_ptr<Entity> e = std::make_shared<Entity>(tag);
    levelmanager->add_entity_to_currlvl(e);
    switch (tag) {
        case E_TEST:
            e->add_component(std::make_unique<Positional>(0, 1, 1, 0x21));
            e->add_component(std::make_unique<EmptyActional>(1000));
            e->add_component(std::make_unique<Carrial>());
            e->add_component(std::make_unique<Vital>());
            e->name = "Test Object";
            break;
        default:
            break;
    }
    return e;
}
