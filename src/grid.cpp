#include "grid.h"

Grid::Grid(int width, int height) : width_(width), height_(height), cells_(width * height, 0) {}

void Grid::toggleCell(int x, int y) {
    cells_[x + y * width_] = !cells_[x + y * width_];
}

bool Grid::getCell(int x, int y) const {
    return cells_[x + y * width_];
}