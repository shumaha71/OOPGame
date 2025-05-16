#pragma once
#include "Unit.h"
#include <iostream>

// === Infantry ===
class Infantry : public Unit {
public:
    Infantry(int x, int y, const Stats& s) : Unit(x, y, s) {}
    void move(int newX, int newY) override { x = newX; y = newY; }
    void printInfo() const override {
        std::cout << "Infantry at (" << x << "," << y << ") HP: " << stats.health << "\n";
    }
};

class Swordsman : public Infantry {
public:
    Swordsman(int x, int y) : Infantry(x, y, Stats(100, 20, 30)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Swordsman>(*this); }
    char symbol() const override { return 'S'; }
};

class Spearman : public Infantry {
public:
    Spearman(int x, int y) : Infantry(x, y, Stats(90, 25, 25)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Spearman>(*this); }
    char symbol() const override { return 'P'; }
};

// === Archers ===
class Archer : public Unit {
public:
    Archer(int x, int y, const Stats& s) : Unit(x, y, s) {}
    void move(int newX, int newY) override { x = newX; y = newY; }
    void printInfo() const override {
        std::cout << "Archer at (" << x << "," << y << ") HP: " << stats.health << "\n";
    }
};

class Longbowman : public Archer {
public:
    Longbowman(int x, int y) : Archer(x, y, Stats(70, 10, 40)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Longbowman>(*this); }
    char symbol() const override { return 'L'; }
};

class Crossbowman : public Archer {
public:
    Crossbowman(int x, int y) : Archer(x, y, Stats(60, 15, 45)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Crossbowman>(*this); }
    char symbol() const override { return 'C'; }
};

// === Cavalry ===
class Cavalry : public Unit {
public:
    Cavalry(int x, int y, const Stats& s) : Unit(x, y, s) {}
    void move(int newX, int newY) override { x = newX; y = newY; }
    void printInfo() const override {
        std::cout << "Cavalry at (" << x << "," << y << ") HP: " << stats.health << "\n";
    }
};

class Knight : public Cavalry {
public:
    Knight(int x, int y) : Cavalry(x, y, Stats(120, 30, 35)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Knight>(*this); }
    char symbol() const override { return 'K'; }
};

class Lancer : public Cavalry {
public:
    Lancer(int x, int y) : Cavalry(x, y, Stats(110, 25, 40)) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Lancer>(*this); }
    char symbol() const override { return 'N'; }
};
