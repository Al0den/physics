#pragma once

#include "../include/force_generator.hpp"

class Spring : public ForceGenerator {
    public:
        Spring();
        ~Spring();

        void apply(SystemState *system);
        void initialize(int p1, int p2, double restLength, double springConstant);

        double potentialEnergy(SystemState *system);
            
        void setP1Index(int p1);
        void setP2Index(int p2);
        void setRestLength(double restLength);
        void setSpringConstant(double springConstant);

        int p1_index;
        int p2_index;


    private:
        double m_restLength;
        double m_springConstant;
};
