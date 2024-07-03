#include <PhysicsEngine>
#include <RenderEngine>

#include "config.hpp"

#include <chrono>
#include <rk4_ode_solver.hpp>
#include <string>
#include <unistd.h>

int main() {
    RigidBodySystem system;
    rend::RenderEngine renderer(width, height, REND_INFOBOX);

    system.initialize(new Rk4OdeSolver);

    int nb = 4;

    system.addForceGenerator(new GravityForceGenerator);
    system.addForceGenerator(new StaticForceGenerator(0, 0, 0));
    for(int i=0; i<nb; i++) {
        system.addRigidBody(new RigidBody(pendulum_l * i, 0, 0, 1, 0));
        if (i < nb - 1) {
            system.addForceGenerator(new SpringForceGenerator(i, i+1, pendulum_l, 1000000));
        }
    }

    system.updateRenderer(&renderer);

    renderer.info_box->setRowCol(4, 1);

    renderer.setZoomFactor(250);

    double simulation_elapsed_s = 0.0;
    double next_display_s = 0;
    
    renderer.info_box->setName(0, 0, "E.M"); 
    renderer.info_box->setName(1, 0, "Temps simulation");
    renderer.info_box->setName(2, 0, "Temps reel");
    renderer.info_box->setName(3, 0, "Vitesse");

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();

    while(renderer.handleEvents()) {
        if (renderer.paused) {
            continue;
        }

        while (next_display_s > simulation_elapsed_s) {
            system.process(dt, 1);
            simulation_elapsed_s += dt;
        }

        double temps_reel = std::chrono::duration_cast<std::chrono::milliseconds>(current - begin).count() / 1000.0;
        double temps_reel_pus = std::chrono::duration_cast<std::chrono::microseconds>(current - begin).count();
        double speed_ratio = simulation_elapsed_s / temps_reel;

        renderer.info_box->setValue(1, 0, std::to_string(simulation_elapsed_s).substr(0, std::to_string(simulation_elapsed_s).find(".") + 2) + "s");
        renderer.info_box->setValue(2, 0, std::to_string(temps_reel).substr(0, std::to_string(temps_reel).find(".") + 2) + "s");
        renderer.info_box->setValue(3, 0, std::to_string(speed_ratio).substr(0, std::to_string(speed_ratio).find(".") + 4) + "x");

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        next_display_s += render_dt / 1000 * time_speed;

        double time_spent = std::chrono::duration_cast<std::chrono::microseconds>(end - current).count();

        int time_to_sleep = (render_dt * 1000 - time_spent);

        if (time_to_sleep > 0) {
            usleep(time_to_sleep);
        }

        current = std::chrono::steady_clock::now();
    }
}
