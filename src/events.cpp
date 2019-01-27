#include "events.h"
#include "globals.h"

//negative return values are for things that aren't expected to happen in normal gameplay, positive for normal stuff
//I've tried to make 0 the "normal" outcome

void move(Entity * ent, int f, int x, int y) {
    auto pos = ent->get_component<Positional>(C_POSITIONAL);
    if (!pos) {
        printf("Entity with no positional component attempted to move\n");
        return;
    }
    if (levelmanager->get_currlvl().passable(f, x, y)){
        pos->setpos(f, x, y);
    }
}

int common_attack(Entity* attacker, Entity* attackee) {
    printf("reached common attack\n");
    if (!(attacker && attackee))
        return -5;
    auto atkcomp = attacker->get_component<Offensal>(C_OFFENSE);
    auto defcomp = attackee->get_component<Vital>(C_VITAL);
    if (!atkcomp)
        return -1;
    if (!defcomp)
        return -2;

    int hit = atkcomp->hit_roll();
    if (hit > defcomp->ev){
        int dmg = atkcomp->dmg_roll();
        int died = defcomp->take_dmg(dmg);
        if (died)
            return 1; //hit and killed
        else
            return 0; // hit normally
    }
    return 2; //missed

}

int item_pickup(Entity* carrier, std::shared_ptr<Entity>& item) {
    auto inv = carrier->get_component<Inventorial>(C_INV);
    if (!inv) {
        printf("Entity with no inventory component attempted to pick an item up\n");
        return -5;
    }
    int status = inv->add_to_inventory(item);
    switch(status) {
        case -1:
            printf("Something attempted to pick up a non-item\n");
            break;
        case 1:
            printf("Attempted to pick up an item over max weight\n");
            break;
        case -3:
            printf("Attempted to pick up an item already in this inventory\n");
            break;
        case -4:
            printf("Attempted to pick up an item already in another inventory\n");
            break;
        case 0:
            printf("picked up\n");
            break;
    }
    return status;
}

