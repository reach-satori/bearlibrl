#pragma once
#include "basecomp.h"
#include "typedefs.h"
#include "comptags.h"
#include "invcomp.h"


struct Carrial : BaseComponent {
    float weight;
    std::weak_ptr<Inventorial> invptr ;

    Carrial(void);
    Carrial(float weight, std::weak_ptr<Inventorial> invptr );
};
