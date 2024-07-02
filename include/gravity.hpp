#pragma once

#include "../include/force_generator.hpp"

class GravityForceGenerator : public ForceGenerator {
    public:
        GravityForceGenerator();
        ~GravityForceGenerator();

        void apply(SystemState *system);

        double potentialEnergy(SystemState *system, double height_0, bool reverse);

        double m_g;
};
