#include "input.h"
#include "globals.h"


Command::Command(bool shift, bool alt, bool ctrl, COMMAND_TAG cmd) :
    shift(shift),
    alt(alt),
    ctrl(ctrl),
    cmd(cmd) {};

bool Command::right_modcomb(bool ishift, bool ialt, bool ictrl) const {
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
    cmdlists.insert(std::make_pair(CMD_INVENTORY, std::unordered_multimap<uint, Command>()));
    cmdlists.insert(std::make_pair(CMD_COMMON_ACTION, std::unordered_multimap<uint, Command>()));

    //                                              shift    alt     ctrl
    add_command(CMD_DEFAULT , TK_KP_8   , Command(false , false , false , MOVE_N));
    add_command(CMD_DEFAULT , TK_KP_7   , Command(false , false , false , MOVE_NW));
    add_command(CMD_DEFAULT , TK_KP_9   , Command(false , false , false , MOVE_NE));
    add_command(CMD_DEFAULT , TK_KP_2   , Command(false , false , false , MOVE_S));
    add_command(CMD_DEFAULT , TK_KP_1   , Command(false , false , false , MOVE_SW));
    add_command(CMD_DEFAULT , TK_KP_3   , Command(false , false , false , MOVE_SE));
    add_command(CMD_DEFAULT , TK_KP_6   , Command(false , false , false , MOVE_E));
    add_command(CMD_DEFAULT , TK_KP_4   , Command(false , false , false , MOVE_W));
    add_command(CMD_DEFAULT , TK_UP     , Command(false , false , false , MOVE_N));
    add_command(CMD_DEFAULT , TK_LEFT   , Command(false , false , false , MOVE_W));
    add_command(CMD_DEFAULT , TK_RIGHT  , Command(false , false , false , MOVE_E));
    add_command(CMD_DEFAULT , TK_DOWN   , Command(false , false , false , MOVE_S));
    add_command(CMD_DEFAULT , TK_PERIOD , Command(true  , false , false , MOVE_DOWN));
    add_command(CMD_DEFAULT , TK_COMMA  , Command(true  , false , false , MOVE_UP));
    //
    add_command(CMD_DEFAULT , TK_KP_8   , Command(false , false , true  , ATK_N));
    add_command(CMD_DEFAULT , TK_KP_7   , Command(false , false , true  , ATK_NW));
    add_command(CMD_DEFAULT , TK_KP_9   , Command(false , false , true  , ATK_NE));
    add_command(CMD_DEFAULT , TK_KP_2   , Command(false , false , true  , ATK_S));
    add_command(CMD_DEFAULT , TK_KP_1   , Command(false , false , true  , ATK_SW));
    add_command(CMD_DEFAULT , TK_KP_3   , Command(false , false , true  , ATK_SE));
    add_command(CMD_DEFAULT , TK_KP_6   , Command(false , false , true  , ATK_E));
    add_command(CMD_DEFAULT , TK_KP_4   , Command(false , false , true  , ATK_W));
    add_command(CMD_DEFAULT , TK_UP     , Command(false , false , true  , ATK_N));
    add_command(CMD_DEFAULT , TK_LEFT   , Command(false , false , true  , ATK_W));
    add_command(CMD_DEFAULT , TK_RIGHT  , Command(false , false , true  , ATK_E));
    add_command(CMD_DEFAULT , TK_DOWN   , Command(false , false , true  , ATK_S));
    //
    add_command(CMD_DEFAULT , TK_G      , Command(false , false , false , PICKUP_OPEN));
    add_command(CMD_DEFAULT , TK_I      , Command(false , false , false , INVENTORY_OPEN));
    add_command(CMD_DEFAULT , TK_Y      , Command(false , false , false , COMMON_ACTION_OPEN));

    add_command(CMD_PICKUP    , TK_ESCAPE , Command(false , false , false , MENU_CANCEL));
    add_command(CMD_PICKUP    , TK_DOWN   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_PICKUP    , TK_UP     , Command(false , false , false , MENU_UP));
    add_command(CMD_PICKUP    , TK_KP_2   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_PICKUP    , TK_KP_8   , Command(false , false , false , MENU_UP));
    add_command(CMD_PICKUP    , TK_ENTER  , Command(false , false , false , PICKUP_CONFIRM));

    add_command(CMD_INVENTORY , TK_ESCAPE , Command(false , false , false , MENU_CANCEL));
    add_command(CMD_INVENTORY , TK_DOWN   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_INVENTORY , TK_UP     , Command(false , false , false , MENU_UP));
    add_command(CMD_INVENTORY , TK_KP_2   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_INVENTORY , TK_KP_8   , Command(false , false , false , MENU_UP));
    add_command(CMD_INVENTORY , TK_ENTER  , Command(false , false , false , INVENTORY_DROP));

    add_command(CMD_COMMON_ACTION , TK_ESCAPE , Command(false , false , false , MENU_CANCEL));
    add_command(CMD_COMMON_ACTION , TK_DOWN   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_COMMON_ACTION , TK_UP     , Command(false , false , false , MENU_UP));
    add_command(CMD_COMMON_ACTION , TK_KP_2   , Command(false , false , false , MENU_DOWN));
    add_command(CMD_COMMON_ACTION , TK_KP_8   , Command(false , false , false , MENU_UP));
}


COMMAND_TAG CommandManager::check_next_cmd() {
    auto& dmnmap = cmdlists.find(domainstack.top())->second;
    auto cmds = dmnmap.find(last_key);
    if (cmds == dmnmap.end()) return NONE;

    auto its = dmnmap.equal_range(cmds->first);
    for (auto it = its.first; it != its.second; it++) {
        if (it->second.right_modcomb(shift, alt, ctrl)) return it->second.cmd;
    }
    return NONE;
}

void CommandManager::read_key() {
    last_key = terminal_read();
    shift = terminal_check(TK_SHIFT);
    ctrl = terminal_check(TK_CONTROL);
    alt = terminal_check(TK_ALT);
    last_cmd = check_next_cmd();
    /* auto pact = player->get_component<PlayerActional>(C_ACT_PLAYER); */
    //here we decide whether the command taken pauses the game or not and whether it changes the command domain
    //for example, opening a pick up menu and cancelling it after looking at the items does not move gametime
    //but if you choose an item to pick up it does
    //(actual action is defined in compact.cpp)
    switch (last_cmd) {
        case MENU_CANCEL:
            game_running = false;
            domainstack.pop();
            break;
        case INVENTORY_DROP:
            if (!retrieve_chosen_item()) {
                printf("input received nullptr when attempting to drop item\nempty inventory?\n");
                game_running = false;
                last_cmd = NONE;
            } else {
                game_running = true;
                domainstack.pop();
            }
            break;
        case PICKUP_OPEN:
            game_running = false;
            domainstack.push(CMD_PICKUP);
            break;
        case PICKUP_CONFIRM:
            game_running = true;
            domainstack.pop();
            break;
        case INVENTORY_OPEN:
            game_running = false;
            domainstack.push(CMD_INVENTORY);
            break;
        case COMMON_ACTION_OPEN:
            game_running = false;
            domainstack.push(CMD_COMMON_ACTION);
            break;
        case MENU_UP:
        case MENU_DOWN:
        case NONE:
            game_running = false;
            break;
        default:
            game_running = true;
            break;
    }
}


