#include <Windows.h>
//#include <locale>
#include <iostream>
//#include <iomanip>
#include <conio.h>
#include <string>


void MainMenu(bool &isGameActive);

short getPosition(const std::string &str);

void out_Menu(int selector, bool &isGameActive);

int ReadKey();

bool YesNoAsk(const std::string &question);

void CenterWindow();