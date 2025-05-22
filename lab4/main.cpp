#include <windows.h>
#include "GameController.h"
#include "Logger.h"

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
    controller.launch();

    return 0;
}
