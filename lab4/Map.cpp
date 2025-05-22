#include "Map.h"


bool Map::addUnit(Unit* unit, int x, int y) {
    if (x < 0 || y < 0 || y >= static_cast<int>(grid.size()) || x >= static_cast<int>(grid[y].size()))
        return false;

    if (grid[y][x] == nullptr) {
        grid[y][x] = unit;
        return true;
    }
    return placeUnit(unit, x, y);

    return false;
}


