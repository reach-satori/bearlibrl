#pragma once
#include "map.h"
#include "entity.h"
#include "BearLibTerminal.h"
#include "comptags.h"
#include <set>
#include <memory>
#include "poscomp.h"

void draw_map(Map map);
void draw_entities(std::set<std::shared_ptr<Entity>> entities);
