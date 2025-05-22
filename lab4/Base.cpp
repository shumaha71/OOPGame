#include "Base.h"
#include "Map.h"
#include <algorithm>
#include "logger.h"

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
        unit->setLogger(logger); // ОБЯЗАТЕЛЬНО

        if (map.addUnit(unit, x, y)) {
            units.push_back(unit);
            std::cout << "Created unit: " << unit->symbol() << std::endl;
            if (logger) logger->logBaseAction(name, "Created unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
        } else {
            delete unit;
            std::cout << "Failed to place unit on the map.\n";
            if (logger) logger->logBaseAction(name, "Failed to create unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
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
void Base::setLogger(LogAdapter* logger) {
    this->logger = logger;
}