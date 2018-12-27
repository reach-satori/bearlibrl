#include "globals.h"

std::map<uint, Tile*> alltiles {
    std::make_pair(T_FLOOR, new FloorTile),
    std::make_pair(T_WALL, new WallTile)
};

std::shared_ptr<Entity> player = std::make_shared<Entity>();

std::shared_ptr<Level> cmap = std::make_shared<Level>();

std::shared_ptr<std::set<std::shared_ptr<Entity>>> cent = std::make_shared<std::set<std::shared_ptr<Entity>>>();

bool game_running = false;

std::shared_ptr<Camera> camera = std::make_shared<Camera>();


