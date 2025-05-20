#pragma once
#include <iostream>
#include <vector>
#include "Landscape.h"
#include "Units.h"
#include "Base.h"



class Map {
    struct Cell {
        Unit* unit = nullptr;
        Base* base = nullptr;
        ILandscape* terrain = nullptr;
    };

    int width, height;
    std::vector<std::vector<Cell>> grid;

public:
    Map(int w, int h) : width(w), height(h), grid(h, std::vector<Cell>(w)) {
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                grid[y][x].terrain = new Grass();
    }

    ~Map() {
        for (auto& row : grid)
            for (auto& cell : row)
                delete cell.terrain;
    }

    bool valid(int x, int y) const {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    void placeBase(Base* base) {
        int x = base->getX();
        int y = base->getY();
        if (valid(x, y)) grid[y][x].base = base;
    }

    bool placeUnit(Unit* unit, int x, int y) {
        if (!valid(x, y) || grid[y][x].unit != nullptr) return false;
        grid[y][x].unit = unit;
        return true;
    }

    Unit* getUnitAt(int x, int y) {
        if (!valid(x, y)) return nullptr;
        return grid[y][x].unit;
    }

    void print() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                const auto& cell = grid[y][x];
                if (cell.base) std::cout << "B";
                else if (cell.unit) std::cout << cell.unit->symbol();
                else std::cout << cell.terrain->symbol();
            }
            std::cout << "\\n";
        }
    }
};
