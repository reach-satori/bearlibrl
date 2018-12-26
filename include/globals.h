#pragma once
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "camera.h"
#include <map>
#include <set>

extern std::map<uint, Tile*> alltiles;
extern std::shared_ptr<Entity> player;
extern std::shared_ptr<Map> cmap;
extern std::shared_ptr<std::set<std::shared_ptr<Entity>>> cent;
extern bool game_running;
extern std::shared_ptr<Camera> camera;

