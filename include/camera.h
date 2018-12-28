#pragma once
#include "typedefs.h"
#include "consts.h"
#include "BearLibTerminal.h"
#include "fdecs.h"
#include <memory>


struct Camera {
        int pos[2] = {0, 0};
        const uint width = CONSOLE_WIDTH;
        const uint height = CONSOLE_HEIGHT;

        Camera(void);
        void draw_world(void) const; // draws full console-size map every time, menus and such go on top with layers
        void draw_entities(void) const;
        void set_pos(int x, int y);
        void center(int x, int y);
        bool in_camera_center(int x, int y) const ;
        bool on_camera(int x, int y) const;
};
