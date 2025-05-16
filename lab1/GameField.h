#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Units.h"

class GameField {
    int width, height, maxUnits;
    std::vector<std::unique_ptr<Unit>> units;

public:
    GameField(int w, int h, int maxU) : width(w), height(h), maxUnits(maxU) {}

    GameField(const GameField& other)
        : width(other.width), height(other.height), maxUnits(other.maxUnits) {
        for (const auto& u : other.units)
            units.push_back(u->clone());
    }

    GameField& operator=(const GameField& other) {
        if (this == &other) return *this;
        units.clear();
        width = other.width;
        height = other.height;
        maxUnits = other.maxUnits;
        for (const auto& u : other.units)
            units.push_back(u->clone());
        return *this;
    }

    bool addUnit(std::unique_ptr<Unit> unit) {
        if (units.size() >= maxUnits) return false;
        if (unit->x < 0 || unit->x >= width || unit->y < 0 || unit->y >= height) return false;
        units.push_back(std::move(unit));
        return true;
    }

    void removeUnitAt(int x, int y) {
        auto it = std::remove_if(units.begin(), units.end(), [=](const std::unique_ptr<Unit>& u) {
            return u->x == x && u->y == y;
        });
        units.erase(it, units.end());
    }

    void moveUnit(int oldX, int oldY, int newX, int newY) {
        for (auto& u : units) {
            if (u->x == oldX && u->y == oldY) {
                u->move(newX, newY);
                return;
            }
        }
    }

    void print() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto it = std::find_if(units.begin(), units.end(), [=](const std::unique_ptr<Unit>& u) {
                    return u->x == x && u->y == y;
                });
                if (it != units.end())
                    std::cout << (*it)->symbol();
                else
                    std::cout << "X";
            }
            std::cout << "\n";
        }
    }

    class Iterator {
        const std::vector<std::unique_ptr<Unit>>& units;
        size_t index;
    public:
        Iterator(const std::vector<std::unique_ptr<Unit>>& units) : units(units), index(0) {}
        bool hasNext() const { return index < units.size(); }
        const Unit* next() { return units[index++].get(); }
    };

    Iterator getIterator() const {
        return Iterator(units);
    }
};
