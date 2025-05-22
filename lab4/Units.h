#pragma once
#include <iostream>
#include "Base.h"
#include "Logger.h"


class NeutralObject;

class Base;

class Unit {
protected:
    int x, y;
    int hp = 100;
    Base* owner = nullptr;
    LogAdapter* logger = nullptr;


public:
    Unit(int x, int y, int hp = 100) : x(x), y(y), hp(hp) {}
    virtual ~Unit() = default;
    int getX() const { return x; }
    int getY() const { return y; }
    virtual char symbol() const = 0;
    virtual void interact(NeutralObject& obj) = 0;
    virtual void useAbility(Map& map) = 0;

    friend Unit& operator+(Unit& u, NeutralObject& obj);
    void takeDamage(int dmg);
    void heal(int amount);

    void setOwner(Base* base) { owner = base; }
    void die() {
        std::cout << symbol() << " dies!\n";
        if (owner) owner->onUnitDestroyed(this);
    }
    void setPosition(int newX, int newY) {
    x = newX;
    y = newY;
    }
    void setLogger(LogAdapter* adapter) {
        logger = adapter;
    }
    int getHP() const { return hp; }

    virtual std::string getTypeName() const { return "Unit"; }
};

class Swordsman : public Unit {
public:
    Swordsman(int x, int y) : Unit(x, y, 120) {}
    char symbol() const override { return 'S'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Swordsman"; }
};

class Archer : public Unit {
public:
    Archer(int x, int y) : Unit(x, y, 80) {}
    char symbol() const override { return 'A'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Archer"; }
};

class Magician : public Unit {
public:
    Magician(int x, int y) : Unit(x, y) {}
    char symbol() const override { return 'M'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Magician"; }
};

class Healer : public Unit {
public:
    Healer(int x, int y) : Unit(x, y) {}
    char symbol() const override { return 'H'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Healer"; }
};

class Crossbowman : public Unit {
public:
    Crossbowman(int x, int y) : Unit(x, y) {}
    char symbol() const override { return 'R'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Crossbowman"; }
};

class Spearman : public Unit {
public:
    Spearman(int x, int y) : Unit(x, y) {}
    char symbol() const override { return 'G'; }
    void useAbility(Map& map) override;
    void interact(NeutralObject& obj) override;
    std::string getTypeName() const override { return "Spearman"; }
};
inline std::ostream& operator<<(std::ostream& os, const Unit& unit) {
    os << "Юнит '" << unit.symbol() << "' на позиции (" << unit.getX() << "," << unit.getY() << ")";
    return os;
}