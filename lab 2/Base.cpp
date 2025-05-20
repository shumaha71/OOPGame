#include "Base.h"
#include "Map.h"
#include <algorithm>

void Base::createUnit(Map& map, const std::string& type, int ux, int uy) {
    if (units.size() >= static_cast<size_t>(maxUnits)) {
        std::cout << "Base unit limit reached.\n";
        return;
    }

    Unit* unit = nullptr;
    if (type == "Swordsman") unit = new Swordsman(ux, uy);
    else if (type == "Archer") unit = new Archer(ux, uy);
    
    if (unit) unit->setOwner(this);

    if (unit && map.placeUnit(unit, ux, uy)) {
        units.push_back(unit);
        std::cout << "Created unit: " << unit->symbol() << "\n";
    } else {
        delete unit;
        std::cout << "Failed to place unit.\n";
    }
}
void Base::onUnitDestroyed(Unit* unit) {
    auto it = std::find(units.begin(), units.end(), unit);
    if (it != units.end()) {
        units.erase(it);
        std::cout << "Base: Unit destroyed. Remaining units: " << units.size() << "\n";
    }
}
