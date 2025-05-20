#include "Units.h"
#include "NeutralObjects.h"

Unit& operator+(Unit& u, NeutralObject& obj) {
    u.interact(obj);
    return u;
}

void Swordsman::interact(NeutralObject& obj) {
    std::cout << "Swordsman interacts with neutral object.\n";
    obj.apply(*this);
    die();
}

void Archer::interact(NeutralObject& obj) {
    std::cout << "Archer interacts with neutral object.\n";
    obj.apply(*this);
}
