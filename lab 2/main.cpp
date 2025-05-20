#include <iostream>
#include "Map.h"
#include "Base.h"
#include "NeutralObjects.h"

int main() {
    Map map(10, 10);
    Base base("Alpha", 1, 1, 300, 5);
    map.placeBase(&base);

    base.createUnit(map, "Swordsman", 2, 2);
    base.createUnit(map, "Archer", 3, 3);

    std::cout << "\nInitial Map:\n";
    map.print();

    std::cout << "\nInteraction with neutral object:\n";
    Unit* unit = map.getUnitAt(2, 2);
    if (unit) {
        Trap trap;
        *unit + trap;
    }

    std::cout << "\nMap After Interaction:\n";
    map.print();

    return 0;
}
