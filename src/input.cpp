#include "input.h"


//probably we will need to revamp this completely later on with a full-fledged input system
void process_input(int key) {

        uint* pos = player->get_pos();

        assert(pos != nullptr);

        uint& x = pos[0];
        uint& y = pos[1];
        switch(key) {
            case TK_UP    :
                if (cmap->is_passable(x, y-1)) {
                    y -= 1;
                }
                break;
            case TK_DOWN    :
                if (cmap->is_passable(x, y+1)) {
                    y += 1;
                }
                break;
            case TK_LEFT    :
                if (cmap->is_passable(x-1, y)) {
                    x -= 1;
                }
                break;
            case TK_RIGHT    :
                if (cmap->is_passable(x+1, y)) {
                    x += 1;
                }
                break;
        }
        key = 0;

}
