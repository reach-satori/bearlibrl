#include "globals.h"
#include "enttags.h"

std::shared_ptr<Entity> player = std::make_shared<Entity>(E_PLAYER);

Camera camera = Camera();

std::unique_ptr<LevelManager> levelmanager = std::make_unique<LevelManager>();

CommandManager input = CommandManager();

