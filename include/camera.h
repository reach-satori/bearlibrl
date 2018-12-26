#pragma once
#include "typedefs.h"
#include "consts.h"
#include "BearLibTerminal.h"
#include "poscomp.h"
#include <stdlib.h>
#include "stdio.h"


struct Camera {
        uint pos[2] = {0, 0};
        const uint width = CONSOLE_WIDTH;
        const uint height = CONSOLE_HEIGHT;

        Camera(void);
        void draw_world(void); // draws full console-size map every time, menus and such go on top with layers
        void draw_entities(void);
        void set_pos(int x, int y);
        void center(std::shared_ptr<Positional> posin);
        bool in_camera_center(std::shared_ptr<Positional> posin);
        bool on_camera(std::shared_ptr<Positional> posin);
        bool on_center(std::shared_ptr<Positional> posin);
};
