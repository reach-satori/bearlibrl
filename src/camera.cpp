#include "camera.h"
#include "globals.h"


Camera::Camera() {};

void Camera::draw_world(void) {
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height; y++) {
            for (auto it = cmap->tiles[x+pos[0]][y+pos[1]].begin(); it != cmap->tiles[x+pos[0]][y+pos[1]].end(); it++) {
                terminal_put(x, y, (*it).second->character);
            }
        }
    }
}
void Camera::draw_entities(void) {
    for (auto& ent : *cent) {
        auto posin = ent->get_positional();
        if (posin == nullptr)
            continue;
        if (!on_camera(posin))
            continue;
        terminal_put(posin->pos[0]-pos[0], posin->pos[1]-pos[1], posin->codepoint);
    }
}

void Camera::set_pos(int x, int y) {
    pos[0] = clamp(x, 0, pos[0] + width);
    pos[1] = clamp(y, 0, pos[1] + height);
    printf("camera position set: xpos:%d, ypos:%d, camx after:%d, camy after:%d\n", x, y, pos[0], pos[1]);
}

//returns true if within some margin of the center of the camera (either horizontally or vertically)
bool Camera::in_camera_center(std::shared_ptr<Positional> posin) {
    uint objx = posin->pos[0];
    uint objy = posin->pos[1];
    bool horcenter = false, vertcenter = false;

    if (objx >= pos[0] + width/5 && objx <= pos[0] + 4*width/5){
        horcenter = true;
    }
    if (objy >= pos[1] + height/4 && objy <= pos[1] + 3*height/4){
        vertcenter = true;
    }

    return (horcenter && vertcenter);
}

bool Camera::on_camera(std::shared_ptr<Positional> posin) {
    uint x = posin->pos[0];
    uint y = posin->pos[1];
    return x >= pos[0] && x < pos[0] + width && y >= pos[1] && y < pos[1] + height;
}

void Camera::center(std::shared_ptr<Positional> posin) {
    if (!in_camera_center(posin)) {
        set_pos(posin->pos[0]-width/2, posin->pos[1]-height/2);
    }
}
