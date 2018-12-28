#include "input.h"
#include "globals.h"


//probably we will need to revamp this completely later on with a full-fledged input system
void process_input(int key) {

        auto pos = player->get_change_component<Positional>(C_POSITIONAL);
        assert(pos != nullptr);

        uint x = pos->pos[0];
        uint y = pos->pos[1];
        switch(key) {
            case TK_UP    :
                pos->move(x, y-1);
                break;
            case TK_DOWN    :
                pos->move(x, y+1);
                break;
            case TK_LEFT    :
                pos->move(x-1, y);
                break;
            case TK_RIGHT    :
                pos->move(x+1, y);
                break;
        }

        key = 0;

}
