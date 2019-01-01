#pragma once
#include <memory>

#include "entity.h"
#include "enttags.h"
#include "comptags.h"
#include "comppos.h"
#include "comphp.h"
#include "compact.h"
#include "compinv.h"
#include "compcarr.h"


std::shared_ptr<Entity> init_entity(ENTITY_TAG);
