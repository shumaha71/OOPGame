#include <iostream>
#include "GameField.h"
#include "UnitFactory.h"

int main() {
    GameField field(10, 10, 10);
    SwordsmanFactory factory;

    // Примеры использования
    field.addUnit(factory.create(1, 1));
    field.addUnit(std::make_unique<Spearman>(2, 2));
    field.addUnit(std::make_unique<Longbowman>(3, 3));
    field.addUnit(std::make_unique<Knight>(4, 4));

    std::cout << "Initial field:\n";
    field.print();

    std::cout << "\nMoving unit (1,1) to (0,0):\n";
    field.moveUnit(1, 1, 0, 0);
    field.print();

    std::cout << "\nCopied field:\n";
    GameField copy = field;
    copy.print();

    std::cout << "\nIterating units:\n";
    auto it = field.getIterator();
    while (it.hasNext()) {
        it.next()->printInfo();
    }

    return 0;
}
