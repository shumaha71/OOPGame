#include "Map.h"
#include "Base.h"

bool Map::placeUnit(Unit* unit, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || grid[y][x])
        return false;

    grid[y][x] = unit;
    return true;
}

bool Map::addUnit(Unit* unit, int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height && grid[y][x] == nullptr) {
        grid[y][x] = unit;
        return true;
    }
    return false;
}


Unit* Map::getUnitAt(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return grid[y][x];
}

void Map::placeBase(Base* b) {
    base = b;
    if (logger) logger->logMapAction("Base placed at (" + std::to_string(base->getX()) + "," + std::to_string(base->getY()) + ")");
}

void Map::print() {
    std::cout << "Печать карты...\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x]) {
                std::cout << grid[y][x]->symbol() << ' ';
            }
            else if (base && base->getX() == x && base->getY() == y) {
                std::cout << 'B' << ' ';
            }
            else {
                std::cout << '.' << ' ';
            }
        }
        std::cout << std::endl;
    }
}

bool Map::moveUnit(Unit* unit, int newX, int newY) {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if (grid[y][x] == unit) {
                if (newX < 0 || newX >= width || newY < 0 || newY >= height || grid[newY][newX])
                    return false;

                grid[y][x] = nullptr;
                grid[newY][newX] = unit;
                return true;
            }

    return false;
}
void Map::clear() {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x] = nullptr;
}
