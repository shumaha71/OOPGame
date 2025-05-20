#pragma once
#include <vector>
#include <iostream>
#include "Units.h"
#include "Landscape.h"

class Base;

class Map {
    int width, height;
    std::vector<std::vector<Unit*>> grid;

public:
    Map(int w, int h) : width(w), height(h), grid(h, std::vector<Unit*>(w, nullptr)) {}

    bool placeUnit(Unit* unit, int x, int y) {
        if (valid(x, y) && grid[y][x] == nullptr) {
            grid[y][x] = unit;
            return true;
        }
        return false;
    }
    bool addUnit(Unit* unit, int x, int y);

    Unit* getUnitAt(int x, int y) {
        if (valid(x, y)) return grid[y][x];
        return nullptr;
    }

    void placeBase(Base* base) {
        // Просто выводим, куда поставили базу
        std::cout << "[Map] Base placed at (" << base->getX() << ", " << base->getY() << ")\n";
    }

    void print() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x]) std::cout << grid[y][x]->symbol();
                else std::cout << '.';
            }
            std::cout << '\n';
        }
    }

    bool moveUnit(Unit* unit, int newX, int newY) {
        if (!valid(newX, newY)) return false;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x] == unit) {
                    grid[y][x] = nullptr;
                    grid[newY][newX] = unit;
                    return true;
                }
            }
        }
        return false;
    }

    const std::vector<std::vector<Unit*>>& getGrid() const { return grid; }

private:
    bool valid(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
};
