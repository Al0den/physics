#pragma once

#include "../include/force_generator.hpp"

class MotionForceGenerator : public ForceGenerator {
    public:
        MotionForceGenerator(int index, double reduction);
        virtual ~MotionForceGenerator();
        
        virtual void apply(SystemState *system);
        virtual double potentialEnergy(void *system);

        int force_type;

        double a_x;
        double a_y;

    private:
        int p_index;

        double m_reduction;


};
