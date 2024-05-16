#include "polarizer.hpp"

Polarizer::Polarizer(Vector2 position, float rotation) : Component(position, COMPONENT_SIZE) {
    this->rotation = rotation;
    this->ui_enabled = false;
}

void Polarizer::draw() {
    DrawRectangleV(position, {50, 150}, GRAY);
    DrawRectangleV(position, {50, 50}, DARKGRAY);
}

void Polarizer::set_rotation(float angle) {
    this->rotation = angle;
}

Hitbox Polarizer::get_hitbox() {
    Hitbox hitbox;
    hitbox.size.x = this->size.x - 10;
    hitbox.size.y = this->size.y;
    hitbox.position = this->position;

    return hitbox;
}


Vector2 Polarizer::get_position() {
    return this->position;
}