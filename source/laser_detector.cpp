#include "laser_detector.hpp"

LaserDetector::LaserDetector(Vector2 position) : Component(position, COMPONENT_SIZE) {
    
}

void LaserDetector::draw() {
    DrawRectangleV(position, COMPONENT_SIZE, DARKGRAY);
}

Vector2 LaserDetector::get_position() {
    return position;
}

Hitbox LaserDetector::get_hitbox() {
    Hitbox hitbox;
    hitbox.size.x = this->size.x - 10;
    hitbox.size.y = this->size.y;
    hitbox.position = this->position;

    return hitbox;
}
