#include "input.h"


Command::Command(bool shift, bool alt, bool ctrl, COMMAND_TAG cmd) :
    shift(shift),
    alt(alt),
    ctrl(ctrl),
    cmd(cmd) {};

bool Command::right_modcomb(bool ishift, bool ialt, bool ictrl) {
    return ishift == shift && ialt == alt && ictrl == ctrl;
}

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
    /* add_command(CMD_DEFAULT, TK_K, Command(false, false, false, MOVE_N)); */
    /* add_command(CMD_DEFAULT, TK_Y, Command(false, false, false, MOVE_NW)); */
    /* add_command(CMD_DEFAULT, TK_U, Command(false, false, false, MOVE_NE)); */
    /* add_command(CMD_DEFAULT, TK_J, Command(false, false, false, MOVE_S)); */
    /* add_command(CMD_DEFAULT, TK_B, Command(false, false, false, MOVE_SW)); */
    /* add_command(CMD_DEFAULT, TK_N, Command(false, false, false, MOVE_SE)); */
    /* add_command(CMD_DEFAULT, TK_L, Command(false, false, false, MOVE_E)); */
    /* add_command(CMD_DEFAULT, TK_H, Command(false, false, false, MOVE_W)); */
    add_command(CMD_DEFAULT, TK_UP, Command(false, false, false, MOVE_N));
    add_command(CMD_DEFAULT, TK_LEFT, Command(false, false, false, MOVE_W));
    add_command(CMD_DEFAULT, TK_RIGHT, Command(false, false, false, MOVE_E));
    add_command(CMD_DEFAULT, TK_DOWN, Command(false, false, false, MOVE_S));
    add_command(CMD_DEFAULT, TK_G, Command(false, false, false, PICKUP_OPEN));
}

COMMAND_TAG CommandManager::get_next_cmd() {
    auto& dmnmap = cmdlists.find(domainstack.top())->second;
    auto cmds = dmnmap.find(last_key);
    last_key = 0;

    game_running=false;
    return cmds == dmnmap.end() ? NONE : cmds->second.cmd;
}

void CommandManager::read_key() {
    last_key = terminal_read();
    game_running = true;
}


