#pragma once
#include <iostream>
#include "Units.h"

class Unit; // чтобы избежать циклической зависимости

class NeutralObject {
public:
    virtual ~NeutralObject() = default;
    virtual void apply(Unit& unit) = 0;
};

// Ловушка — наносит урон
class Trap : public NeutralObject {
public:
    void apply(Unit& unit) override;
};

// Артефакт — усиливает
class Artifact : public NeutralObject {
public:
    void apply(Unit& unit) override;
};

// Бонус — небольшое улучшение
class Bonus : public NeutralObject {
public:
    void apply(Unit& unit) override;
};

// Портал — телепортация (пока не реализовано)
class Portal : public NeutralObject {
public:
    void apply(Unit& unit) override;
};
