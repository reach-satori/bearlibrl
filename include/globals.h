#pragma once
#include <map>

#include "tile.h"
#include "entity.h"
#include "camera.h"
#include "lvlmanager.h"
#include "input.h"

extern std::map<uint, Tile*> alltiles;
extern std::shared_ptr<Entity> player;
extern std::unique_ptr<LevelManager> levelmanager;
extern Camera camera;
extern CommandManager input;

