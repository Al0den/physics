#include "../include/rk4_ode_solver.hpp"

#include <stdio.h>

Rk4OdeSolver::Rk4OdeSolver() {
    m_stage = m_next_stage = Stage1;
}

Rk4OdeSolver::~Rk4OdeSolver() {
    m_initialState.destroy();
    m_accumulator.destroy();
}

void Rk4OdeSolver::start(SystemState *initial, double dt) {
    OdeSolver::start(initial, dt);

    m_initialState.copy(initial);
    m_accumulator.copy(initial);

    m_stage = Stage1;
}

bool Rk4OdeSolver::step(SystemState *state) {
    switch(m_stage) {
        case Stage1:
            state->dt = 0.0;
            break;
        case Stage2:
        case Stage3:
            for (int i=0; i<state->n; i++) {
                state->v_theta[i] = m_initialState.v_theta[i] + state->a_theta[i] * m_dt / 2.0;
                state->theta[i] = m_initialState.theta[i] + state->v_theta[i] * m_dt / 2.0;
                state->v_x[i] = m_initialState.v_x[i] + state->a_x[i] * m_dt / 2.0;
                state->p_x[i] = m_initialState.p_x[i] + state->v_x[i] * m_dt / 2.0;
                state->v_y[i] = m_initialState.v_y[i] + state->a_y[i] * m_dt / 2.0;
                state->p_y[i] = m_initialState.p_y[i] + state->v_y[i] * m_dt / 2.0;
            }
            state->dt = m_dt / 2.0;
            break;
        case Stage4:
            for (int i=0; i<state->n; i++) {
                state->v_theta[i] = m_initialState.v_theta[i] + state->a_theta[i] * m_dt;
                state->theta[i] = m_initialState.theta[i] + state->v_theta[i] * m_dt;
                state->v_x[i] = m_initialState.v_x[i] + state->a_x[i] * m_dt;
                state->p_x[i] = m_initialState.p_x[i] + state->v_x[i] * m_dt;
                state->v_y[i] = m_initialState.v_y[i] + state->a_y[i] * m_dt;
                state->p_y[i] = m_initialState.p_y[i] + state->v_y[i] * m_dt;
            }
            state->dt = m_dt;
            break;
        default:
            break;
    }   
    m_next_stage = getNextStage(m_stage);

    return m_next_stage == Complete;
}

void Rk4OdeSolver::solve(SystemState *system) {
    double stage_weight = 0.0;
    switch(m_stage) {
        case Stage1: stage_weight = 1.0; break;
        case Stage2: stage_weight = 2.0; break;
        case Stage3: stage_weight = 2.0; break;
        case Stage4: stage_weight = 1.0; break;
        default: stage_weight = 0.0;
    }

    for(int i=0; i<system->n; i++) {
        m_accumulator.v_theta[i] += (m_dt / 6.0) * system->a_theta[i] * stage_weight;
        m_accumulator.theta[i] += (m_dt / 6.0) * system->v_theta[i] * stage_weight;
        m_accumulator.v_x[i] += (m_dt / 6.0) * system->a_x[i] * stage_weight;
        m_accumulator.v_y[i] += (m_dt / 6.0) * system->a_y[i] * stage_weight;
        m_accumulator.p_x[i] += (m_dt / 6.0) * system->v_x[i] * stage_weight;
        m_accumulator.p_y[i] += (m_dt / 6.0) * system->v_y[i] * stage_weight;
    }

    if(m_stage == Stage4) {
        for (int i = 0; i < system->n; ++i) {
            system->v_theta[i] = m_accumulator.v_theta[i];
            system->theta[i] = m_accumulator.theta[i];
            system->v_x[i] = m_accumulator.v_x[i];
            system->v_y[i] = m_accumulator.v_y[i];
            system->p_x[i] = m_accumulator.p_x[i];
            system->p_y[i] = m_accumulator.p_y[i];
        }
    }

    m_stage = m_next_stage;
}

void Rk4OdeSolver::end(SystemState *system) {
    OdeSolver::end(system);
    
    m_stage = m_next_stage = Undefined;
}

int Rk4OdeSolver::getNextStage(int stage) {
    switch(stage){
        case Stage1: return Stage2;
        case Stage2: return Stage3;
        case Stage3: return Stage4;
        case Stage4: return Complete;
        default: return Undefined;
    }
}
