#pragma once
#include <vector>
#include <iostream>
#include "Units.h"
#include "Logger.h"

class Base;

class Map {
public:
    Map(int w = 10, int h = 10)
        : width(w), height(h), grid(h, std::vector<Unit*>(w, nullptr)) {}

    void setLogger(ILogger* lgr) { logger = lgr; }

    const std::vector<std::vector<Unit*>>& getGrid() const { return grid; }

    void resize(int w, int h) {
        width = w;
        height = h;
        grid = std::vector<std::vector<Unit*>>(h, std::vector<Unit*>(w, nullptr));
    }

    bool placeUnit(Unit* unit, int x, int y);
    bool addUnit(Unit* unit, int x, int y);  // <-- объявляем, чтобы не было "undefined reference"
    Unit* getUnitAt(int x, int y);
    void placeBase(Base* base);
    void print();

    bool moveUnit(Unit* unit, int newX, int newY);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void clear();

private:
    int width, height;
    std::vector<std::vector<Unit*>> grid;
    Base* base = nullptr;
    ILogger* logger = nullptr;
};