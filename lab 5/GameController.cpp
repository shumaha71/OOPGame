#include "GameController.h"
#include <iostream>
#include <limits>
#include "CreateUnitCommand.h"
#include "MoveUnitCommand.h"
#include "ShowBaseStatusCommand.h"
#include <sstream>

GameController::GameController() {
    map = std::make_unique<Map>(15, 15);
    base = std::make_unique<Base>("Main Base", 1, 1, 100, 10);
    map->placeBase(base.get());
}

void GameController::mainMenu() {
    while (true) {
        showMap();
        std::cout << "\n1 - Управление базой\n";
        std::cout << "2 - Управление юнитом\n";
        std::cout << "3 - Сохранить игру\n";
        std::cout << "4 - Загрузить игру\n";
        std::cout << "5 - Завершить игру\n";
        std::cout << "Выбор: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: baseMenu(); break;
        case 2: unitMenu(); break;
        case 3: gameState.save(*map, *base, "save.txt"); break;
        case 4: gameState.load(*map, *base, "save.txt"); break;
        case 5: return;
            default: std::cout << "Неверный выбор.\n";
        }
    }
}

void GameController::baseMenu() {
    while (true) {
        std::cout << "\n1 - Состояние базы\n2 - Список юнитов\n3 - Создание юнита\n4 - Назад\nВыбор: ";
        int choice;
        std::cin >> choice;
        if (logger) logger->logSystem("Пользователь выбрал пункт меню: " + std::to_string(choice));
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

    if (logger) {
        std::stringstream ss;
        ss << *unit;
        logger->logUnitAction("selected", ss.str());
    }

    std::cout << "\nЮнит " << unit->symbol() << " готов к приказу!\n";
    std::cout << "1 - Перемещение\n";
    std::cout << "2 - Использование способности\n";
    std::cout << "3 - Оставить юнита в покое\n";
    std::cout << "Выбор действия: ";
    int choice;
    std::cin >> choice;

    if (logger) logger->logSystem("Пользователь выбрал действие юнита: " + std::to_string(choice));

    switch (choice) {
        case 1:
            moveUnit();
            break;
        case 2:
            unit->useAbility(*map);
            break;
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
    std::cout << "[System] Игрок выбрал: создать юнита\n";
    std::cout << "Выберите тип юнита:\n";
    std::cout << "1 - Мечник (S)\n";
    std::cout << "2 - Лучник (A)\n";
    std::cout << "3 - Маг (M)\n";
    std::cout << "4 - Целитель (H)\n";
    std::cout << "5 - Арбалетчик (R)\n";
    std::cout << "6 - Копейщик (G)\n";
    std::cout << "Выбор: ";

    int choice;
    std::cin >> choice;

    std::string type;
    switch (choice) {
        case 1: type = "swordsman"; break;
        case 2: type = "archer"; break;
        case 3: type = "magician"; break;
        case 4: type = "healer"; break;
        case 5: type = "crossbowman"; break;
        case 6: type = "spearman"; break;
        default:
            std::cout << "Неверный выбор.\n";
            return;
    }

    int x, y;
    std::cout << "Координаты x y: от 0 до " << map->getWidth() - 1
              << " и от 0 до " << map->getHeight() - 1 << "\n";
    std::cout << "Введите x y: ";
    std::cin >> x >> y;

    base->createUnit(*map, type, x, y);
    std::cout << "Created unit: " << static_cast<char>(toupper(type[0])) << "\n";
}

void GameController::moveUnit() {
    int x, y;
    std::cout << "Введите координаты x и y (от 0 до " << map->getWidth() - 1
              << " и от 0 до " << map->getHeight() - 1 << "): ";
    std::cin >> x >> y;

    Unit* unit = map->getUnitAt(x, y);
    if (!unit) {
        std::cout << "Юнит не найден.\n";
        return;
    }

    int newX, newY;
    std::cout << "Новая позиция (x y): ";
    std::cin >> newX >> newY;

    bool success = map->moveUnit(unit, newX, newY);
    if (success) {
        std::cout << "Юнит перемещён в (" << newX << "," << newY << ")\n";
        if (logger) {
            std::stringstream ss;
            ss << *unit;
            logger->logUnitAction("move", ss.str());
        }
    } else {
        std::cout << "Не удалось переместить юнита. Возможно, клетка занята или координаты неверны.\n";
    }
}


void GameController::showBaseStatus() {
    if (logger) {
        std::stringstream ss;
        ss << *base;
        logger->logSystem("Состояние базы: " + ss.str());
    }
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
void GameController::setLogger(LogAdapter* adapter) {
    map->setLogger(adapter->getLogger());
    base->setLogger(adapter->getLogger());
}