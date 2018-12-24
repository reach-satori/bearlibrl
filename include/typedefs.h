#pragma once
#include <memory>

struct BaseComponent;
struct Entity; // avoid circular includes

typedef unsigned int uint;
typedef std::shared_ptr<BaseComponent> BCptr;
