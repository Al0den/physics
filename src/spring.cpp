#include "../include/spring.hpp"
#include "../include/rigid_body_system.hpp"

#include <math.h>
#include <stdio.h>

SpringForceGenerator::SpringForceGenerator(int p1, int p2, double restLength, double springConstant) {
    initialize(p1, p2, restLength, springConstant);
    force_type = FORCE_SPRING;
}

SpringForceGenerator::~SpringForceGenerator() {}

void SpringForceGenerator::initialize(int p1, int p2, double restLength, double springConstant) {
    p1_index = p1;
    p2_index = p2;
    m_restLength = restLength;
    m_springConstant = springConstant;
}

void SpringForceGenerator::apply(SystemState *system) {
    double p1_x = system->p_x[p1_index];
    double p1_y = system->p_y[p1_index];

    double p2_x = system->p_x[p2_index];
    double p2_y = system->p_y[p2_index];

    double distance = sqrt(pow(p2_x - p1_x, 2) + pow(p2_y - p1_y, 2));
    double force = m_springConstant * (distance - m_restLength);

    double angle = atan2(p2_y - p1_y, p2_x - p1_x);
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    system->f_x[p1_index] += force * cos_angle / system->m[p1_index];
    system->f_y[p1_index] += force * sin_angle / system->m[p1_index];

    system->f_x[p2_index] -= force * cos_angle / system->m[p2_index];
    system->f_y[p2_index] -= force * sin_angle / system->m[p2_index];
}

double SpringForceGenerator::potentialEnergy(void *system) {
    return 0;
    RigidBodySystem *real_sys = (RigidBodySystem*)system;
    double p1_x = real_sys->getRigidBody(p1_index)->p_x;
    double p1_y = real_sys->getRigidBody(p1_index)->p_y;
    double p2_x = real_sys->getRigidBody(p2_index)->p_x;
    double p2_y = real_sys->getRigidBody(p2_index)->p_y;

    double distance = sqrt(pow(p2_x - p1_x, 2) + pow(p2_y - p1_y, 2));
    return 0.5 * m_springConstant * pow(distance - m_restLength, 2);
}

