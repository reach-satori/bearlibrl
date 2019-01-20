#include "camera.h"
#include "globals.h"


Camera::Camera() {};

void Camera::draw_world() const {
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
    for (auto const posin : levelmanager->get_current_components<Positional const>(C_POSITIONAL)) {
        assert(posin);
        if (!on_camera(posin))
            continue;
        terminal_put(posin->x()-pos[0], posin->y()-pos[1], posin->codepoint);
    }
    if (input.domainstack.top() == CMD_LOOK) {
        auto tpos = get_target();
        terminal_put(tpos->x()-pos[0], tpos->y()-pos[1], tpos->codepoint);
    }
}

void Camera::set_pos(int f, int x, int y) {
    pos[0] = x;
    pos[1] = y;
    floor = f;
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

bool Camera::on_camera(Positional const * posin) const {
    return
        //focken compiler warnings
        posin->f() == floor &&
        static_cast<int>(posin->x()) >= pos[0] &&
        posin->x() < pos[0] + width &&
        static_cast<int>(posin->y()) >= pos[1] &&
        posin->y() < pos[1] + height;
}

void Camera::chfloor(int dir) {
    auto lvl = levelmanager->get_change_currlvl();
    if (floor + dir < 0 || floor + dir >= lvl.depth) {
        return;
    }
    floor += dir;
}

void Camera::center_after_check(Positional const * pos){
    int x = pos->x();
    int y = pos->y();
    if (!in_camera_center(x, y) || pos->f() != floor) {
        center(pos);
    }
}

void Camera::center(Positional const * pos) {
    int x = pos->x();
    int y = pos->y();
    set_pos(pos->f(), x-width/2, y-height/2);
}
void Camera::center_on_player(){
    center_after_check(player->get_component<Positional const>(C_POSITIONAL));
}
