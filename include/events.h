#pragma once
#include "comppos.h"
#include "compinv.h"


void move(Entity * ent, int x, int y);
int item_pickup(Entity* carrier, std::shared_ptr<Entity>& item);
