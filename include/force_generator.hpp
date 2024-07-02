#pragma once

#include "../include/system_state.hpp"

class ForceGenerator {
    public:
        ForceGenerator();
        ~ForceGenerator();

        void apply(SystemState *system);

        int m_index;
};
