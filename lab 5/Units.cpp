#include "Units.h"
#include "Map.h"
#include "NeutralObjects.h"
#include <iostream>


// --- Swordsman ---
void Swordsman::useAbility(Map& map) {
    int tx = x + 1;
    int ty = y;
    Unit* target = map.getUnitAt(tx, ty);

    if (target) {
        target->takeDamage(20);
        std::cout << "Мечник ударил врага на (" << tx << "," << ty << ")!\n";
        if (logger) logger->logUnitAction("Swordsman", "Удар по (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Рядом никого нет.\n";
        if (logger) logger->logUnitAction("Swordsman", "Промах — никого справа");
    }
}

void Swordsman::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Swordsman", "Interacted with neutral object");
}

// --- Archer ---
void Archer::useAbility(Map& map) {
    int tx = x + 2;
    int ty = y;
    Unit* target = map.getUnitAt(tx, ty);

    if (target) {
        target->takeDamage(15);
        std::cout << "Лучник попал по врагу на (" << tx << "," << ty << ")!\n";
        if (logger) logger->logUnitAction("Archer", "Выстрел по (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Нет врага на дистанции.\n";
    }
}

void Archer::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Archer", "Interacted with neutral object");
}

// --- Magician ---
void Magician::useAbility(Map& map) {
    int tx, ty;
    std::cout << "Введите координаты цели (x y): ";
    std::cin >> tx >> ty;

    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        target->takeDamage(30);
        std::cout << "Маг атаковал цель!\n";
        if (logger) logger->logUnitAction("Magician", "Атаковал (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Цель не найдена.\n";
    }
}

void Magician::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Magician", "Interacted with neutral object");
}

// --- Healer ---
void Healer::useAbility(Map& map) {
    int tx, ty;
    std::cout << "Введите координаты союзника для лечения (x y): ";
    std::cin >> tx >> ty;

    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        target->heal(25);
        std::cout << "Цель вылечена!\n";
        if (logger) logger->logUnitAction("Healer", "Вылечил юнита на (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Никого нет на указанной клетке.\n";
    }
}

void Healer::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Healer", "Interacted with neutral object");
}

// --- Crossbowman ---
void Crossbowman::useAbility(Map& map) {
    int tx = x - 1;
    int ty = y;

    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        target->takeDamage(20);
        std::cout << "Арбалетчик выстрелил в (" << tx << "," << ty << ")!\n";
        if (logger) logger->logUnitAction("Crossbowman", "Выстрел по (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Цель не найдена слева.\n";
    }
}

void Crossbowman::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Crossbowman", "Interacted with neutral object");
}

// --- Spearman ---
void Spearman::useAbility(Map& map) {
    int tx = x;
    int ty = y + 2;

    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        target->takeDamage(25);
        std::cout << "Копейщик поразил врага внизу!\n";
        if (logger) logger->logUnitAction("Spearman", "Удар вниз по (" + std::to_string(tx) + "," + std::to_string(ty) + ")");
    } else {
        std::cout << "Цель вне зоны досягаемости.\n";
    }
}

void Spearman::interact(NeutralObject& obj) {
    obj.apply(*this);
    if (logger) logger->logUnitAction("Spearman", "Interacted with neutral object");
}

void Unit::takeDamage(int dmg) {
    hp -= dmg;
    if (hp <= 0) {
        die();
    }
}

void Unit::heal(int amount) {
    hp += amount;
    if (hp > 100) hp = 100;
}