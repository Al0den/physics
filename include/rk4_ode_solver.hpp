#pragma once

#include "../include/ode_solver.hpp"

enum RkStage {
    Stage1,
    Stage2,
    Stage3,
    Stage4,
    Complete,
    Undefined
};

class Rk4OdeSolver : public OdeSolver {
    public:
        
    public:
        Rk4OdeSolver();
        ~Rk4OdeSolver();

        virtual void start(SystemState *initial, double dt);
        virtual bool step(SystemState *state);
        virtual void solve(SystemState *system);
        virtual void end(SystemState *system);

        SystemState m_initialState;
        SystemState m_accumulator;

        int m_stage;
    protected:
        int getNextStage(int stage);

    private:
        int m_next_stage;

};
