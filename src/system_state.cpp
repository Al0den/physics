#include "../include/system_state.hpp"

#include <cstdlib>
#include <cstring>

#include <stdio.h>

SystemState::SystemState() {
    n = 0;
    dt = 0.0;

    a_x = nullptr;
    a_y = nullptr;

    v_x = nullptr;
    v_y = nullptr;

    p_x = nullptr;
    p_y = nullptr;

    theta = nullptr;
    v_theta = nullptr;
    a_theta = nullptr;

    f_x = nullptr;
    f_y = nullptr;

    m = nullptr;
}

bool SystemState::setObjectsCount(int count) {
    if ( n >= count ) {
        return false;
    } else if(n == 0) {
        n = count;

        a_x = new double[n];
        a_y = new double[n];

        v_x = new double[n];
        v_y = new double[n];

        p_x = new double[n];
        p_y = new double[n];

        theta = new double[n];
        v_theta = new double[n];
        a_theta = new double[n];

        f_x = new double[n];
        f_y = new double[n];

        m = new double[n];
    } else {
        n = count;

        a_x = (double*)realloc(a_x, sizeof(double) * n);
        a_y = (double*)realloc(a_y, sizeof(double) * n);

        v_x = (double*)realloc(v_x, sizeof(double) * n);
        v_y = (double*)realloc(v_y, sizeof(double) * n);

        p_x = (double*)realloc(p_x, sizeof(double) * n);
        p_y = (double*)realloc(p_y, sizeof(double) * n);

        theta = (double*)realloc(theta, sizeof(double) * n);
        v_theta = (double*)realloc(v_theta, sizeof(double) * n);
        a_theta = (double*)realloc(a_theta, sizeof(double) * n);

        f_x = (double*)realloc(f_x, sizeof(double) * n);
        f_y = (double*)realloc(f_y, sizeof(double) * n);

        m = (double*)realloc(m, sizeof(double) * n);
    }

    return true;
}

void SystemState::reset() {
    for (int i=0; i<n; i++) {
        a_x[i] = 0;
        a_y[i] = 0;
        v_x[i] = 0;
        v_y[i] = 0;
        p_x[i] = 0;
        p_y[i] = 0;
        theta[i] = 0;
        v_theta[i] = 0;
        a_theta[i] = 0;
        f_x[i] = 0;
        f_y[i] = 0;
        m[i] = 0;
    }
}

double SystemState::kineticEnergy() {
    double energy = 0.0;
    
    for (int i=0; i<n; i++) {
        energy += 0.5 * m[i] * (v_x[i]*v_x[i] + v_y[i]*v_y[i]);
    }

    return energy;
}

void SystemState::destroy() {
    if (n > 0) {
        delete[] a_x;
        delete[] a_y;
        delete[] v_x;
        delete[] v_y;
        delete[] p_x;
        delete[] p_y;
        delete[] theta;
        delete[] v_theta;
        delete[] a_theta;
        delete[] f_x;
        delete[] f_y;
        delete[] m;

        a_x = nullptr;
        a_y = nullptr;
        v_x = nullptr;
        v_y = nullptr;
        p_x = nullptr;
        p_y = nullptr;
        theta = nullptr;
        v_theta = nullptr;
        a_theta = nullptr;
        f_x = nullptr;
        f_y = nullptr;
        m = nullptr;
    }

    n = 0;
}

void SystemState::copy(SystemState *ori) {
    setObjectsCount(ori->n);
    dt = ori->dt;

    memcpy(a_x, ori->a_x, sizeof(double) * n);
    memcpy(a_y, ori->a_y, sizeof(double) * n);
    memcpy(v_x, ori->v_x, sizeof(double) * n);
    memcpy(v_y, ori->v_y, sizeof(double) * n);
    memcpy(p_x, ori->p_x, sizeof(double) * n);
    memcpy(p_y, ori->p_y, sizeof(double) * n);
    memcpy(theta, ori->theta, sizeof(double) * n);
    memcpy(v_theta, ori->v_theta, sizeof(double) * n);
    memcpy(a_theta, ori->a_theta, sizeof(double) * n);
    memcpy(f_x, ori->f_x, sizeof(double) * n);
    memcpy(f_y, ori->f_y, sizeof(double) * n);
    memcpy(m, ori->m, sizeof(double) * n);
}

void SystemState::clearAccelerations() {
    for (int i=0; i<n; i++) {
        a_x[i] = 0;
        a_y[i] = 0;
    }
}
