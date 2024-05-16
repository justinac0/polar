#pragma once

#include <iostream>
#include <math.h>
#include <vector>

#include <raylib.h>

#include "collision.hpp"
#include "component.hpp"
#include "polarizer.hpp"
#include "laser.hpp"
#include "laser_source.hpp"
#include "laser_detector.hpp"
#include "laser_system.hpp"

class LaserSystem {
    public:
        LaserSystem(LaserSource *source, LaserDetector *detector, float inital_intensity);
        void draw();

        void add_polarizer(Polarizer *polar);
        void reset();
        void integrate(float dt);

    private:
        LaserSource *source;
        LaserDetector *detector;
        std::vector<Polarizer*> polarizers;
        std::vector<Laser> lasers;
        float initial_intensity;
};
