#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

#include "Main_Menu.hpp"

//using namespace std;

class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	//30, 31, 16, 17
	//up_rows
	const wchar_t u = 30;
	//down rows
	const wchar_t d = 31;
	//left rows
	const wchar_t l = 17;
	//right rows
	const wchar_t r = 16;

	std::vector<std::vector< wchar_t > >screenBuffer;
	

	void Render();

public:
	int score = 0;
	bool isGameActive = false;

	//размеры области вывода по горизонтали и вертикали в символах
	const int X_SIZE;
	const int Y_SIZE;

	//аргументами являются размеры области вывода по горизонтали и вертикали в символах
	BaseApp(int xSize=100, int ySize=80);
	virtual ~BaseApp();

	//запускает игровой цикл
	void Run();

	//можно заполнить x,y-символ экрана определенным символом, или считать его
	void SetChar(int x, int y, wchar_t c);
	wchar_t GetChar(int x, int y);
	//устанавливает курсор в указанное место
	void SetConsoleCursor(int x, int y);
	//помещает текст в указанной позиции
	void RenderSystemDrawText(int x, int y, const char *text);

	/*эта функция вызывается каждую игровую итерацию, её можно переопределить, в наследнике класса.
	в неё приходит deltaTime - разница во времени между предыдущей итерацией и этой, в секундах*/
	virtual void UpdateF (float deltaTime){}
	/*эта функция вызывается при нажатии клавиши на клавиатуре, в неё приходит код клавиши - btnCode.
	если использовать стрелки или функциональные клавиши, то придет общее для них число, например 224, а следующее за ним - 
	будет уже непосредственно код самой клавиши, его можно получить, вызвав метод getch().
	Метод KeyPressed так же можно переопределить в наследнике*/
	virtual void KeyPressed (int btnCode){}
};