#pragma once

#include "../include/force_generator.hpp"
#include "../include/rigid_body_system.hpp"

class FrictionForceGenerator : public ForceGenerator {
    public:
        FrictionForceGenerator(double coeff);
        virtual ~FrictionForceGenerator();

        virtual void apply(SystemState *system);

        virtual double potentialEnergy(void *system);

        double friction_coeff;
};
