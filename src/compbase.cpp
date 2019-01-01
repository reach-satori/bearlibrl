#include "compbase.h"

BaseComponent::BaseComponent(COMPONENT_TAG tag) : tag(tag) {}

//toggle
void BaseComponent::ghost() {
    ghosted = true;
}
