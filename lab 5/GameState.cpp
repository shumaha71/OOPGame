#include "GameState.h"
#include <iostream>
#include <sstream>

void GameState::save(Map& map, Base& base, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Ошибка открытия файла для записи\n";
        return;
    }

    out << "SAVE\n";
    out << map.getWidth() << " " << map.getHeight() << "\n";

    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (map.getUnitAt(x, y))
                out << map.getUnitAt(x, y)->symbol();
            else
                out << ".";
        }
        out << "\n";
    }

    out << "BASE " << base.getName() << " " << base.getX() << " "
        << base.getY() << " " << base.getHP() << "\n";

    out << "UNITS " << base.getUnitCount() << "\n";
    for (Unit* u : base.getUnits()) {
        out << u->symbol() << " " << u->getX() << " "
            << u->getY() << " " << u->getHP() << "\n";
    }

    out.close();
    std::cout << "Игра успешно сохранена в " << filename << "\n";
}

void GameState::load(Map& map, Base& base, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "[Ошибка] Не удалось открыть файл сохранения: " << filename << std::endl;
        return;
    }

    std::string header;
    in >> header;
    if (header != "p") {
        std::cerr << "[Ошибка] Файл повреждён или имеет неверный формат (нет заголовка p)" << std::endl;
        return;
    }
    if (!in) {
        std::cerr << "Ошибка открытия файла для чтения\n";
        return;
    }

    int width, height;
    in >> width >> height;

    map.clear();
    map.resize(width, height);

    std::string line;
    std::getline(in, line); // добить \n после чисел

    for (int y = 0; y < height; ++y)
        std::getline(in, line); // читаем карту

    std::string label;
    in >> label;
    if (label != "BASE") {
        std::cerr << "Ошибка: ожидался блок BASE, но получено: " << label << "\n";
        return;
    }

    std::string name;
    int bx, by, bhp;
    in >> name >> bx >> by >> bhp;
    base = Base(name, bx, by, bhp, 100);
    map.placeBase(&base);

    in >> label; // UNITS
    int unitCount;
    in >> unitCount;
    std::getline(in, line); // добить \n после числа

    for (int i = 0; i < unitCount; ++i) {
        std::getline(in, line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        char symbol;
        int ux, uy, hp;
        iss >> symbol >> ux >> uy >> hp;

        std::string type;
        switch (symbol) {
            case 'S': type = "Swordsman"; break;
            case 'A': type = "Archer"; break;
            case 'M': type = "Magician"; break;
            case 'H': type = "Healer"; break;
            case 'R': type = "Crossbowman"; break;
            case 'G': type = "Spearman"; break;
            default:
                std::cerr << "[Загрузка] Неизвестный символ юнита: " << symbol << "\n";
                continue;
        }

        std::cout << "[Загрузка] Пытаемся создать " << type << " (" << symbol
                  << ") на координатах (" << ux << "," << uy << ")\n";

        base.createUnit(map, type, ux, uy);
        base.getUnits().back()->setHP(hp);
    }

    std::cout << "Игра успешно загружена из " << filename << "\n";
}
