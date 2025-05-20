#include "GameController.h"
#include <iostream>
#include <limits>
#include "CreateUnitCommand.h"
#include "MoveUnitCommand.h"
#include "ShowBaseStatusCommand.h"

GameController::GameController() {
    map = std::make_unique<Map>(15, 15);
    base = std::make_unique<Base>("Main Base", 1, 1, 100, 10);
    map->placeBase(base.get());
}

void GameController::mainMenu() {
    while (true) {
        map->print();
        std::cout << "\n1 - Управление базой\n2 - Управление юнитом\n3 - Завершить игру\nВыбор: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: baseMenu(); break;
            case 2: unitMenu(); break;
            case 3: return;
            default: std::cout << "Неверный ввод.\n";
        }
    }
}

void GameController::baseMenu() {
    while (true) {
        std::cout << "\n1 - Состояние базы\n2 - Список юнитов\n3 - Создание юнита\n4 - Назад\nВыбор: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: showBaseStatus(); break;
            case 2: listUnits(); break;
            case 3: createUnit(); break;
            case 4: return;
            default: std::cout << "Неверный ввод.\n";
        }
    }
}

void GameController::unitMenu() {
    listUnits();
    int x, y;
    std::cout << "Введите ID юнита для управления (x y): ";
    std::cin >> x >> y;

    Unit* unit = map->getUnitAt(x, y);
    if (!unit) {
        std::cout << "Юнит не найден.\n";
        return;
    }

    std::cout << "\nЮнит " << unit->symbol() << " готов к приказу!\n";
    std::cout << "1 - Перемещение\n";
    std::cout << "2 - Использование способности\n";
    std::cout << "3 - Оставить юнита в покое\n";
    std::cout << "Выбор действия: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            moveUnit();
            break;
        case 2:
            unit->useAbility(*map);
            break;
        case 3:
            return;
    }
    
    int action;
    std::cin >> action;

    switch (action) {
        case 1: {
            int nx, ny;
            std::cout << "Введите координаты юнита (x y): ";
            std::cin >> nx >> ny;
            map->moveUnit(unit, nx, ny);
            break;
        }
        case 2: {
            std::cout << "Юнит " << unit->symbol() << " использует способность! (заглушка)\n";
            // Здесь в будущем можно будет вызывать метод unit->useAbility();
            break;
        }
        case 3:
            std::cout << "Юнит остался в покое.\n";
            break;
        default:
            std::cout << "Неверный выбор.\n";
    }
}



void GameController::listUnits() {
    std::cout << "\nЮниты на карте:\n";
    for (const auto& row : map->getGrid()) {
        for (const auto& unit : row) {
            if (unit) std::cout << unit->symbol() << "(" << unit->getX() << "," << unit->getY() << ") ";
        }
    }
    std::cout << "\n";
}

void GameController::createUnit() {
    CreateUnitCommand cmd(base.get(), map.get());
    cmd.execute();
}

void GameController::moveUnit() {
    MoveUnitCommand cmd(map.get());
    cmd.execute();
}

void GameController::showBaseStatus() {
    ShowBaseStatusCommand cmd(base.get());
    cmd.execute();
}
void GameController::launch() {
    while (true) {
        showMap();
        std::cout << "\n1 - Управление базой\n2 - Управление юнитом\n3 - Завершить игру\nВыбор: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: baseMenu(); break;
            case 2: unitMenu(); break;
            case 3: return;
            default: std::cout << "Неверный выбор!\n";
        }
    }
}
void GameController::showMap() {
    map->print(); 
}