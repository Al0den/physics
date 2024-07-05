#include <RenderEngine>
#include <PhysicsEngine>

#include "config.hpp"

#include <chrono>
#include <rk4_ode_solver.hpp>
#include <string>
#include <unistd.h>

void updateRenderer(rend::RenderEngine *renderer, RigidBodySystem *system);

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

    updateRenderer(&renderer, &system);
    rend::InfoBox* info_box = renderer.getInfoBox();
    info_box->setRowCol(4, 1);

    renderer.setZoomFactor(250);

    double simulation_elapsed_s = 0.0;
    double next_display_s = 0;
    
    info_box->setName(0, 0, "E.M"); 
    info_box->setName(1, 0, "Temps simulation");
    info_box->setName(2, 0, "Temps reel");
    info_box->setName(3, 0, "Vitesse");

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();

    while(renderer.handleEvents()) {
        if (renderer.isPaused()) {
            continue;
        }

        while (next_display_s > simulation_elapsed_s) {
            system.process(dt, 1);
            simulation_elapsed_s += dt;
        }

        double temps_reel = std::chrono::duration_cast<std::chrono::milliseconds>(current - begin).count() / 1000.0;
        double temps_reel_pus = std::chrono::duration_cast<std::chrono::microseconds>(current - begin).count();
        double speed_ratio = simulation_elapsed_s / temps_reel;

        info_box->setValue(1, 0, std::to_string(simulation_elapsed_s).substr(0, std::to_string(simulation_elapsed_s).find(".") + 2) + "s");
        info_box->setValue(2, 0, std::to_string(temps_reel).substr(0, std::to_string(temps_reel).find(".") + 2) + "s");
        info_box->setValue(3, 0, std::to_string(speed_ratio).substr(0, std::to_string(speed_ratio).find(".") + 4) + "x");

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

void updateRenderer(rend::RenderEngine *renderer, RigidBodySystem *system) {
    int n = system->getRigidBodiesCount();
    double ball_radius = 0.05;
    double line_width = 0.1;

    for(int i=0; i<n; i++) {
        RigidBody *body = system->getRigidBody(i);
        auto obj = std::make_unique<rend::BallRenderer>(&(body->p_x), &(body->p_y), ball_radius, 255, 255, 255, 0);
        renderer->attachObject(std::move(obj)); 
    }
    
    int n_f = system->getForceGeneratorsCount();
    for(int i=0; i<n_f; i++) {
        if(system->getForceGenerator(i)->force_type == FORCE_SPRING) {
            SpringForceGenerator *spring = (SpringForceGenerator*)system->getForceGenerator(i);
            double *p1_x = &(system->getRigidBody(spring->p1_index)->p_x);
            double *p1_y = &(system->getRigidBody(spring->p1_index)->p_y);

            double *p2_x = &(system->getRigidBody(spring->p2_index)->p_x);
            double *p2_y = &(system->getRigidBody(spring->p2_index)->p_y);

            double rest_length = spring->m_restLength;
            auto obj = std::make_unique<rend::SpringRenderer>(p1_x, p1_y, p2_x, p2_y, rest_length, 255, 255, 255, 0);
            renderer->attachObject(std::move(obj));
        }
    }
}
