#pragma once

#include "../include/system_state.hpp"

class OdeSolver {
    public:
        OdeSolver();
        virtual ~OdeSolver();
        
        virtual void start(SystemState *initial, double dt) = 0;
        virtual bool step(SystemState *system) = 0;
        virtual void solve(SystemState *system) = 0;
        virtual void end(SystemState *system) = 0;
    protected:
        double m_dt;
};
