#pragma once
#include <memory>
#include "Map.h"
#include "GameState.h"

template <typename Rule, int Players = 2>
class Game {
private:
    static Game<Rule, Players>* instance;
    Rule rule;
    std::unique_ptr<Map> map;
    std::unique_ptr<GameState> state;

    Game() {
        map = std::make_unique<Map>();
        state = std::make_unique<GameState>();
        rule.initializeGame(*map);
    }

public:
    static Game<Rule, Players>* getInstance() {
        if (!instance) {
            instance = new Game<Rule, Players>();
        }
        return instance;
    }

    void update() {
        rule.executeTurn(*map, *state);
    }

    void reset() {
        map = std::make_unique<Map>();
        state = std::make_unique<GameState>();
        rule.initializeGame(*map);
    }

    bool isGameOver() const {
        return rule.checkWinCondition(*map, *state);
    }

    const Map& getMap() const { return *map; }
    const GameState& getState() const { return *state; }
};

template <typename Rule, int Players>
Game<Rule, Players>* Game<Rule, Players>::instance = nullptr;
