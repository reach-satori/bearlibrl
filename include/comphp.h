#pragma once
#include "compbase.h"
#include "comptags.h"
#include "typedefs.h"
#include <random>

struct Vital: public BaseComponent {
    uint maxhp;
    int currhp;
    int ev = 5;
    //death function;??

    int take_dmg(int dmg);
    Vital(void);
    Vital(uint maxhp);
    ~Vital(void);
};

struct Offensal : public BaseComponent {
    private:
        std::pair<int, int> n_tohit;
        std::pair<int, int> n_todmg;
        std::random_device rd;
        std::mt19937 mt = std::mt19937(rd());
    public:
        Offensal(void);
        Offensal(int, int, int, int);
        int hit_roll();
        int dmg_roll();
};


struct Statsal : public BaseComponent {
    private:
        int stre;
        int dext;
        int inte;
        int attu;
        int endu;
        int luck;

    public:
        Statsal(void);
        Statsal(int s, int d, int i, int a, int e, int l);
};
