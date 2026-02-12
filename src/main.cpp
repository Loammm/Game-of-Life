#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr float WINDOW_RATIO = 0.8;

int main(int argc, char* argv[]) {
    // --- 1. Initialise SDL VIDEO (graphics) ---
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialise! Error: %s", SDL_GetError());
        return 1;
    }

    // --- 2. Create a window ---
    SDL_Window* window = SDL_CreateWindow("Game of Life", WINDOW_WIDTH*WINDOW_RATIO, WINDOW_HEIGHT*WINDOW_RATIO, 0);

    if (window == nullptr) {
        SDL_Log("Window could not be created! Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // --- 3. Create a renderer ---
    // We pass NULL to let SDL pick the best graphics driver automatically.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // --- 4. The game loop ---
    //   1. Handle events  (keyboard, mouse, window close)
    //   2. Update state   (nothing to update yet)
    //   3. Render          (paint the screen)
    bool running = true;

    while (running) {
        // --- 4a. Handle events ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // --- 4b. Render ---
        // Step 1: Set the draw colour (R, G, B, A).
        SDL_SetRenderDrawColor(renderer, 15, 15, 20, 255);
        // Step 2: Clear the whole screen with that colour.
        SDL_RenderClear(renderer);
        // Step 3: Present — flip the back buffer to the screen.
        SDL_RenderPresent(renderer);
    }

    // --- 5. Cleanup (reverse order)---
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
