#include "globals.h"

std::map<uint, Tile*> alltiles {
    std::make_pair(T_FLOOR, new FloorTile),
    std::make_pair(T_WALL, new WallTile)
};

std::shared_ptr<Entity> player = std::make_shared<Entity>();

Camera camera = Camera();

std::unique_ptr<LevelManager> levelmanager = std::make_unique<LevelManager>();

CommandManager input = CommandManager();

