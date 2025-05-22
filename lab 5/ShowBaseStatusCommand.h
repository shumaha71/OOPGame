#pragma once
#include "ICommand.h"
#include "Base.h"
#include <iostream>

class ShowBaseStatusCommand : public ICommand {
    Base* base;
public:
    ShowBaseStatusCommand(Base* b) : base(b) {}
    void execute() override {
        std::cout << "\n[База] Имя: " << base->getName()
                  << " | HP: " << base->getHP()
                  << " | Юнитов: " << base->getUnitCount() << "\n";
    }
};