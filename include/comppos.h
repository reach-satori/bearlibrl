#pragma once
#include "compbase.h"
#include "comptags.h"
#include "typedefs.h"
#include "BearLibTerminal.h"

struct Positional: public BaseComponent {

    private:
        int pos[3]; // x, y
    public:
        uint codepoint; // display character

        Positional(void);
        Positional(int f, int x, int y, uint codepoint);
        ~Positional(void);
        void setpos(int f, int x, int y);

        uint x(void) const;
        uint y(void) const;
        uint f(void) const;
};
