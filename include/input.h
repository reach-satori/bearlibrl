#include <unordered_map>
#include <stack>
#include "menus.h"
#include "BearLibTerminal.h"

enum COMMAND_DOMAIN {
    CMD_DEFAULT,
    CMD_PICKUP,
    CMD_INVENTORY
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
    INVENTORY_OPEN,
    INVENTORY_DROP,
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
