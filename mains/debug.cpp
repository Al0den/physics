#include <PhysicsEngine>
#include <gravity.hpp>
#include <rigid_body.hpp>
#include <rigid_body_system.hpp>
#include <rk4_ode_solver.hpp>
#include <system_state.hpp>

#include <iostream>

int main() {
    SystemState *system = new SystemState();
    delete system;

    RigidBodySystem *r_system = new RigidBodySystem();

    RigidBody *body = new RigidBody(0, 0, 0, 10, 0);
    delete body;

    body = new RigidBody(0, 0, 0, 10, 0);
    r_system->addRigidBody(body);

    delete r_system;

    for(int i=0; i<10000000; i++) {
        r_system = new RigidBodySystem();

        for(int j=0; j<10000; j++) {
            RigidBody *body = new RigidBody(0, 0, 0, 10, 0);
            r_system->addRigidBody(body);
        }
        for (int j=0; j<10000; j++) {
            r_system->addForceGenerator(new GravityForceGenerator);
        }

        r_system->initialize(new Rk4OdeSolver);


        delete r_system;
    }

    std::cout << "Finished test" << std::endl;

}
