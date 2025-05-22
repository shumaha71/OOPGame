#pragma once
#include "ICommand.h"
#include "Base.h"
#include "Map.h"
#include <string>
#include <iostream>

class CreateUnitCommand : public ICommand {
    Base* base;
    Map* map;
public:
    CreateUnitCommand(Base* b, Map* m) : base(b), map(m) {}
    void execute() override {
        std::cout << "Выберите тип юнита:\n"
             "1 - Мечник (S)\n"
             "2 - Лучник (A)\n"
             "3 - Маг (M)\n"
             "4 - Целитель (H)\n"
             "5 - Арбалетчик (R)\n"
             "6 - Копейщик (G)\n"
             "Выбор: ";
        int type; std::cin >> type;
        std::cout << "Координаты x y: ";
        int x, y; std::cin >> x >> y;
        if (type == 1) base->createUnit(*map, "Swordsman", x, y);
        else if (type == 2) base->createUnit(*map, "Archer", x, y);
        else if (type == 3) base->createUnit(*map, "Magician", x, y);
        else if (type == 4) base->createUnit(*map, "Healer", x, y);
        else if (type == 5) base->createUnit(*map, "Crossbowman", x, y);
        else if (type == 6) base->createUnit(*map, "Spearman", x, y);
        else std::cout << "Неверный тип.\n";
    }
};