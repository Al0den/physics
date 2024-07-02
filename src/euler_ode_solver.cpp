#include "../include/euler_ode_solver.hpp"

EulerOdeSolver::EulerOdeSolver() {}
EulerOdeSolver::~EulerOdeSolver() {}

void EulerOdeSolver::start(SystemState *system, double dt) {
    OdeSolver::start(system, dt);
} 

bool EulerOdeSolver::step(SystemState *system) {
    return true;
}

void EulerOdeSolver::solve(SystemState *system) {
    system->dt = m_dt;

    for (int i=0; i<system->n; i++) {
        system->p_x[i] += system->v_x[i] * m_dt;
        system->p_y[i] += system->v_y[i] * m_dt;
        system->theta[i] += system->v_theta[i] * m_dt;

        system->v_x[i] += system->a_x[i] * m_dt;
        system->v_y[i] += system->a_y[i] * m_dt;
        system->v_theta[i] += system->a_theta[i] * m_dt;

        system->f_x[i] = 0;
        system->f_y[i] = 0;
    }
}

void EulerOdeSolver::end(SystemState *system) {}
