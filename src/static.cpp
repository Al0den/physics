#include "../include/static.hpp"

StaticForceGenerator::StaticForceGenerator(int index, double x, double y) {
    p_index = index;
    m_x = x;
    m_y = y;
}

StaticForceGenerator::~StaticForceGenerator() {}

void StaticForceGenerator::initialize(int index, double x, double y) {
    p_index = index;
    m_x = x;
    m_y = y;
}

void StaticForceGenerator::apply(SystemState *system) {
    system->f_x[p_index] = 0;
    system->f_y[p_index] = 0;
    system->a_x[p_index] = 0;
    system->a_y[p_index] = 0;
    system->v_x[p_index] = 0;
    system->v_y[p_index] = 0;
    system->p_x[p_index] = m_x;
    system->p_y[p_index] = m_y;
}

double StaticForceGenerator::potentialEnergy(void *system) {
    return 0;
}
