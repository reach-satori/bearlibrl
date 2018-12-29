#include "camera.h"
#include "globals.h"


Camera::Camera() {};

void Camera::draw_world(void) const {
    Level lvl = levelmanager->get_change_currlvl();
    const int camx = pos[0];
    const int camy = pos[1];
    //TODO: optimize this by making the check that decides if the tile is inside or outside the "map area" in advance, rather than inside the inner loop
    //that way you'd separate it out into two loops, one that just places nothing and one that draws the map
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height; y++) {
            int x_in_cam = x + camx;
            int y_in_cam = y + camy;
            uint c = (x_in_cam >= lvl.width ||
                      x_in_cam < 0 ||
                      y_in_cam >= lvl.height ||
                      y_in_cam < 0)  ? 0x20 :
                        lvl.is_visible(x_in_cam, y_in_cam) ? lvl.get_character(x_in_cam, y_in_cam) :
                            0x70;
            terminal_put(x, y, c);
        }
    }
}

void Camera::draw_entities(void) const {
    for (const auto& ent : levelmanager->get_current_entities()) {
        auto posin = ent->get_component<Positional>(C_POSITIONAL);
        if (posin == nullptr)
            continue;
        if (!on_camera(posin->pos[0], posin->pos[1]) && ent == player){
            on_camera(posin->pos[0], posin->pos[1]);
            continue;
        }
        terminal_put(posin->pos[0]-pos[0], posin->pos[1]-pos[1], posin->codepoint);
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
