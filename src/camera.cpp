#include "camera.h"
#include "globals.h"


Camera::Camera() {};

void Camera::draw_world(void) const {
    Level const * lvl = levelmanager->get_const_currlvl();
    const int currx = pos[0];
    const int curry = pos[1];
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height; y++) {
            uint c = (x + currx >= lvl->width ||
                      x + currx < 0 ||
                      y + curry >= lvl->height ||
                      y + curry < 0
                      ) ? 0x2588 : lvl->tiles[x+pos[0]][y+pos[1]].second->character;
            terminal_put(x, y, c);
        }
    }
}
void Camera::draw_entities(void) const {
    for (const auto& ent : *levelmanager->get_current_entities()) {
        Positional const *posin = dynamic_cast<Positional const *>(ent->get_const_component(C_POSITIONAL));
        if (posin == nullptr)
            continue;
        if (!on_camera(posin) && ent == player){
            on_camera(posin);
            continue;
        }
        terminal_put(posin->pos[0]-pos[0], posin->pos[1]-pos[1], posin->codepoint);
    }
}

void Camera::set_pos(int x, int y) {
    /* auto lvlwidth = levelmanager->get_const_currlvl()->width; */
    /* auto lvlheight = levelmanager->get_const_currlvl()->height; */
    /* pos[0] = clamp(x, 0, lvlwidth - width); */
    /* pos[1] = clamp(y, 0, lvlheight - height); */
    pos[0] = x;
    pos[1] = y;
}

//returns true if within some margin of the center of the camera (either horizontally or vertically)
bool Camera::in_camera_center(Positional const * posin) const {
    const int objx = posin->pos[0];
    const int objy = posin->pos[1];
    bool horcenter = false, vertcenter = false;

    if (objx >= pos[0] + (int)width/5 && objx <= pos[0] + 4*(int)width/5){
        horcenter = true;
    }
    if (objy >= pos[1] + (int)height/4 && objy <= pos[1] + 3*(int)height/4){
        vertcenter = true;
    }

    return (horcenter && vertcenter);
}

bool Camera::on_camera(Positional const * posin) const {
    const int x = posin->pos[0];
    const int y = posin->pos[1];
    return x >= pos[0] && x < pos[0] + width && y >= pos[1] && y < pos[1] + height;
}

void Camera::center(Positional const *posin) {
    if (!in_camera_center(posin)) {
        set_pos(posin->pos[0]-width/2, posin->pos[1]-height/2);
    }
}
