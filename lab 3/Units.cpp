#include "Units.h"
#include "NeutralObjects.h"
#include "Map.h"
#include <iostream>

void Swordsman::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Archer::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Magician::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Healer::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Crossbowman::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Spearman::interact(NeutralObject& obj) {
    obj.apply(*this);
}

void Swordsman::useAbility(Map& map) {
    int tx = x - 1;
    int ty = y;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Мечник наносит удар по (" << tx << ", " << ty << ")!\n";
        target->takeDamage(40);
    } else {
        std::cout << "Противника рядом нет.\n";
    }
}

void Archer::useAbility(Map& map) {
    int tx = x + 1;
    int ty = y + 1;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Лучник стреляет по (" << tx << ", " << ty << ")!\n";
        target->takeDamage(20);
    } else {
        std::cout << "Цель не обнаружена по диагонали.\n";
    }
}

void Magician::useAbility(Map& map) {
    int tx = x + 1;
    int ty = y;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Маг применяет заклинание на (" << tx << ", " << ty << ")!\n";
        target->takeDamage(30);
    } else {
        std::cout << "Цели рядом нет.\n";
    }
}

void Healer::useAbility(Map& map) {
    int tx = x;
    int ty = y - 1;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Целитель лечит юнита на (" << tx << ", " << ty << ")!\n";
        target->heal(25);
    } else {
        std::cout << "Юнит для лечения не найден.\n";
    }
}

void Crossbowman::useAbility(Map& map) {
    int tx = x + 2;
    int ty = y;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Арбалетчик стреляет в (" << tx << ", " << ty << ")!\n";
        target->takeDamage(25);
    } else {
        std::cout << "Цель вне зоны действия.\n";
    }
}

void Spearman::useAbility(Map& map) {
    int tx = x;
    int ty = y - 2;
    Unit* target = map.getUnitAt(tx, ty);
    if (target) {
        std::cout << "Копейщик тычет в (" << tx << ", " << ty << ")!\n";
        target->takeDamage(35);
    } else {
        std::cout << "Нет врага в зоне досягаемости.\n";
    }
}
void Unit::takeDamage(int dmg) {
    hp -= dmg;
    if (hp <= 0) {
        std::cout << symbol() << " погиб!" << std::endl;
        die();  // вызвать удаление юнита
    }
}

void Unit::heal(int amount) {
    hp += amount;
    if (hp > 100) hp = 100;  // допустим максимум здоровья — 100
    std::cout << symbol() << " восстановил здоровье до " << hp << std::endl;
}