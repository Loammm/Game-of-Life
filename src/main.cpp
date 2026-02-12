#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "grid.h"

constexpr float WINDOW_RATIO = 0.8;
constexpr int CELL_SIZE = 16;
constexpr int WINDOW_WIDTH = static_cast<int>(1920 * WINDOW_RATIO / CELL_SIZE) * CELL_SIZE;
constexpr int WINDOW_HEIGHT = static_cast<int>(1080 * WINDOW_RATIO / CELL_SIZE) * CELL_SIZE;
constexpr int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
constexpr int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

bool drag = false;
bool dragValue = false; // true for alive, false for dead

int main(int argc, char* argv[]) {
    // --- Initialise SDL VIDEO (graphics) ---
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialise! Error: %s", SDL_GetError());
        return 1;
    }

    // --- Create a window ---
    // +1 pixel for the last line of the grid
    SDL_Window* window = SDL_CreateWindow("Game of Life", WINDOW_WIDTH+1, WINDOW_HEIGHT+1, 0);

    if (window == nullptr) {
        SDL_Log("Window could not be created! Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // --- Create a renderer ---
    // We pass NULL to let SDL pick the best graphics driver automatically.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Grid grid(GRID_WIDTH, GRID_HEIGHT);

    // --- The game loop ---
    //   1. Handle events  (keyboard, mouse, window close)
    //   2. Update state   (nothing to update yet)
    //   3. Render          (paint the screen)
    bool running = true;

    while (running) {
        // --- Handle events ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            // --- Handle mouse click event ---
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                drag = true;
                float mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                int grid_x = static_cast<int>(mouse_x / CELL_SIZE);
                int grid_y = static_cast<int>(mouse_y / CELL_SIZE);
                if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
                    grid.toggleCell(grid_x, grid_y);
                    dragValue = grid.getCell(grid_x, grid_y);
                }
            }
            // --- Handle mouse drag event ---
            if (drag && event.type == SDL_EVENT_MOUSE_MOTION){
                float mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                int grid_x = static_cast<int>(mouse_x / CELL_SIZE);
                int grid_y = static_cast<int>(mouse_y / CELL_SIZE);
                if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
                    if (grid.getCell(grid_x, grid_y) != dragValue) {
                        grid.toggleCell(grid_x, grid_y);
                    }
                }
            }
            // --- Handle mouse release event ---
            if(event.type == SDL_EVENT_MOUSE_BUTTON_UP){
                drag = false;
            }
            // placeholder manual update
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_A) {
                    grid.update();
                }
            }
        }

        // --- Render ---
        // Set the draw colour (R, G, B, A).
        SDL_SetRenderDrawColor(renderer, 15, 15, 20, 255);
        // Clear the whole screen with that colour.
        SDL_RenderClear(renderer);
        // Render the grid.
        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
        for (int x = 0; x <= GRID_WIDTH; x++) {
            SDL_RenderLine(renderer, x * CELL_SIZE, 0, x * CELL_SIZE, WINDOW_HEIGHT);
        }
        for (int y = 0; y <= GRID_HEIGHT; y++) {
            SDL_RenderLine(renderer, 0, y * CELL_SIZE, WINDOW_WIDTH, y * CELL_SIZE);
        }
        // Render the cells.
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (grid.getCell(x, y)) {
                    SDL_FRect cell = { static_cast<float>(x * CELL_SIZE), static_cast<float>(y * CELL_SIZE), static_cast<float>(CELL_SIZE), static_cast<float>(CELL_SIZE) };
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }
        // Present — flip the back buffer to the screen.
        SDL_RenderPresent(renderer);
    }

    // --- Cleanup (reverse order)---
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
