#pragma once
#include "Map.h"
#include "Base.h"
#include <memory>

class GameController {
    std::unique_ptr<Map> map;
    std::unique_ptr<Base> base;

public:
    GameController();
    void mainMenu();
    void baseMenu();
    void unitMenu();
    void listUnits();
    void createUnit();          
    void showBaseStatus(); 
    void moveUnit();
    void launch(); 
    void showMap(); 
};