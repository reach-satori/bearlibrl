#include "globals.h"

std::shared_ptr<Entity> player = std::make_shared<Entity>();

Camera camera = Camera();

std::unique_ptr<LevelManager> levelmanager = std::make_unique<LevelManager>();

CommandManager input = CommandManager();

