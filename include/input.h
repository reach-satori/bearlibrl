#include <unordered_map>
#include <stack>
#include "BearLibTerminal.h"

enum COMMAND_DOMAIN {
    CMD_DEFAULT,
    CMD_PICKUP,
};

enum COMMAND_TAG {
    NONE,
    MOVE_N,
    MOVE_NW,
    MOVE_NE,
    MOVE_S,
    MOVE_SW,
    MOVE_SE,
    MOVE_E,
    MOVE_W,
    PICKUP_ITEM
};

struct Command {
    bool shift;
    bool alt;
    bool ctrl;
    COMMAND_TAG cmd;
    Command(bool, bool, bool, COMMAND_TAG);
};

struct CommandManager {
    std::unordered_map<COMMAND_DOMAIN, std::unordered_multimap<uint, Command>> cmdlists;
    std::stack<COMMAND_DOMAIN> domainstack;
    int last_key;

    void add_command(COMMAND_DOMAIN dmn, uint key, Command cmd);
    COMMAND_TAG get_next_cmd();
    void read_key();
    CommandManager();

};
