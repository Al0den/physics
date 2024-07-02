#pragma once

#include "../../include/system_state.hpp"

#include "/opt/homebrew/include/SDL2/SDL.h"

class Renderer {
    public:
        Renderer();
        ~Renderer();

        void render(SystemState *system);

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
};
