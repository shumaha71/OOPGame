#include "Base.h"
#include "Map.h"
#include <algorithm>
#include "logger.h"

void Base::createUnit(Map& map, const std::string& type, int x, int y) {
    std::cout << "[DEBUG] type в методе createUnit: '" << type << "'\n";
    std::cout << "[DEBUG] Попытка создать юнита типа: " << type << " на (" << x << "," << y << ")\n";

    Unit* unit = nullptr;
    std::string t = type;
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);

    if (t == "swordsman") unit = new Swordsman(x, y);
    else if (t == "archer") unit = new Archer(x, y);
    else if (t == "magician") unit = new Magician(x, y);
    else if (t == "healer") unit = new Healer(x, y);
    else if (t == "crossbowman") unit = new Crossbowman(x, y);
    else if (t == "spearman") unit = new Spearman(x, y);

    if (!unit) {
        std::cout << "[DEBUG] Не удалось создать юнита: тип не распознан\n";
        return;
    }

    std::cout << "[DEBUG] Юнит создан: " << unit->symbol() << "\n";

    unit->setPosition(x, y);
    unit->setOwner(this);
    unit->setLogger(logger);

   
    std::cout << "[DEBUG] Проверка grid[" << y << "][" << x << "] перед добавлением...\n";
    if (map.getUnitAt(x, y)) {
        std::cout << "[DEBUG] Клетка ЗАНЯТА\n";
    } else {
        std::cout << "[DEBUG] Клетка свободна\n";
    }

    // if (map.addUnit(unit, x, y)) {
    //     units.push_back(unit);
    //     std::cout << "Created unit: " << unit->symbol() << std::endl;

    //     if (logger) logger->logBaseAction(name, "Created unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
    // } else {
    //     delete unit;
    //     std::cout << "Failed to place unit on the map.\n";

    //     if (logger) logger->logBaseAction(name, "Failed to create unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
    // }
    if (map.addUnit(unit, x, y)) {
        units.push_back(unit);
        std::cout << "[DEBUG] Юнит " << unit->symbol() << " добавлен в список базы и на карту.\n";
    } else {
        std::cout << "[DEBUG] Не удалось разместить юнита " << unit->symbol() << " — клетка занята!\n";
        delete unit;
    }
}

// void Base::createUnit(Map& map, const std::string& type, int x, int y) {
//     Unit* unit = nullptr;

//     if (type == "Swordsman") unit = new Swordsman(x, y);
//     else if (type == "Archer") unit = new Archer(x, y);
//     else if (type == "Magician") unit = new Magician(x, y);
//     else if (type == "Healer") unit = new Healer(x, y);
//     else if (type == "Crossbowman") unit = new Crossbowman(x, y);
//     else if (type == "Spearman") unit = new Spearman(x, y);

//     if (unit) {
//         unit->setPosition(x, y);              // Устанавливаем координаты
//         unit->setOwner(this);                 // Устанавливаем базу-владельца
//         unit->setLogger(logger);              // Привязываем логгер

//         if (map.addUnit(unit, x, y)) {
//             units.push_back(unit);            // Обязательно добавляем в список базы
//             std::cout << "Created unit: " << unit->symbol() << std::endl;

//             if (logger) logger->logBaseAction(name, "Created unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
//         } else {
//             delete unit;
//             std::cout << "Failed to place unit on the map.\n";

//             if (logger) logger->logBaseAction(name, "Failed to create unit: " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")");
//         }
//     }
// }

void Base::onUnitDestroyed(Unit* unit) {
    auto it = std::find(units.begin(), units.end(), unit);
    if (it != units.end()) {
        units.erase(it);
        std::cout << "Base: Unit destroyed. Remaining units: " << units.size() << "\n";
    }
}
void Base::setLogger(ILogger* logger) {
    this->logger = logger;
}