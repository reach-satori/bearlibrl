#include "input.h"


Command::Command(bool shift, bool alt, bool ctrl, COMMAND_TAG cmd) :
    shift(shift),
    alt(alt),
    ctrl(ctrl),
    cmd(cmd) {};

void CommandManager::add_command(COMMAND_DOMAIN dmn, uint key, Command cmd) {

    auto& dmnmap = cmdlists.find(dmn)->second;
    dmnmap.insert(std::make_pair(key, cmd));
}


CommandManager::CommandManager() {

    domainstack.push(CMD_DEFAULT);

    cmdlists.insert(std::make_pair(CMD_DEFAULT, std::unordered_multimap<uint, Command>()));
    cmdlists.insert(std::make_pair(CMD_PICKUP, std::unordered_multimap<uint, Command>()));

    add_command(CMD_DEFAULT, TK_KP_8, Command(false, false, false, MOVE_N));
    add_command(CMD_DEFAULT, TK_KP_7, Command(false, false, false, MOVE_NW));
    add_command(CMD_DEFAULT, TK_KP_9, Command(false, false, false, MOVE_NE));
    add_command(CMD_DEFAULT, TK_KP_2, Command(false, false, false, MOVE_S));
    add_command(CMD_DEFAULT, TK_KP_1, Command(false, false, false, MOVE_SW));
    add_command(CMD_DEFAULT, TK_KP_3, Command(false, false, false, MOVE_SE));
    add_command(CMD_DEFAULT, TK_KP_6, Command(false, false, false, MOVE_E));
    add_command(CMD_DEFAULT, TK_KP_4, Command(false, false, false, MOVE_W));
}

COMMAND_TAG CommandManager::cmd_from_key(uint key) {
    auto& dmnmap = cmdlists.find(domainstack.top())->second;
    return dmnmap.find(key)->second.cmd;
}


