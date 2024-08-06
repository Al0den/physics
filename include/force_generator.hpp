#pragma once

#include "../include/system_state.hpp"

#define UNDEFINED 0
#define FORCE_SPRING 1
#define FORCE_GRAVITY 2
#define FORCE_STATIC 3
#define FORCE_MOTION 4

class ForceGenerator {
    public:
        ForceGenerator();
        virtual ~ForceGenerator();

        virtual void apply(SystemState *system) = 0;
        virtual double potentialEnergy(void *system);

        int m_index;
        int force_type;
};
