#include "../include/ode_solver.hpp"

OdeSolver::OdeSolver() {
    m_dt = 0.0;
}

OdeSolver::~OdeSolver() {}

void OdeSolver::start(SystemState *system, double dt) {
    m_dt = dt;
}

bool OdeSolver::step(SystemState *system) {
    return true;
}

void OdeSolver::solve(SystemState *system) {}
void OdeSolver::end(SystemState *system) {}
