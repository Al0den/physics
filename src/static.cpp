#include "../include/static.hpp"

StaticForceGenerator::StaticForceGenerator(int index, double x, double y) {
    p_index = index;
    m_x = x;
    m_y = y;

    static_x = true;
    static_y = true;
}

StaticForceGenerator::~StaticForceGenerator() {}

void StaticForceGenerator::initialize(int index, double x, double y) {
    p_index = index;
    m_x = x;
    m_y = y;
}

void StaticForceGenerator::apply(SystemState *system) {
    if(static_x) {
        system->f_x[p_index] = 0;
        system->v_x[p_index] = 0;
        system->p_x[p_index] = m_x;
        system->a_x[p_index] = 0;
    }
    if(static_y) {
        system->a_y[p_index] = 0;
        system->f_y[p_index] = 0;
        system->v_y[p_index] = 0;
        system->p_y[p_index] = m_y;
    }
}

double StaticForceGenerator::potentialEnergy(void *system) {
    return 0;
}
