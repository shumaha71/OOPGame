#include "Base.h"
#include "Map.h"
#include <algorithm>

void Base::createUnit(Map& map, const std::string& type, int x, int y) {
    Unit* unit = nullptr;

    if (type == "Swordsman") unit = new Swordsman(x, y);
    else if (type == "Archer") unit = new Archer(x, y);
    else if (type == "Magician") unit = new Magician(x, y);
    else if (type == "Healer") unit = new Healer(x, y);
    else if (type == "Crossbowman") unit = new Crossbowman(x, y);
    else if (type == "Spearman") unit = new Spearman(x, y);

    if (unit) {
        unit->setPosition(x, y);
        unit->setOwner(this);

        if (map.addUnit(unit, x, y)) {
            units.push_back(unit);
            std::cout << "Created unit: " << unit->symbol() << std::endl;
        } else {
            delete unit;
        }
    }
}

void Base::onUnitDestroyed(Unit* unit) {
    auto it = std::find(units.begin(), units.end(), unit);
    if (it != units.end()) {
        units.erase(it);
        std::cout << "Base: Unit destroyed. Remaining units: " << units.size() << "\n";
    }
}
