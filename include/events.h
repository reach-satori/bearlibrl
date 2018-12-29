#pragma once
#include "comppos.h"
#include "compinv.h"


void move(Entity * ent, int x, int y);
void item_pickup(Entity* carrier, std::shared_ptr<Entity>item);
