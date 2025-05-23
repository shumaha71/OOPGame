#pragma once
#include "Map.h"
#include "GameState.h"
#include "Base.h"
#include <iostream>

class CaptureBaseRule {
public:
    void initializeGame(Map& map) {
        std::cout << "[Rule] Игра началась: Победа при уничтожении базы врага.\n";
    }

    void executeTurn(Map& map, GameState& state) {
        std::cout << "[Rule] Ход игрока: " << state.getCurrentPlayer() << std::endl;
        // Логика хода игрока (упрощённо)
        state.nextPlayer();
    }

    bool checkWinCondition(const Map& map, const GameState& state) const {
        for (const auto& base : map.getBases()) {
            if (base && base->getHealth() <= 0) {
                std::cout << "База уничтожена! Победа противника.\n";
                return true;
            }
        }
        return false;
    }
};
