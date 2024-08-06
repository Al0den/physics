#pragma once

#include "../include/force_generator.hpp"
#include "../include/rigid_body_system.hpp"
#include "../include/static.hpp"

class StaticForceGenerator : public ForceGenerator {
    public:
        StaticForceGenerator(int index, double x, double y);
        virtual ~StaticForceGenerator();
        
        void initialize(int index, double x, double y);
        virtual void apply(SystemState *system);
        virtual double potentialEnergy(void *system);

        int force_type;

        double m_x;
        double m_y;

        bool static_x;
        bool static_y;
    private:
        int p_index;

};
