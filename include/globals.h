#pragma once

#include "entity.h"
#include "lvlmanager.h"
#include "input.h"
#include "camera.h"

extern std::shared_ptr<Entity> player;
extern std::unique_ptr<LevelManager> levelmanager;
extern CommandManager input;
extern Camera camera;

