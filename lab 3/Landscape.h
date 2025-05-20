#pragma once

class ILandscape {
public:
    virtual ~ILandscape() = default;
    virtual char symbol() const = 0;
    virtual bool canMove() const = 0;
};

// Простой тип ландшафта — трава
class Grass : public ILandscape {
public:
    char symbol() const override { return '.'; }
    bool canMove() const override { return true; }
};

// Вода — по ней нельзя ходить
class Water : public ILandscape {
public:
    char symbol() const override { return '~'; }
    bool canMove() const override { return false; }
};

// Горы — тоже непроходимый тип
class Mountain : public ILandscape {
public:
    char symbol() const override { return '^'; }
    bool canMove() const override { return false; }
};
