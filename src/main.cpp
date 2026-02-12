#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

constexpr float WINDOW_RATIO = 0.8;
constexpr int CELL_SIZE = 32;
constexpr int WINDOW_WIDTH = static_cast<int>(1920 * WINDOW_RATIO / CELL_SIZE) * CELL_SIZE;
constexpr int WINDOW_HEIGHT = static_cast<int>(1080 * WINDOW_RATIO / CELL_SIZE) * CELL_SIZE;
constexpr int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
constexpr int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;


int main(int argc, char* argv[]) {
    // --- 1. Initialise SDL VIDEO (graphics) ---
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialise! Error: %s", SDL_GetError());
        return 1;
    }

    // --- 2. Create a window ---
    // +1 pixel for the last line of the grid
    SDL_Window* window = SDL_CreateWindow("Game of Life", WINDOW_WIDTH+1, WINDOW_HEIGHT+1, 0);

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
        // Set the draw colour (R, G, B, A).
        SDL_SetRenderDrawColor(renderer, 15, 15, 20, 255);
        // Clear the whole screen with that colour.
        SDL_RenderClear(renderer);
        // Render the grid.
        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
        for (int x = 0; x <= GRID_WIDTH; x++) {
            SDL_RenderLine(renderer, x * CELL_SIZE, 0, x * CELL_SIZE, WINDOW_HEIGHT);
        }
        for (int y = 0; y <= GRID_HEIGHT; y++) {
            SDL_RenderLine(renderer, 0, y * CELL_SIZE, WINDOW_WIDTH, y * CELL_SIZE);
        }
        // Present — flip the back buffer to the screen.
        SDL_RenderPresent(renderer);
    }

    // --- 5. Cleanup (reverse order)---
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
