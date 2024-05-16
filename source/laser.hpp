#pragma once

#define MAX_LASER_LENGTH 400 // pixels
#define MARCH_LENGTH 25      // pixels

#include <iostream>
#include <math.h>
#include <raylib.h>

#include "collision.hpp"
#include "component.hpp"

class Laser : Component {
    public:
        Laser(Vector2 start, Vector2 direction, float intensity);
        ~Laser();
        void draw();

        void integrate(float dt);
        Hitbox get_hitbox();
        Vector2 start;
        Vector2 end;
        Vector2 direction;
        float intensity;
        bool has_hit = false;
};
