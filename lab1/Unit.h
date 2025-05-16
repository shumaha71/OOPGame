#pragma once
#include "Stats.h"
#include <memory>

class Unit {
public:
    virtual ~Unit() = default;
    virtual void move(int x, int y) = 0;
    virtual void printInfo() const = 0;
    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual char symbol() const = 0;
    int x{}, y{};
protected:
    Stats stats;
    Unit(int x, int y, const Stats& s) : x(x), y(y), stats(s) {}
};
