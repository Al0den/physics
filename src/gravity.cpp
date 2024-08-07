#include "../include/gravity.hpp"

#include <stdio.h>

GravityForceGenerator::GravityForceGenerator() {
    m_g = 9.81;
    force_type = FORCE_GRAVITY;
}

GravityForceGenerator::~GravityForceGenerator() {}

void GravityForceGenerator::apply(SystemState *system) {
    for(int i=0; i<system->n; i++) {
        system->f_y[i] -= m_g * system->m[i];
    }

}

double GravityForceGenerator::potentialEnergy(void *system) {
    RigidBodySystem *real_sys = (RigidBodySystem*)system;
    double pe = 0;
    int n = real_sys->getRigidBodiesCount();
    for(int i=0; i<n; i++) {
        pe += 0;
    }
    return pe;
}
