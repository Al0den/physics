#pragma once

#include "../include/force_generator.hpp"
#include "../include/rigid_body_system.hpp"

class GravityForceGenerator : public ForceGenerator {
    public:
        GravityForceGenerator();
        ~GravityForceGenerator();

        virtual void apply(SystemState *system);

        virtual double potentialEnergy(void *system);

        double m_g;
};
