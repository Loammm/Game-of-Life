#include "grid.h"
#include <algorithm>
#include <random>

Grid::Grid(int width, int height) : width_(width), height_(height), cells_(width * height, 0), nextCells_(width * height, 0), liveCells_(width * height) {}

void Grid::toggleCell(int x, int y) {
    cells_[x + y * width_] = !cells_[x + y * width_];
    if (cells_[x + y * width_]) {
        liveCells_.insert(x + y * width_);
    } else {
        liveCells_.erase(x + y * width_);
    }
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

bool Grid::update() {
    std::unordered_set<int> activeCells;
    // reset nextCells_ to prevent ghost cells
    std::fill(nextCells_.begin(), nextCells_.end(), 0);
    // get all live cells and their neighbours to check
    for(int index: liveCells_){
        int x = index % width_;
        int y = index / width_;
        // add all neighbours to "active cells"
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if (i == 0 && j == 0) continue;
                int nx = (x + i + width_) % width_;
                int ny = (y + j + height_) % height_;
                activeCells.insert(nx + ny * width_);
            }
        }
    }
    // get and update the "active cells"
    for (int index: activeCells) {
        int x = index % width_;
        int y = index / width_;
        int count = countNeighbours(x, y);
        if (count < 2 || count > 3) {
            nextCells_[index] = 0;
        } else if (count == 3) {
            nextCells_[index] = 1;
        }
        else{
            nextCells_[index] = cells_[index];
        }
    }
    cells_.swap(nextCells_); // update the grid
    // replace live cells with the new live cells
    liveCells_.clear();
    for(int index: activeCells){
        if(cells_[index]){
            liveCells_.insert(index);
        }
    }
    if(liveCells_.empty() || cells_==nextCells_) return false; // used to pause the game when the grid is stable
    return true;
}

void Grid::reset() {
    cells_.assign(width_ * height_, 0);
    liveCells_.clear();
}

void Grid::randomise(float density) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(density); // true/false with probability density
    for(int i = 0; i < width_ * height_; i++) {
        cells_[i] = d(gen);
    }
    liveCells_.clear();
    for(int i = 0; i < width_ * height_; i++) {
        if(cells_[i]) {
            liveCells_.insert(i);
        }
    }
}