#include "../include/bound.hpp"

#include <stdio.h>

BoundForceGenerator::BoundForceGenerator(double x, double y, int index) {
    m_x = x;
    m_y = y;
    this->index = index;
}

BoundForceGenerator::~BoundForceGenerator() {}

void BoundForceGenerator::apply(SystemState *system) {
    if(system->p_x[index] > m_x) {
        system->p_x[index] = m_x;
        if(system->v_x[index] > 0) {
            system->v_x[index] = 0;
        }
        if(system->a_x[index] > 0) {
            system->a_x[index] = 0;
        }

    }
    if(system->p_y[index] > m_y) {
        system->p_y[index] = m_y;
        if(system->v_y[index] > 0) {
            system->v_y[index] = 0;
        }
        if(system->a_y[index] > 0) {
            system->a_y[index] = 0;
        }
    }

    if(system->p_x[index] < -m_x) {
        system->p_x[index] = -m_x;
        if (system->v_x[index] < 0) {
            system->v_x[index] = 0;
        }
        if (system->a_x[index] < 0) {
            system->a_x[index] = 0;
        }
    }

    if(system->p_y[index] < -m_y) {
        system->p_y[index] = -m_y;
        if (system->v_y[index] < 0) {
            system->v_y[index] = 0;
        }
        if (system->a_y[index] < 0) {
            system->a_y[index] = 0;
        }
    }

}

double BoundForceGenerator::potentialEnergy(void *system) {
    return 0;
}
