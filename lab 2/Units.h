#pragma once
#include <iostream>
#include "Base.h"
class NeutralObject; // чтобы избежать циклической зависимости
class Base; // предварительное объявление

class Unit {
protected:
    int x, y;
    int hp;

public:
    Unit(int x, int y, int hp = 100) : x(x), y(y), hp(hp) {}
    virtual ~Unit() = default;

    virtual char symbol() const = 0;
    virtual void interact(NeutralObject& obj) = 0;

    // перегрузка оператора для взаимодействия с объектами
    friend Unit& operator+(Unit& u, NeutralObject& obj);
    
    Base* owner = nullptr;

    void setOwner(Base* base) { owner = base; }
    void die() {
        std::cout << symbol() << " dies!\n";
        if (owner) owner->onUnitDestroyed(this);
    }

};

class Swordsman : public Unit {
public:
    Swordsman(int x, int y) : Unit(x, y, 120) {}
    char symbol() const override { return 'S'; }
    void interact(NeutralObject& obj) override;
};

class Archer : public Unit {
public:
    Archer(int x, int y) : Unit(x, y, 80) {}
    char symbol() const override { return 'A'; }
    void interact(NeutralObject& obj) override;
};
