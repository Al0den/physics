#include "../include/rigid_body.hpp"

RigidBody::RigidBody(double x, double y, double theta, double m, double I) {
    p_x = x;
    p_y = y;

    v_x = 0;
    v_y = 0;

    this->theta = theta;
    v_theta = 0;

    this->m = m;
    this->I = I;
}
