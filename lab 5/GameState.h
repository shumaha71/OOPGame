#pragma once
#include "Map.h"
#include "Base.h"
#include <fstream>

class GameState {
public:
    void save(Map& map, Base& base, const std::string& filename);
    void load(Map& map, Base& base, const std::string& filename);
};
