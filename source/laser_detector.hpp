#pragma once

#include <raylib.h>

#include "collision.hpp"
#include "component.hpp"

class LaserDetector : Component {
    public:
        LaserDetector(Vector2 position);
        void draw();
        Vector2 get_position();
        Hitbox get_hitbox();
};
