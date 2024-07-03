#pragma once 

#include "../include/rigid_body.hpp"
#include "../include/force_generator.hpp"
#include "../include/system_state.hpp"
#include "../include/ode_solver.hpp"

#include <RenderEngine>

#include <vector>

class RigidBodySystem {
    public:
        RigidBodySystem();
        ~RigidBodySystem();

        void initialize(OdeSolver *solve);

        void addRigidBody(RigidBody *rigidbody);
        void removeRigidBody(RigidBody *rigidbody);
        int getRigidBodiesCount();
        RigidBody *getRigidBody(int index);


        void addForceGenerator(ForceGenerator *forceGenerator);
        void removeForceGenerator(ForceGenerator *forceGenerator);
        int getForceGeneratorsCount();
        ForceGenerator *getForceGenerator(int index);

        void process(double dt, double steps);

        double mechanicalEnergy();

        void updateRenderer(rend::RenderEngine *renderer);
    protected:
        OdeSolver *m_solver;

        std::vector<RigidBody*> m_rigidBodies;
        std::vector<ForceGenerator*> m_forceGenerators;

        void processForces();
        void propagateResults();

        void populateSystemState(); 

        SystemState m_state;
};
