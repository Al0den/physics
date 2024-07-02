#pragma once

#include "../include/system_state.hpp"

class OdeSolver {
    public:
        OdeSolver();
        ~OdeSolver();
        
        void start(SystemState *initial, double dt);
        bool step(SystemState *system);
        void solve(SystemState *system);
        void end(SystemState *system);
    protected:
        double m_dt;
};
