#include "../include/gravity.hpp"

GravityForceGenerator::GravityForceGenerator() {
    m_g = 9.81;
}

GravityForceGenerator::~GravityForceGenerator() {}

void GravityForceGenerator::apply(SystemState *system) {

    for(int i=0; i<system->n; i++) {
        system->a_y[i] -= m_g;
    }
}

double GravityForceGenerator::potentialEnergy(SystemState *system, double height_0, bool reverse) {
    double pe = 0;
    int sign = reverse ? -1 : 1;
    for(int i=0; i<system->n; i++) {
        pe += system->m[i] * m_g * (system->p_y[i] - height_0);
    }
    return pe;
}
