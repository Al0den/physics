#include "../include/rigid_body_system.hpp"
#include "../include/euler_ode_solver.hpp"

#include <iostream>
#include <assert.h>

RigidBodySystem::RigidBodySystem() {
    m_state = new SystemState();
    m_solver = new EulerOdeSolver();
    m_rigidBodies = std::vector<RigidBody*>();
    m_forceGenerators = std::vector<ForceGenerator*>();
}

RigidBodySystem::~RigidBodySystem() {
    delete m_state;
    delete m_solver;
    for(int i=0; i<m_rigidBodies.size(); i++) {
        delete m_rigidBodies[i];
    }
    for(int j=0; j<m_forceGenerators.size(); j++) {
        delete m_forceGenerators[j];
    }
}

void RigidBodySystem::initialize(OdeSolver *solver) {
    delete m_solver;
    m_solver = solver;
}

void RigidBodySystem::addRigidBody(RigidBody *rigidbody) {
    m_rigidBodies.push_back(rigidbody);
}

RigidBody* RigidBodySystem::getRigidBody(int index) {
    assert (index < m_rigidBodies.size());
    return m_rigidBodies[index];
}

ForceGenerator* RigidBodySystem::getForceGenerator(int index) {
    assert (index < m_forceGenerators.size());
    return m_forceGenerators[index];
}

void RigidBodySystem::removeRigidBody(RigidBody *rigidbody) {
    m_rigidBodies[rigidbody->index] = m_rigidBodies.back();
    m_rigidBodies[rigidbody->index]->index = rigidbody->index;
    m_rigidBodies.resize(m_rigidBodies.size() - 1);
}

void RigidBodySystem::addForceGenerator(ForceGenerator *generator) {
    m_forceGenerators.push_back(generator);
}

void RigidBodySystem::removeForceGenerator(ForceGenerator *generator) {
    m_forceGenerators[generator->m_index] = m_forceGenerators.back();
    m_forceGenerators[generator->m_index]->m_index = generator->m_index;
    m_forceGenerators.resize(m_forceGenerators.size() - 1);
}

void RigidBodySystem::populateSystemState() {
    int n = m_rigidBodies.size();
    m_state->setObjectsCount(n);

    for (int i = 0; i < n; i++) {
        m_state->p_x[i] = m_rigidBodies[i]->p_x;
        m_state->p_y[i] = m_rigidBodies[i]->p_y;

        m_state->v_x[i] = m_rigidBodies[i]->v_x;
        m_state->v_y[i] = m_rigidBodies[i]->v_y;

        m_state->theta[i] = m_rigidBodies[i]->theta;
        m_state->v_theta[i] = m_rigidBodies[i]->v_theta;

        m_state->m[i] = m_rigidBodies[i]->m;

        m_state->a_x[i] = 0;
        m_state->a_y[i] = 0;
    }
}

void RigidBodySystem::processForces() {
    int n_f = m_forceGenerators.size();
    int n = m_rigidBodies.size();

    for (int i = 0; i < n; i++) {
        m_state->f_x[i] = 0;
        m_state->f_y[i] = 0;
    }

    for (int i = 0; i < n_f; i++) {
        m_forceGenerators[i]->apply(m_state);
    }

    for (int i = 0; i < n; i++) {
        m_state->a_x[i] = m_state->f_x[i] / m_state->m[i];
        m_state->a_y[i] = m_state->f_y[i] / m_state->m[i];
    }
}

void RigidBodySystem::process(double dt, double steps) {
    populateSystemState();
    for(int i=0; i<steps; i++) {
        m_solver->start(m_state, dt);

        while(true) {
            const bool done = m_solver->step(m_state);

            processForces();

            m_solver->solve(m_state);

            if (done) break;
        }

        m_solver->end(m_state);
    }

    propagateResults();
}

int RigidBodySystem::getRigidBodiesCount() {
    return m_rigidBodies.size();
}

int RigidBodySystem::getForceGeneratorsCount() {
    return m_forceGenerators.size();
}

void RigidBodySystem::propagateResults() {
    int n = m_rigidBodies.size();
    for (int i = 0; i < n; i++) {
        m_rigidBodies[i]->p_x = m_state->p_x[i];
        m_rigidBodies[i]->p_y = m_state->p_y[i];
        m_rigidBodies[i]->v_x = m_state->v_x[i];
        m_rigidBodies[i]->v_y = m_state->v_y[i];
        m_rigidBodies[i]->theta = m_state->theta[i];
        m_rigidBodies[i]->v_theta = m_state->v_theta[i];
    }
}

double RigidBodySystem::mechanicalEnergy() {
    double kineticEnergy = m_state->kineticEnergy();
    

    double potentialEnergy = 0;
    int n = m_forceGenerators.size();
        
    for (int i = 0; i < n; i++) {
        printf("Energie potentielle de %d\n", i);
        printf("Potential energy: %f\n", m_forceGenerators[i]->potentialEnergy(m_state));
        potentialEnergy += m_forceGenerators[i]->potentialEnergy(this);
    }

    return kineticEnergy + potentialEnergy;
}




