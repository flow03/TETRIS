#pragma once

#include <Windows.h>
//#include <locale>
#include <iostream>
//#include <iomanip>
#include <conio.h>
#include <string>

// #include "TestApp.h"

class MainMenu
{
public:
    //MainMenu::MainMenu(BaseApp &base);

    void ShowMenu(bool &isGameActive);

    void out_Menu(int selector, bool &isGameActive);

    int ReadKey();

    bool YesNoAsk(const std::string &question);

    void CenterWindow();

private:
    short getPosition(const std::string &str);

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //bool isGameActive = false;  // работает ли игра в данный момент
    //bool isGameStart = false;   // была ли начата игра ???
    bool isMenuActive = false;  // включено ли главное меню

    int windowWidth = 28;
    int windowHeight = 24;

    std::string continueStr = "Continue";
    std::string newGameStr = "New game";
    std::string loadMenuStr = "Save/Load";
    std::string statisticStr = "Records";
    std::string exitStr = "Exit";

    std::string exitAskStr = "Do you want exit?";
    std::string newGameAsk = "Do you want to start?";

    //TestApp * base;
};