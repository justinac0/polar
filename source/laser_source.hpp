#pragma once

#include <raylib.h>

#include "component.hpp"

class LaserSource : Component {
    public:
        LaserSource(Vector2 position);
        void draw();

        Vector2 get_position();
};