#pragma once

#include <raylib.h>

typedef struct {
    Vector2 size;
    Vector2 position;
} Hitbox;

bool is_hit(Hitbox *b1, Hitbox *b2);