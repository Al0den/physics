#pragma once

#include "../include/force_generator.hpp"

class Static : public ForceGenerator {
    public:
        Static();
        ~Static();
        
        void initialize(int index, double x, double y);
        void apply(SystemState *system);

    private:
        int p_index;
        double m_x;
        double m_y;
};
