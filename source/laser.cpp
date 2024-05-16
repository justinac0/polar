#include "laser.hpp"

Laser::Laser(Vector2 start, Vector2 direction, float intensity) : Component(start, {20, 20}) {
    this->start = start;
    this->end = start;
    this->direction = direction;
    this->intensity = intensity;
}

Laser::~Laser() {}

void Laser::draw() {
    unsigned char alpha = 255 * intensity; 
    Color c = {255, 0, 0, alpha};
    DrawLineEx(this->start, this->end, 20, c);

    Hitbox hitbox = get_hitbox();
    DrawRectangleV(hitbox.position, hitbox.size, {0, 255, 0, 100});
    DrawText(std::to_string(intensity).c_str(), start.x, hitbox.position.y-50, 14, WHITE);
}

void Laser::integrate(float dt) {
    if (has_hit)
        return;

    float dx = this->end.x - this->start.x;
    float dy = this->end.x - this->start.x;
    float sqr_length = dx * dx + dy * dy;
    float length = sqrtf(sqr_length);

    if (length >= MAX_LASER_LENGTH)
        return;

    this->end.x += this->direction.x * MARCH_LENGTH * dt;
    this->end.y += this->direction.y * MARCH_LENGTH * dt;
}

Hitbox Laser::get_hitbox() {
    Hitbox hitbox;
    hitbox.size.x = 1;
    hitbox.size.y = this->size.y;
    hitbox.position.x = this->end.x;
    hitbox.position.y = this->end.y - this->size.y / 2;

    return hitbox;
}
