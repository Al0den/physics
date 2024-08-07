#include "../include/friction.hpp"

#include <stdio.h>

FrictionForceGenerator::FrictionForceGenerator(double coeff) {
    friction_coeff = coeff;
}

FrictionForceGenerator::~FrictionForceGenerator() {}

void FrictionForceGenerator::apply(SystemState *system) {
    for(int i=0; i<system->n; i++) {
        system->f_x[i] -= friction_coeff * system->v_x[i];
        system->f_y[i] -= friction_coeff * system->v_y[i];
    }
}

double FrictionForceGenerator::potentialEnergy(void *system) {
    return 0;
}
