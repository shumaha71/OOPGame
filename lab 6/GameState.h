#pragma once
#include "Map.h"
#include "Base.h"
#include <fstream>

class GameState {
public:
    void save(Map& map, Base& base, const std::string& filename);
    void load(Map& map, Base& base, const std::string& filename);
    int getCurrentPlayer() const {
        return currentPlayer;
    }

    void nextPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

private:
    int currentPlayer = 1;
};
