#pragma once

#include "../include/force_generator.hpp"

class BoundForceGenerator : public ForceGenerator {
    public:
        BoundForceGenerator(double x, double y, int index);
        virtual ~BoundForceGenerator();

        virtual void apply(SystemState *system);

        virtual double potentialEnergy(void *system);

        double m_x;
        double m_y;
        int index;
};
