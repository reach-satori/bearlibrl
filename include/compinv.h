#pragma once
#include "compbase.h"
#include "comptags.h"
#include "entity.h"
#include "compcarr.h"
#include "slottags.h"
#include <memory>
#include <set>
#include <cassert>
#include <map>

struct Inventorial : public BaseComponent {
    float maxweight;
    float currload = 0;
    std::set<std::shared_ptr<Entity>> inventory = std::set<std::shared_ptr<Entity>>();

    int add_to_inventory(std::shared_ptr<Entity>& item);
    int remove_from_inventory(std::shared_ptr<Entity>& item);
    Inventorial(void);
    Inventorial(float maxweight);
    Inventorial(float maxweight, COMPONENT_TAG tag);
};

struct EquipInventorial : public Inventorial {
    //slot, equipped yes/no
    std::multimap<EQUIP_SLOT_TAG, bool> slotlist{
        std::make_pair(ES_HEAD, false),
        std::make_pair(ES_CHEST, false),
        std::make_pair(ES_FINGER, false),
        std::make_pair(ES_FINGER, false),
        std::make_pair(ES_LEGS, false),
        std::make_pair(ES_HAND, false),
        std::make_pair(ES_HAND, false),
        std::make_pair(ES_NECK, false),
    };
    EquipInventorial(float weight);
    int inner_equip_item(std::shared_ptr<Entity>& equipped);
};
