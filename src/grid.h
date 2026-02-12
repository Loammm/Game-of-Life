#pragma once

#include <vector>
#include <cstdint>

class Grid {
public:
    Grid(int width, int height);

    void toggleCell(int x, int y);
    bool getCell(int x, int y) const;

private:
    int width_;
    int height_;
    std::vector<uint8_t> cells_; // using uint8_t for speed instead of bool
};