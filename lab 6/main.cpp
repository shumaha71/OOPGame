#include <windows.h>
#include "GameController.h"
#include "Logger.h"
#include "Game.h"
#include "CaptureBaseRule.h"
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Выберите режим логирования:\n";
    std::cout << "1 - В консоль\n";
    std::cout << "2 - В файл\n";
    std::cout << "3 - Без логов\n";
    std::cout << "Ваш выбор: ";
    int mode;
    std::cin >> mode;

    LoggerProxy::Mode selectedMode;
    switch (mode) {
        case 1: selectedMode = LoggerProxy::TO_CONSOLE; break;
        case 2: selectedMode = LoggerProxy::TO_FILE; break;
        default: selectedMode = LoggerProxy::DISABLED;
    }

    LoggerProxy logger(selectedMode);

    GameController controller;
    controller.setLogger(logger.get());
    controller.mainMenu();
    auto* game = Game<CaptureBaseRule, 2>::getInstance();

    while (!game->isGameOver()) {
        game->update();
    }
    while (true) {
        std::cout << "\n1. Начать новую игру\n2. Выйти\nВаш выбор: ";
        int choice;
        std::cin >> choice;

        if (choice == 2) break;

        auto* game = Game<CaptureBaseRule, 2>::getInstance();
        game->reset();  // новая игра

        while (!game->isGameOver()) {
            game->update();
        }

        std::cout << "Игра окончена!\n";
    }
    return 0;
}
