#include "../include/spring.hpp"

#include <math.h>
#include <stdio.h>

Spring::Spring() {
    p1_index = -1;
    p2_index = -1;
    m_restLength = -1.0;
    m_springConstant = -1.0;
}

Spring::~Spring() {}

void Spring::initialize(int p1, int p2, double restLength, double springConstant) {
    p1_index = p1;
    p2_index = p2;
    m_restLength = restLength;
    m_springConstant = springConstant;
}

void Spring::apply(SystemState *system) {
    if(p1_index == -1 || p2_index == -1) {
        return;
    }

    double p1_x = system->p_x[p1_index];
    double p1_y = system->p_y[p1_index];

    double p2_x = system->p_x[p2_index];
    double p2_y = system->p_y[p2_index];

    double distance = sqrt(pow(p2_x - p1_x, 2) + pow(p2_y - p1_y, 2));
    double force = m_springConstant * (distance - m_restLength);

    double angle = atan2(p2_y - p1_y, p2_x - p1_x);

    double rel_vel = (system->v_x[p2_index] - system->v_x[p1_index]) * cos(angle) + (system->v_y[p2_index] - system->v_y[p1_index]) * sin(angle);

    system->a_x[p1_index] += force * cos(angle) / system->m[p1_index];
    system->a_y[p1_index] += force * sin(angle) / system->m[p1_index];

    system->a_x[p2_index] -= force * cos(angle) / system->m[p2_index];
    system->a_y[p2_index] -= force * sin(angle) / system->m[p2_index];
}

double Spring::potentialEnergy(SystemState *system) {
    if(p1_index == -1 || p2_index == -1) {
        return 0;
    }
    double p1_x = system->p_x[p1_index];
    double p1_y = system->p_y[p1_index];
    double p2_x = system->p_x[p2_index];
    double p2_y = system->p_y[p2_index];
    double distance = sqrt(pow(p2_x - p1_x, 2) + pow(p2_y - p1_y, 2));
    return 0.5 * m_springConstant * pow(distance - m_restLength, 2);
}

