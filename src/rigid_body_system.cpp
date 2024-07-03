#include "../include/rigid_body_system.hpp"
#include "../include/spring.hpp"

RigidBodySystem::RigidBodySystem() {}

RigidBodySystem::~RigidBodySystem() {
    m_state.destroy();
}

void RigidBodySystem::updateRenderer(rend::RenderEngine *renderer) {
    int n = m_rigidBodies.size();
    double ball_radius = 0.05;
    double line_width = 0.1;

    for(int i=0; i<n; i++) {
        RigidBody *body = m_rigidBodies[i];
        rend::Ball b = {&(body->p_x), &(body->p_y), ball_radius, 255, 255, 255, 0};
        renderer->addBall(b);
    }
    
    int n_f = m_forceGenerators.size();
    for(int i=0; i<n_f; i++) {
        if(m_forceGenerators[i]->force_type == FORCE_SPRING) {
            SpringForceGenerator *spring = (SpringForceGenerator*)m_forceGenerators[i];
            double *p1_x = &(m_rigidBodies[spring->p1_index]->p_x);
            double *p1_y = &(m_rigidBodies[spring->p1_index]->p_y);

            double *p2_x = &(m_rigidBodies[spring->p2_index]->p_x);
            double *p2_y = &(m_rigidBodies[spring->p2_index]->p_y);

            double rest_length = spring->m_restLength;


            rend::Spring s = {p1_x, p1_y, p2_x, p2_y, spring->m_restLength, line_width, 255, 255, 255, 0};
            renderer->addSpring(s);
        }
    }
}

void RigidBodySystem::initialize(OdeSolver *solver) {
    m_solver = solver;
}

void RigidBodySystem::addRigidBody(RigidBody *rigidbody) {
    m_rigidBodies.push_back(rigidbody);
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
    m_state.setObjectsCount(n);

    for (int i = 0; i < n; i++) {
        m_state.p_x[i] = m_rigidBodies[i]->p_x;
        m_state.p_y[i] = m_rigidBodies[i]->p_y;

        m_state.v_x[i] = m_rigidBodies[i]->v_x;
        m_state.v_y[i] = m_rigidBodies[i]->v_y;

        m_state.theta[i] = m_rigidBodies[i]->theta;
        m_state.v_theta[i] = m_rigidBodies[i]->v_theta;

        m_state.m[i] = m_rigidBodies[i]->m;

        m_state.a_x[i] = 0;
        m_state.a_y[i] = 0;
    }
}

void RigidBodySystem::processForces() {
    int n_f = m_forceGenerators.size();
    int n = m_rigidBodies.size();

    for (int i = 0; i < n; i++) {
        m_state.f_x[i] = 0;
        m_state.f_y[i] = 0;
    }

    for (int i = 0; i < n_f; i++) {
        m_forceGenerators[i]->apply(&m_state);
    }

    for (int i = 0; i < n; i++) {
        m_state.a_x[i] = m_state.f_x[i] / m_state.m[i];
        m_state.a_y[i] = m_state.f_y[i] / m_state.m[i];
    }
}

void RigidBodySystem::process(double dt, double steps) {
    populateSystemState();

    for(int i=0; i<steps; i++) {
        m_solver->start(&m_state, dt);

        while(true) {
            const bool done = m_solver->step(&m_state);

            processForces();

            m_solver->solve(&m_state);

            if (done) break;
        }

        m_solver->end(&m_state);
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
        m_rigidBodies[i]->p_x = m_state.p_x[i];
        m_rigidBodies[i]->p_y = m_state.p_y[i];
        m_rigidBodies[i]->v_x = m_state.v_x[i];
        m_rigidBodies[i]->v_y = m_state.v_y[i];
        m_rigidBodies[i]->theta = m_state.theta[i];
        m_rigidBodies[i]->v_theta = m_state.v_theta[i];
    }
}

double RigidBodySystem::mechanicalEnergy() {
    double kineticEnergy = m_state.kineticEnergy();
    

    double potentialEnergy = 0;
    int n = m_forceGenerators.size();
        
    printf("dsadsdsa\n");
    for (int i = 0; i < n; i++) {
        printf("Energie potentielle de %d\n", i);
        printf("Potential energy: %f\n", m_forceGenerators[i]->potentialEnergy(&m_state));
        potentialEnergy += m_forceGenerators[i]->potentialEnergy(this);
    }

    return kineticEnergy + potentialEnergy;
}




