#include "Main_Menu.hpp"

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



short getPosition(const std::string &str)
{
    return static_cast<short>(windowWidth/2 - (str.size()/2 + 2)); // +1
}

void out_Menu(int selector, bool &isGameActive)
{
	//setlocale(LC_ALL, "Russian");
	short y = 4;

    auto out_Str = [&y, selector](std::string str, int id)
    {
        SetConsoleCursorPosition(consoleHandle, COORD{ getPosition(str), y });

		if (selector == id) std::cout << "> " << str;
		else std::cout << "  " << str;
		y += 2;
    };

	if (isGameActive) out_Str(continueStr, 0);

	out_Str(newGameStr, 1);

	out_Str(loadMenuStr, 2);

	out_Str(statisticStr, 3);

    out_Str(exitStr, 4);

}

int ReadKey()
{
	int inputChar = _getch();

	if (inputChar == 224)
	{
		inputChar = _getch();
		switch (inputChar)
		{
		case 80:
			inputChar = 'S';
			break;
		case 77:
			inputChar = 'D';
			break;
		case 75:
			inputChar = 'A';
			break;
		case 72:
			inputChar = 'W';
			break;
		default:
			inputChar = 224;
			break;
		}
	}
	else if (inputChar == 0) _getch();

	inputChar = toupper(inputChar);

	return inputChar;
}

bool YesNoAsk(const std::string &question)
{
	bool result = false;
	bool currentSelect = true;
	//const char * strAsk;
    //std::string exitAskStr = "Do you want exit?";
	bool QuestionMenuActive = true;
    short y = 6;    // отступ от верхнего края

    auto out_YesNo = [](bool select)
    {
        std::string strYes = "Yes";
        std::string strNo = "No";

        std::string indent_ = "         ";	// 10
        short x = static_cast<short>(windowWidth/2 - ((strYes.size() + indent_.size() + strNo.size()) / 2 + 2));	// 2 + 2 + 2
        SetConsoleCursorPosition(consoleHandle, COORD{ x, 8 });

        if (select)
        {
            std::cout << "> " << strYes << indent_;
            std::cout << "  " << strNo;
        }
        else
        {
            std::cout << "  " << strYes << indent_;
            std::cout << "> " << strNo;
        }
    };

	system("cls");

	SetConsoleCursorPosition(consoleHandle, COORD{ short(getPosition(question) + 2), y });
	std::cout << question;

	do {
		// Render
		out_YesNo(currentSelect);

		// Update
		char Key = ReadKey();

		switch (Key)
		{
		// Left
		case 'A':
		{
			currentSelect = true;
			break;
		}
		// Right
		case 'D':
		{
			currentSelect = false;
			break;
		}
		// Enter
		case 13:
            result = currentSelect;
			QuestionMenuActive = false;
			break;
		// Esc
		case 27:
			result = false;
			QuestionMenuActive = false;	// Cancel
			break;
		}
	} while (QuestionMenuActive);

	system("cls");

	return result;
}

void CenterWindow()
{
	HWND consoleWindow = GetConsoleWindow();

	RECT r;
	GetWindowRect(consoleWindow, &r);

	std::cout << "r.top\t" << r.top << std::endl;
	std::cout << "r.left\t" << r.left << std::endl;
	std::cout << "r.bott\t" << r.bottom << std::endl;
	std::cout << "r.right\t" << r.right << std::endl;

	int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((r.right - r.left) / 2);
	int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((r.bottom - r.top) / 2);

	std::cout << "SM_CXSCREEN " << GetSystemMetrics(SM_CXSCREEN) << std::endl;
	std::cout << "SM_CXSCREEN " << GetSystemMetrics(SM_CYSCREEN) << std::endl;

	std::cout << "x y\t" << x << ' ' << y << std::endl;	// 662 312

	std::cout << "SetWindowPos " << SetWindowPos(consoleWindow, HWND_TOP, x, y, 0, 0, SWP_NOSIZE) << std::endl;
}