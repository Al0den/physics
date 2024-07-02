#include "../include/static.hpp"

Static::Static() {
    p_index = -1;
    m_x = -1.0;
    m_y = -1.0;
}

Static::~Static() {}

void Static::initialize(int index, double x, double y) {
    p_index = index;
    m_x = x;
    m_y = y;
}

void Static::apply(SystemState *system) {
    if(p_index == -1) {
        return;
    }
    system->f_x[p_index] = 0;
    system->f_y[p_index] = 0;
    system->a_x[p_index] = 0;
    system->a_y[p_index] = 0;
    system->v_x[p_index] = 0;
    system->v_y[p_index] = 0;
    system->p_x[p_index] = m_x;
    system->p_y[p_index] = m_y;
}
