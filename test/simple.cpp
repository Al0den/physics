#include "../include/system_state.hpp"
#include "../include/euler_ode_solver.hpp"

#include <stdio.h>

int main() {
    SystemState system;

    system.setObjectsCount(1);

    system.n = 1;
    system.a_x[0] = 0.1;

    double dt = (double)1/60;

    EulerOdeSolver solver;
    solver.start(&system, dt);
    
    int steps = 0;
    while (true) {
        steps++;
        solver.solve(&system);
        printf("x: %f, v: %f\n", system.p_x[0], system.v_x[0]);
    }
}

