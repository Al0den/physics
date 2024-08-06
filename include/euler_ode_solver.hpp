#pragma once

#include "../include/ode_solver.hpp"

class EulerOdeSolver : public OdeSolver {
    public:
        EulerOdeSolver();
        virtual ~EulerOdeSolver();
        
        void start(SystemState *initial, double dt);
        bool step(SystemState *system);
        void solve(SystemState *system);
        void end(SystemState *system);
};
