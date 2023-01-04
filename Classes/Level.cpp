#include "Level.h"

void Level::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta);
    }
}