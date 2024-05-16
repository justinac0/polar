#include "laser_source.hpp"

LaserSource::LaserSource(Vector2 position) : Component(position, COMPONENT_SIZE) {

}

void LaserSource::draw() {
    DrawRectangleV(position, COMPONENT_SIZE, DARKGRAY);
}

Vector2 LaserSource::get_position() {
    return this->position;
}