#pragma once
#include "typedefs.h"
#include "consts.h"
#include "BearLibTerminal.h"
#include "fdecs.h"
#include <memory>


struct Camera {
        int pos[2] = {0, 0};
        uint floor = 0;
        const uint width = CONSOLE_WIDTH;
        const uint height = SCREEN_HEIGHT;

        Camera(void);
        void draw_world() const;
        void draw_entities(void) const;
        void set_pos(int, int, int);
        void center(Positional const *);
        void center_after_check(Positional const *);
        void center_on_player();
        bool in_camera_center(int, int) const ;
        bool on_camera(Positional const *) const;
        void chfloor(int);
};
