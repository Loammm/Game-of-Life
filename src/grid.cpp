#include "grid.h"
#include <algorithm>

Grid::Grid(int width, int height) : width_(width), height_(height), cells_(width * height, 0), nextCells_(width * height, 0) {}

void Grid::toggleCell(int x, int y) {
    cells_[x + y * width_] = !cells_[x + y * width_];
}

bool Grid::getCell(int x, int y) const {
    return cells_[x + y * width_];
}

int Grid::countNeighbours(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = (x + i + width_) % width_; // wrap around using modulo
            int ny = (y + j + height_) % height_;
            count += cells_[nx + ny * width_];
        }
    }
    return count;
}

void Grid::update() {
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            int count = countNeighbours(x, y);
            if (count < 2 || count > 3) {
                nextCells_[x + y * width_] = 0;
            } else if (count == 3) {
                nextCells_[x + y * width_] = 1;
            } else {
                nextCells_[x + y * width_] = cells_[x + y * width_];
            }
        }
    }
    cells_.swap(nextCells_);
}