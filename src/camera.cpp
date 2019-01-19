#include "camera.h"
#include "globals.h"


Camera::Camera() {};

void Camera::draw_world(int floor) const {
    Level& lvl = levelmanager->get_change_currlvl();
    const int camx = pos[0];
    const int camy = pos[1];

    //clamp camera to map (doesnt attempt to render non-map tiles)
    int startx = camx < 0 ? -camx : 0;
    int starty = camy < 0 ? -camy : 0;
    int endx = camx + width > lvl.width ? width - (camx + width - lvl.width) : width;
    int endy = camy + height > lvl.height ? height - (camy + height - lvl.height): height;

    for (int x = startx; x < endx; x++) {
        for (int y = starty; y < endy; y++) {
            lvl.at(floor, x + camx, y + camy)->draw(x, y);
        }
    }
}

void Camera::draw_entities(void) const {
    for (const auto& ent : levelmanager->get_current_entities()) {
        auto posin = ent->get_component<Positional>(C_POSITIONAL);
        if (!posin)
            continue;
        if (!on_camera(posin->x(), posin->y()))
            continue;
        terminal_put(posin->x()-pos[0], posin->y()-pos[1], posin->codepoint);
    }
}

void Camera::set_pos(int x, int y) {
    pos[0] = x;
    pos[1] = y;
}

//returns true if within some margin of the center of the camera (either horizontally or vertically)
bool Camera::in_camera_center(int x, int y) const {
    bool horcenter = false, vertcenter = false;

    if (x >= pos[0] + (int)width/5 && x <= pos[0] + 4*(int)width/5){
        horcenter = true;
    }
    if (y >= pos[1] + (int)height/4 && y <= pos[1] + 3*(int)height/4){
        vertcenter = true;
    }

    return (horcenter && vertcenter);
}

bool Camera::on_camera(int x, int y) const {
    return x >= pos[0] && x < pos[0] + width && y >= pos[1] && y < pos[1] + height;
}

void Camera::center(int x, int y) {
    if (!in_camera_center(x, y)) {
        set_pos(x-width/2, y-height/2);
    }
}
void Camera::center_on_player(){
    const auto * ppos = player->get_component<Positional const>(C_POSITIONAL);
    center(ppos->x(), ppos->y());
}
