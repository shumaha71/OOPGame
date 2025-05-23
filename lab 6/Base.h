#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Logger.h"

class Unit;
class Map;

class Base {
    std::string name;
    int x, y;
    int hp;
    int maxUnits;
    std::vector<Unit*> units;

    ILogger* logger = nullptr;  

public:
    Base(std::string name, int x, int y, int hp, int maxUnits)
        : name(std::move(name)), x(x), y(y), hp(hp), maxUnits(maxUnits) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void createUnit(Map& map, const std::string& type, int ux, int uy);
    void onUnitDestroyed(Unit* unit);

    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getUnitCount() const { return units.size(); }

    // Метод для установки логгера
    void setLogger(ILogger* logger);
    const std::vector<Unit*>& getUnits() const { return units; }
    void addUnit(Unit* unit) {
    units.push_back(unit);
    }
    int getHealth() const {
        return health;
    }
private:
    int health;
};
inline std::ostream& operator<<(std::ostream& os, const Base& base) {
    os << "База \"" << base.getName() << "\" [HP: " << base.getHP() << ", юнитов: " << base.getUnitCount() << "]";
    return os;
}