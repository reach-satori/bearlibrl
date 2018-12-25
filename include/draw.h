#pragma once
#include "map.h"
#include "entity.h"
#include "BearLibTerminal.h"
#include "comptags.h"
#include <set>
#include <memory>
#include "poscomp.h"

void draw_map(std::shared_ptr<Map> map);
void draw_entities(std::shared_ptr<std::set<std::shared_ptr<Entity>>> entities);
