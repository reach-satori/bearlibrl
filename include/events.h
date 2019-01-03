#pragma once
#include "comppos.h"
#include "compinv.h"
#include "comphp.h"
#include <random>


void move(Entity * ent, int f, int x, int y);
int item_pickup(Entity* carrier, std::shared_ptr<Entity>& item);
int common_attack(Entity* attacker, Entity* attackee);
