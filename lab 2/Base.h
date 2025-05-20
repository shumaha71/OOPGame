#pragma once
#include <string>
#include <vector>
#include <iostream>

class Unit;

class Map;

class Base {
    std::string name;
    int x, y;
    int hp;
    int maxUnits;
    std::vector<Unit*> units;

public:
    Base(std::string name, int x, int y, int hp, int maxUnits)
        : name(std::move(name)), x(x), y(y), hp(hp), maxUnits(maxUnits) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void createUnit(Map& map, const std::string& type, int ux, int uy);
    void onUnitDestroyed(Unit* unit); // <- наблюдатель
};
