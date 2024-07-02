#include <iostream>

#include "render.hpp"
#include "config.hpp"

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Balls", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    surface = SDL_GetWindowSurface(window);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_UpdateWindowSurface(window);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render(SystemState *system) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < system->n; i++) {
        double x = system->p_x[i];
        double y = system->p_y[i];
    
        // Draw a circle
        SDL_Rect rect = { (int)(x - radius), (int)(y - radius), (int)(2 * radius), (int)(2 * radius) };
        SDL_RenderFillRect(renderer, &rect);
    
    }
    SDL_RenderPresent(renderer);
}
