#include "comphp.h"

Vital::Vital(uint maxhp) : BaseComponent(C_VITAL), maxhp(maxhp), currhp(maxhp) {}
Vital::Vital(void) : Vital(100) {}
Vital::~Vital(void) {};
int Vital::take_dmg(int dmg) {
    printf("%d, %d\n", dmg, currhp);
    currhp -= dmg;
    if (currhp <= 0) {
        //death
        return 1;
    } else {
        return 0;
    }
}

///////////////////////////////

Offensal::Offensal(int dhit, int numhit, int ddmg, int numdmg) :
    BaseComponent(C_OFFENSE),
    n_tohit(std::make_pair(dhit, numhit)),
    n_todmg(std::make_pair(ddmg, numdmg)) {}

Offensal::Offensal() : BaseComponent(C_OFFENSE), n_tohit(std::make_pair(2,4)), n_todmg(std::make_pair(1,4)) {}

int Offensal::hit_roll() {
    std::uniform_int_distribution<int> uf(1, n_tohit.second);

    int roll = 0;
    for (int i = 0; i< n_tohit.first; i++) {
        roll += uf(mt);
    }
    return roll;
}

int Offensal::dmg_roll() {
    std::uniform_int_distribution<> uf(1, n_todmg.second);

    int roll = 0;
    for (int i = 0; i< n_todmg.first; i++) {
        roll += uf(mt);
    }
    return roll;
}

////////////////////////////////

Statsal::Statsal(int s, int d, int i, int a, int e, int l) :
    BaseComponent(C_STATS),
    stre(s),
    dext(d),
    inte(i),
    attu(a),
    endu(e),
    luck(l) {}

Statsal::Statsal() : Statsal(10, 10, 10, 10, 10, 10) {}
