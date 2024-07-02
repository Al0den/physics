#include "../../include/system_state.hpp"
#include "../../include/gravity.hpp"
#include "../../include/euler_ode_solver.hpp"

#include "collisions.hpp"

#include "render.hpp"
#include "config.hpp"

int main() {
    SystemState system;
    Renderer renderer;
    GravityForceGenerator gravity;
    EulerOdeSolver solver;

    double dt = (double)1/60;

    system.setObjectsCount(1000);
    solver.start(&system, dt);

    for(int i=0; i<system.n; i++) {
        system.p_x[i] = rand() % width;
        system.p_y[i] = rand() % height;
        system.v_x[i] = rand() % 100;
        system.v_y[i] = rand() % 100;
        system.theta[i] = 0;
        system.v_theta[i] = 0;
        system.a_theta[i] = 0;
        system.m[i] = 1;
    }
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return 0;
            }
        }

        gravity.apply(&system);
        solver.solve(&system);
        SolveCollisions(&system);
        renderer.render(&system);


        SDL_Delay (1000/180);
    }
    
    return 0;
}
