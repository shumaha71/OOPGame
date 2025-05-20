#include "NeutralObjects.h"
#include "Units.h"

void Trap::apply(Unit& unit) {
    std::cout << "Trap triggered! Unit takes damage.\n";
}

void Artifact::apply(Unit& unit) {
    std::cout << "Artifact found! Unit gains power.\n";
}

void Bonus::apply(Unit& unit) {
    std::cout << "Bonus collected! Unit gets minor buff.\n";
}

void Portal::apply(Unit& unit) {
    std::cout << "Portal activated! (Teleportation not implemented).\n";
}
