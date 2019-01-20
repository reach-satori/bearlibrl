#pragma once
#include <unordered_map>
#include <stack>
#include "menus.h"
#include "compact.h"
#include "comptags.h"
#include "BearLibTerminal.h"

enum COMMAND_DOMAIN {
    CMD_DEFAULT,
    CMD_PICKUP,
    CMD_INVENTORY,
    CMD_COMMON_ACTION,
    CMD_TARGET,
    CMD_LOOK
};

enum COMMAND_TAG {
    NONE,
    TEST,
    MOVE_N,
    MOVE_NW,
    MOVE_NE,
    MOVE_S,
    MOVE_SW,
    MOVE_SE,
    MOVE_E,
    MOVE_W,
    MOVE_UP,
    MOVE_DOWN,
    TARGET_MOVE_N,
    TARGET_MOVE_NW,
    TARGET_MOVE_NE,
    TARGET_MOVE_S,
    TARGET_MOVE_SW,
    TARGET_MOVE_SE,
    TARGET_MOVE_E,
    TARGET_MOVE_W,
    TARGET_MOVE_UP,
    TARGET_MOVE_DOWN,
    TARGET_CANCEL,
    TARGET_CONFIRM,
    ATK_N,
    ATK_NW,
    ATK_NE,
    ATK_S,
    ATK_SW,
    ATK_SE,
    ATK_E,
    ATK_W,
    PICKUP_OPEN,
    PICKUP_CONFIRM,
    LOOK_OPEN,
    INVENTORY_OPEN,
    INVENTORY_DROP,
    COMMON_ACTION_OPEN,
    COMMON_ACTION_LEAP,
    MENU_CANCEL,
    MENU_UP,
    MENU_DOWN,
};

struct Command {
    bool shift;
    bool alt;
    bool ctrl;
    COMMAND_TAG cmd;
    Command(bool, bool, bool, COMMAND_TAG);
    bool right_modcomb(bool, bool, bool) const;
};

struct CommandManager {
    bool shift = false;
    bool alt = false;
    bool ctrl = false;
    std::unordered_map<COMMAND_DOMAIN, std::unordered_multimap<uint, Command>> cmdlists;
    std::stack<COMMAND_DOMAIN> domainstack;
    int last_key;
    int last_cmd = NONE;
    bool game_running = false;

    void add_command(COMMAND_DOMAIN dmn, uint key, Command cmd);
    COMMAND_TAG get_next_cmd();
    COMMAND_TAG check_next_cmd();
    void read_key();
    CommandManager();

};
