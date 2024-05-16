#pragma once

#include <raylib.h>

#include "collision.hpp"
#include "component.hpp"

class Polarizer : Component {
    public:
        Polarizer(Vector2 position, float rotation);
        void draw();

        void set_rotation(float angle);
        Hitbox get_hitbox();
        float rotation;
};
