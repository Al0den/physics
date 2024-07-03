#pragma once

#include "../include/force_generator.hpp"
#include "../include/rigid_body_system.hpp"

class SpringForceGenerator : public ForceGenerator {
    public:
        SpringForceGenerator(int p1, int p2, double restLength, double springConstant);
        ~SpringForceGenerator();

        virtual void apply(SystemState *system);

        virtual double potentialEnergy(void *system);
            
        void setP1Index(int p1);
        void setP2Index(int p2);
        void setRestLength(double restLength);
        void setSpringConstant(double springConstant);

        int p1_index;
        int p2_index;

        double m_restLength;
    private:
        double m_springConstant;

        void initialize(int p1, int p2, double restLength, double springConstant);
};
