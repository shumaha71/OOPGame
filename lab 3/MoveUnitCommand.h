#pragma once
#include "ICommand.h"
#include "Map.h"
#include <iostream>

class MoveUnitCommand : public ICommand {
    Map* map;
public:
    MoveUnitCommand(Map* m) : map(m) {}
    void execute() override {
        int x, y, nx, ny;
        std::cout << "Введите координаты юнита (x y): ";
        std::cin >> x >> y;
        Unit* unit = map->getUnitAt(x, y);
        if (!unit) {
            std::cout << "Юнит не найден.\n";
            return;
        }
        std::cout << "Новая позиция (x y): ";
        std::cin >> nx >> ny;
        map->moveUnit(unit, nx, ny);
    }
};