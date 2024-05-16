#include "collision.hpp"

bool is_hit(Hitbox *b1, Hitbox *b2) {
    if (!b1 || !b2)
        return false;

    bool xhit = b1->position.x < b2->position.x + b2->size.x &&
                b1->position.x + b1->size.x > b2->position.x;

    bool yhit = b1->position.y < b2->position.y + b2->size.y &&
                b1->position.y + b1->size.y > b2->position.y;

    return xhit & yhit;
}