#pragma once
#include <vector>
#include <iostream>
#include "Units.h"
#include "Landscape.h"
#include "Logger.h"

class Base;

class Map {
    int width, height;
    std::vector<std::vector<Unit*>> grid;
    LogAdapter* logger = nullptr;

public:
    Map(int w, int h) : width(w), height(h), grid(h, std::vector<Unit*>(w, nullptr)) {}

    void setLogger(LogAdapter* lgr) { logger = lgr; }

    const std::vector<std::vector<Unit*>>& getGrid() const { return grid; }

    bool placeUnit(Unit* unit, int x, int y) {
        if (valid(x, y) && grid[y][x] == nullptr) {
            grid[y][x] = unit;
            if (logger) logger->logMapAction("Unit placed at (" + std::to_string(x) + "," + std::to_string(y) + ")");
            return true;
        }
        return false;
    }

    Unit* getUnitAt(int x, int y) {
        if (valid(x, y)) return grid[y][x];
        return nullptr;
    }

    void placeBase(Base* base) {
        if (logger) logger->logMapAction("Base placed at (" + std::to_string(base->getX()) + "," + std::to_string(base->getY()) + ")");
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
        int oldX = unit->getX();
        int oldY = unit->getY();
        grid[oldY][oldX] = nullptr;
        grid[newY][newX] = unit;
        if (logger) logger->logMapAction("Unit moved from (" + std::to_string(oldX) + "," + std::to_string(oldY) + ") to (" + std::to_string(newX) + "," + std::to_string(newY) + ")");
        return true;
    }
    bool addUnit(Unit* unit, int x, int y);

private:
    bool valid(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
};