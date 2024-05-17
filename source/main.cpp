#include <raylib.h>
#define WINDOW_WIDTH 1280 
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "polar"

#include <iostream>

#include "resources.hpp"
#include "laser_source.hpp"
#include "laser_detector.hpp"
#include "laser_system.hpp"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    load_resources(); // we need fonts...
    Font font = get_font();

    Vector2 offset;
    offset.x = (WINDOW_WIDTH / 2.);
    offset.y = (WINDOW_HEIGHT / 2.);

    Camera2D camera;
    camera.target = {0, 0};
    camera.offset = offset;
    camera.rotation = 0;
    camera.zoom = 1;

#ifdef POLAR_3
    // 3 Polar Setup
    LaserSource source({-250, 0});
    LaserDetector detector({200, 0});    // I1
    Polarizer polar1({-100, 0}, 0); // I2
    Polarizer polar2({50, 0}, 0);   // I3

    LaserSystem system(&source, &detector, 1);
    system.add_polarizer(&polar1);
    system.add_polarizer(&polar2);
#endif

#ifdef POLAR_2
    // 2 Polar Setup
    LaserSource source({-250, 0});
    LaserDetector detector({200, 0});   // I1
    Polarizer polar1({-25, 0}, 0); // I2

    LaserSystem system(&source, &detector, 1);
    system.add_polarizer(&polar1);
#endif

    float t = 0.0;
    float dt = 1.;

    float current_time = GetTime();

    int pcount = system.get_polarizer_count();

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
        ClearBackground({0, 100, 255, 240});
        DrawRectangle(60, 60, WINDOW_WIDTH - 120, WINDOW_HEIGHT - 120, {0, 0, 0, 200});
        DrawRectangleLines(60, 60, WINDOW_WIDTH - 120, WINDOW_HEIGHT - 120, WHITE);

        if (pcount == 1) {
            DrawTextEx(font, "System: 2 Polar", {10, 10}, 48, 2, WHITE);
        } else if (pcount == 2) {
            DrawTextEx(font, "System: 3 Polar", {10, 10}, 48, 2, WHITE);
        } else {
            // ...
        }

        BeginMode2D(camera);
        system.draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
