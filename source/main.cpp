#define WINDOW_WIDTH 840
#define WINDOW_HEIGHT 680
#define WINDOW_TITLE "polar"

#include <iostream>
#include "laser_source.hpp"
#include "laser_detector.hpp"
#include "laser_system.hpp"

bool do_spin(bool *enabled, Vector2 position, Vector2 mouse, float *theta) {
    float base_radius = 16;
    float dot_radius = 8;
    float rad = *theta * PI/180;

    Vector2 dp;
    dp.x = cos(rad) * base_radius + position.x;
    dp.y = -sin(rad) * base_radius + position.y;

    DrawText(std::to_string((int)(*theta) % 360).c_str(), position.x, position.y - 50, 14, WHITE);

    Hitbox hdot;
    hdot.position = position;
    hdot.size.x = base_radius;
    hdot.size.y = base_radius;

    Hitbox mdot;
    mdot.position = mouse;
    mdot.size = {base_radius,base_radius};

    char interact = 0;
    Color dot_color = DARKGRAY;
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

    DrawCircle(position.x, position.y, base_radius, GRAY);
    DrawCircle(dp.x, dp.y, dot_radius, dot_color);

    return interact > 0 && *enabled == false; // update was made if true
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Vector2 offset;
    offset.x = (WINDOW_WIDTH / 2.);
    offset.y = (WINDOW_HEIGHT / 2.);

    Camera2D camera;
    camera.target = {0, 0};
    camera.offset = offset;
    camera.rotation = 0;
    camera.zoom = 1;

    bool t0 = false;
    bool t1 = false;
    float theta0 = 0;
    float theta1 = 0;

#ifdef POLAR_3
    // 3 Polar Setup
    LaserSource source({-250, 0});
    LaserDetector detector({200, 0});    // I1
    Polarizer polar1({-100, 0}, theta0); // I2
    Polarizer polar2({50, 0}, theta1);   // I3

    LaserSystem system(&source, &detector, 1);
    system.add_polarizer(&polar1);
    system.add_polarizer(&polar2);
#endif

#ifdef POLAR_2
    // 2 Polar Setup
    LaserSource source({-250, 0});
    LaserDetector detector({200, 0});   // I1
    Polarizer polar1({-25, 0}, theta0); // I2

    LaserSystem system(&source, &detector, 1);
    system.add_polarizer(&polar1);
#endif

    float t = 0.0;
    float dt = 1 / 1.;

    float current_time = GetTime();

    while (!WindowShouldClose()) {
        float new_time = GetTime();
        float frame_time = new_time - current_time;
        current_time = new_time;

        while (frame_time > 0.0) {
            float delta_time = frame_time > dt ? dt : frame_time;

            system.integrate(dt);

            frame_time -= delta_time;
            t += delta_time;
        }

        if (IsKeyPressed(KEY_R))
            system.reset();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        Vector2 mp = GetMousePosition();
        mp.x -= WINDOW_WIDTH / 2;
        mp.y -= WINDOW_HEIGHT / 2;

        bool a = false;
        bool b = false;

#if POLAR_2
        a = do_spin(&t0, {0, -100}, mp, &theta0);
        if (a) {
             polar1.set_rotation(theta0);
             system.reset();
        }
#endif

#if POLAR_3
        a = do_spin(&t0, {0, -100}, mp, &theta0);
        b = do_spin(&t1, {100, -100}, mp, &theta1);
        if (a | b) {
             polar1.set_rotation(theta0);
             polar2.set_rotation(theta1);
             system.reset();
        }
#endif

        system.draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
