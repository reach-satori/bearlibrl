#include "init_entity.h"
#include "globals.h"



std::shared_ptr<Entity> init_entity(ENTITY_TAG tag) {
    std::shared_ptr<Entity> e = std::make_shared<Entity>(tag);
    levelmanager->add_entity_to_currlvl(e);
    switch (tag) {
        case E_TEST:
            e->add_component(std::make_unique<Positional>(-1, -1, 0x21));
            e->add_component(std::make_unique<EmptyActional>(2000));
            e->add_component(std::make_unique<Carrial>());
            break;
    }
    return e;
}
