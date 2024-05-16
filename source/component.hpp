#pragma once

#define COMPONENT_SIZE {50, 150}

#include <raylib.h>

class Component {
    public:
        Component(Vector2 position, Vector2 size);
        virtual void draw() = 0;

        Vector2 size;
        Vector2 position;
};