#pragma once
#include "Units.h"
#include <memory>

class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::unique_ptr<Unit> create(int x, int y) const = 0;
};

class SwordsmanFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create(int x, int y) const override {
        return std::make_unique<Swordsman>(x, y);
    }
};
