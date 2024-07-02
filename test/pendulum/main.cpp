#include "../../include/physics.hpp"
#include "../../../render_engine/include/renderer.hpp"

#include "config.hpp"

int main() {
    SystemState system;
    GravityForceGenerator gravity;
    EulerOdeSolver solver;
    //Rk4OdeSolver solver;
    rend::RenderEngine renderer(width, height, REND_GRID);

    system.setObjectsCount(2);
    system.reset();
    
    system.p_x[0] = 0.0;
    system.p_y[0] = 0.0;

    system.p_x[1] = pendulum_l;
    system.p_y[1] = 0.0;

    system.m[0] = 1;
    system.m[1] = 1;
    
    Static static1;
    static1.initialize(0, 0.0, 0.0);

    Spring spring1;

    spring1.initialize(0, 1, pendulum_l, 10000);

    double initial_energy = gravity.potentialEnergy(&system, 0, true) + spring1.potentialEnergy(&system) + system.kineticEnergy();

    double rad = 0.05;
    double w = 0.1;

    rend::Ball b1 = {&system.p_x[0], &system.p_y[0], &rad, 255, 255, 255, 0};
    rend::Ball b2 = {&system.p_x[1], &system.p_y[1], &rad, 255, 255, 255, 0};

    double rest_length = pendulum_l;

    rend::Spring s1 = {&system.p_x[0], &system.p_y[0], &system.p_x[1], &system.p_y[1], &rest_length, &w, 255, 255, 255, 0};

    renderer.addBall(b1);
    renderer.addBall(b2);
    renderer.addSpring(s1);

    renderer.setZoomFactor(250);

    double simulation_elapsed_s = 0.0;
    double next_display_s = 0;
    
    int prev_simu_info = 0;


    while(renderer.handleEvents()) {
        while (next_display_s > simulation_elapsed_s) {
            gravity.apply(&system);
            spring1.apply(&system);
            static1.apply(&system);
            solver.start(&system, dt);
            while (true) {
                const bool complete = solver.step(&system);
                solver.solve(&system);
                
                if(complete) break;
            }

            solver.end(&system);

            simulation_elapsed_s += dt;
            system.clearAccelerations();
        }

        SDL_Delay(render_dt);
        next_display_s += render_dt / 1000 * time_speed;
    }
}
