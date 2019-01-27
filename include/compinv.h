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

    int add_to_inventory(std::shared_ptr<Entity>&);
    int remove_from_inventory(std::shared_ptr<Entity>&);
    std::vector<std::shared_ptr<Entity>> inv_to_vector(void) const;
    void refresh_weight(void);
    int inv_add_check(std::shared_ptr<Entity> const &) const;
    Inventorial(void);
    Inventorial(float);
    Inventorial(float, COMPONENT_TAG);
};

struct EquipInventorial : public Inventorial {
    //slot, equipped yes/no
    std::multimap<EQUIP_SLOT_TAG, bool> slotlist;

    EquipInventorial(float);
    EquipInventorial(float, std::multimap<EQUIP_SLOT_TAG, bool>);
    int inner_equip_item(std::shared_ptr<Entity>&);
    bool is_slot_free(EQUIP_SLOT_TAG);
};
