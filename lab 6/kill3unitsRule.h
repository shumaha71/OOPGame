#pragma once
#include "Map.h"
#include "GameState.h"
#include <iostream>

class Kill3UnitsRule {
private:
    int killsPlayer1 = 0;
    int killsPlayer2 = 0;

public:
    void initializeGame(Map& map) {
        // Здесь можно разместить начальные юниты
        std::cout << "[Rule] Игра началась: Победа при 3 убийствах.\n";
    }

    void executeTurn(Map& map, GameState& state) {
        std::cout << "[Rule] Ход игрока: " << state.getCurrentPlayer() << std::endl;
        // Здесь можно вставить вызов логики одного хода — сейчас это заглушка
        state.nextPlayer(); // меняем игрока (паттерн Состояние)
    }

    bool checkWinCondition(const Map& map, const GameState& state) const {
        if (killsPlayer1 >= 3) {
            std::cout << "Игрок 1 победил!\n";
            return true;
        }
        if (killsPlayer2 >= 3) {
            std::cout << "Игрок 2 победил!\n";
            return true;
        }
        return false;
    }

    void registerKill(int killerPlayerId) {
        if (killerPlayerId == 1) ++killsPlayer1;
        else if (killerPlayerId == 2) ++killsPlayer2;
    }
};
