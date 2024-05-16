#include "laser_system.hpp"

float calculate_intensity(float initial, float angle) {
    float rad = angle * PI / 180;
    return initial * powf(cosf(rad), 2);
}


bool do_spin(bool *enabled, Vector2 position, Vector2 mouse, float *theta) {
    float base_radius = 16;
    float dot_radius = 8;
    float rad = *theta * PI/180;

    Vector2 dp;
    dp.x = cos(rad) * base_radius + position.x;
    dp.y = -sin(rad) * base_radius + position.y;

    Hitbox hdot;
    hdot.position = position;
    hdot.size.x = base_radius;
    hdot.size.y = base_radius;

    Hitbox mdot;
    mdot.position = mouse;
    mdot.size = {base_radius,base_radius};

    char interact = 0;
    Color dot_color = DARKGREEN;
    if (is_hit(&hdot, &mdot) && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        *enabled = !(*enabled);
        interact++;
    }

    if (*enabled) {
        dot_color = GREEN;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
            *theta += 5;
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
            *theta -= 5;
        }

        DrawCircle(position.x, position.y, base_radius + 4, DARKGREEN);
    }

    DrawCircle(position.x, position.y, base_radius, DARKGRAY);
    DrawCircle(dp.x, dp.y, dot_radius, dot_color);

    return interact > 0 && *enabled == false; // update was made if true
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

    Vector2 window_size;
    window_size.x = GetScreenWidth();
    window_size.y = GetScreenHeight();

    Vector2 mp = GetMousePosition();
    mp.x -= window_size.x / 2;
    mp.y -= window_size.y / 2;
    for (Polarizer *p : this->polarizers) {
        p->draw();

        Vector2 offset = p->get_position();
        offset.x += 25;
        offset.y -= 100;

        if (do_spin(&p->ui_enabled, offset, mp, &p->rotation)) {
             reset();
        }
    }

    this->source->draw();
    this->detector->draw();

}

int LaserSystem::get_polarizer_count() {
    return polarizers.size();
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