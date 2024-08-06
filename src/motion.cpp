#include "../include/motion.hpp"

#include <assert.h>

MotionForceGenerator::MotionForceGenerator(int index, double reduction) {
    p_index = index;
    m_reduction = reduction;

    assert(abs(reduction) <= 1);
}

MotionForceGenerator::~MotionForceGenerator() {}

void MotionForceGenerator::apply(SystemState *state) {
    state->f_x[p_index] += a_x * state->m[p_index]; 
    state->f_y[p_index] += a_y * state->m[p_index];

    a_x *= m_reduction;
    a_y *= m_reduction;
}

double MotionForceGenerator::potentialEnergy(void *system) {
    return 0;
}

