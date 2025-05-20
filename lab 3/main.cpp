#include <windows.h>
#include "GameController.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    GameController game;
    game.launch(); 

    return 0;
}