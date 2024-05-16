#include "laser_system.hpp"

float calculate_intensity(float initial, float angle) {
    float rad = angle * PI / 180;
    return initial * powf(cosf(rad), 2);
}

LaserSystem::LaserSystem(LaserSource *source, LaserDetector *detector, float initial_intensity) {
    this->source = source;
    this->detector = detector;
    this->initial_intensity = initial_intensity;
    
    reset();
}

void LaserSystem::draw() {
    for (Laser &l : this->lasers) {
        l.draw();
    }

    for (Polarizer *p : this->polarizers) {
        p->draw();
    }

    this->source->draw();
    this->detector->draw();
}

void LaserSystem::add_polarizer(Polarizer *polar) {
    this->polarizers.push_back(polar);
}

void LaserSystem::reset() {
    lasers.clear();

    Vector2 laser_offset = source->get_position();
    laser_offset.x += 40;
    laser_offset.y += 25;

    Laser laser(laser_offset, {1, 0}, initial_intensity);

    lasers.push_back(laser);
}

void LaserSystem::integrate(float dt) {
    for (Laser &l : this->lasers) {
        Hitbox lhit = l.get_hitbox();

        for (int i = 0; i < (int)polarizers.size(); i++) {
            Polarizer *p = polarizers[i];
            Hitbox phit = p->get_hitbox(); 
  
            if (is_hit(&phit, &lhit) && !l.has_hit) {
                l.has_hit = true;

                Vector2 position;
                position.x = phit.position.x + phit.size.x;
                position.y = l.end.y;

                // first polarizer
                float relative_rotation = polarizers[i]->rotation;
                if (i > 0) {
                    relative_rotation = abs(polarizers[i-1]->rotation - polarizers[i]->rotation);
                }

                // n polarizer
                float intensity = calculate_intensity(l.intensity, relative_rotation);
                if (intensity <= 0)
                    break;

                Laser new_laser(position, l.direction, intensity);
                this->lasers.push_back(new_laser);
                break;
            }
        }

        // Has laser hit the detector?
        Hitbox dhit = detector->get_hitbox();
        if (is_hit(&lhit, &dhit)) {
            l.has_hit = true;
            break;
        }

        l.integrate(dt);
    }
}