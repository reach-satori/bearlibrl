#pragma once
#include "typedefs.h"
#include "consts.h"
#include "BearLibTerminal.h"
#include "fdecs.h"
#include <memory>


struct Camera {
        int pos[2] = {0, 0};
        const uint width = CONSOLE_WIDTH;
        const uint height = SCREEN_HEIGHT;

        Camera(void);
        void draw_world(int floor) const;
        void draw_entities(void) const;
        void set_pos(int x, int y);
        void center(int x, int y);
        void center_on_player();
        bool in_camera_center(int x, int y) const ;
        bool on_camera(int x, int y) const;
};
