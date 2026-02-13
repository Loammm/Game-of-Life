# Conway's Game of Life

A minimalist C++ implementation of Conway's Game of Life using SDL3.

**[▶ Live version](https://stacktoprod.com/life)**

## Controls

| Key | Action |
|-----|--------|
| **Click / Drag** | Toggle cells |
| **Space** | Play / Pause |
| **N** | Step (while paused) |
| **R** | Reset |
| **1–9** | Random fill (10%–90%) |
| **↑ / ↓** | Speed up / slow down |

## Build

**Prerequisites:** Git, CMake, a C++17 compiler.

```bash
# 1. Clone the project
git clone https://github.com/Loammm/Game-of-Life.git
cd Game-of-Life

# 2. Clone SDL3 into vendored/
mkdir vendored
git clone https://github.com/libsdl-org/SDL.git vendored/SDL

# 3. Configure and build
cmake -B build-cmake -S .
cmake --build build-cmake

# 4. Run
./build-cmake/Debug/game_of_life
```