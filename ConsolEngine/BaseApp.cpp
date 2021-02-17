#include "TestApp.h"
#include <algorithm>
//#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>

#define MY_PERFORMENCE_COUNTER

typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD); 
SETCONSOLEFONT SetConsoleFont;

#include "PerformanceCounter.h"

BaseApp::BaseApp(int xSize, int ySize) : X_SIZE(xSize), Y_SIZE(ySize)
{
	isGameActive = true;

	SMALL_RECT windowSize = { (short)0, (short)0, (short)(X_SIZE - 1), (short)(Y_SIZE - 1)};
	COORD windowBufSize = { (short)X_SIZE, (short)Y_SIZE}; //COORD windowBufSize = {X_SIZE+1, Y_SIZE+1};

	mConsole = GetStdHandle(STD_OUTPUT_HANDLE); //STD_OUTPUT_HANDLE
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	//Шрифт
	//HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");    
	//SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");   
	////if (!SetConsoleFont) { std::cout << "error\n"; exit(1); }  
	//SetConsoleFont(mConsole, 8);
	

	//Размер шрифта
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(mConsole, TRUE, &fontInfo);
	fontInfo.nFont = 6;
	fontInfo.dwFontSize.X = 12;
	fontInfo.dwFontSize.Y = 16;
	fontInfo.FontFamily = FF_MODERN;  //48;
	//fontInfo.FontWeight = FW_NORMAL; //400
	wcscpy_s(fontInfo.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(mConsole, TRUE, &fontInfo);
	

	//Сначала задаём минимальные значения буфера
	SMALL_RECT zeroWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(mConsole, TRUE, &zeroWindow);
	SetConsoleScreenBufferSize(mConsole, COORD{ 1, 1 });

	//А уже потом изменяем значения на нужные нам
	if(!SetConsoleScreenBufferSize(mConsole,  windowBufSize))
	{
		std::cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << std::endl;
	}
	if(!SetConsoleWindowInfo(mConsole, TRUE, &windowSize))
	{
		std::cout << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);


	mChiBuffer = (CHAR_INFO*)malloc((X_SIZE+1)*(Y_SIZE+1)*sizeof(CHAR_INFO));

	mDwBufferSize.X = X_SIZE + 1;
	mDwBufferSize.Y = Y_SIZE + 1;		// размер буфера данных

	mDwBufferCoord.X = 0;
	mDwBufferCoord.Y = 0;				// координаты ячейки

	mLpWriteRegion.Left = 0;
	mLpWriteRegion.Top = 0;
	mLpWriteRegion.Right = X_SIZE;  //X_SIZE + 1, Y_SIZE + 1
	mLpWriteRegion.Bottom = Y_SIZE;	// прямоугольник для чтения


	for (int x = 0; x < X_SIZE + 1; ++x)
	{
		for (int y = 0; y < Y_SIZE + 1; ++y)
		{
			SetChar(x, y, L' ');
		}
	}

	screenBuffer = {
	{d, d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d },
	{u, u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{r, l ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', r , l ,' ',' ',' ',' ',' ',' ',' ', r , l },
	{d, d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d , d },
	{u, u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u , u}
	};

	//вывод игрового поля
	for (int x = 0; x < screenBuffer.size(); ++x)
		for (int y = 0; y < screenBuffer[x].size(); ++y)
		{
			//if ((screenBuffer[x][y]) != (backBuffer[x][y])) {
			SetChar(y, x, screenBuffer[x][y]);
			//backBuffer[x][y] = screenBuffer[x][y];
		//}
		}
}

BaseApp::~BaseApp()
{
	free(mChiBuffer);
}

void BaseApp::SetChar(int x, int y, wchar_t c)
{
	//mChiBuffer[x + (X_SIZE + 1)*y].Char.UnicodeChar = c;
	mChiBuffer[x + (X_SIZE + 1)*y].Char.AsciiChar = c;
	mChiBuffer[x + (X_SIZE + 1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;

}

wchar_t BaseApp::GetChar(int x, int y)
{
	return mChiBuffer[x + (X_SIZE+1)*y].Char.AsciiChar;
}

void BaseApp::SetConsoleCursor(int x, int y)
{
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(mConsole, cursorCoord);
}

void BaseApp::RenderSystemDrawText(int x, int y, const char *text)
{
	int column = x;
	char symbol = *text;
	while (symbol != 0)
	{
		SetChar(column, y, symbol);
		column++;
		text++;
		symbol = *text;
		if (column >= X_SIZE) { ++y; column = x; }
	}
}

void BaseApp::Render()
{
	if (!WriteConsoleOutputA(mConsole, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion))
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError()); 
	}
}

void BaseApp::Run()
{
	CStopwatch timer;
	__int64 sum = 0;
	//int counter = 0;
	int currentKey = 0;

	__int64 deltaTime = 0;
	//главный цикл игры
	while (isGameActive)
	{
		timer.Start();
		if (_kbhit())
		{
			currentKey = _getch();
			KeyPressed (currentKey);
			if (!FlushConsoleInputBuffer(mConsoleIn))
				std::cout<<"FlushConsoleInputBuffer failed with error "<<GetLastError();
		}

		//UpdateF((float)deltaTime / 1000.0f);
		UpdateF((float)deltaTime);
		Render();
		Sleep(1);

		while (1)
		{
			deltaTime = timer.Now();
			if (deltaTime > 20)
				break;
		}

		//deltaTime = timer.Now();

		sum += deltaTime;
		//counter++;
		if (sum >= 1000)
		{
			TCHAR  szbuff[255];
			StringCchPrintf(szbuff, 255, TEXT("CurrentKey: %d"), currentKey);
			SetConsoleTitle(szbuff);

			//counter = 0;
			sum = 0;
		}
	}

	std::vector<wchar_t> new_row;
	new_row.assign(28, L' ');

	for (auto it = screenBuffer.begin(); it != screenBuffer.end(); ++it)
		*it = new_row;

	//вывод игрового поля
	for (int x = 0; x < screenBuffer.size(); ++x)
		for (int y = 0; y < screenBuffer[x].size(); ++y)
			SetChar(y, x, screenBuffer[x][y]);

	RenderSystemDrawText(9, 5, "GAME OVER");
	RenderSystemDrawText(9, 10, "Your score");
	if (score == 0)
		RenderSystemDrawText(13, 12, (std::to_string(score).c_str()));
	else if (score >= 100)
		RenderSystemDrawText(12, 12, (std::to_string(score).c_str()));

	RenderSystemDrawText(3, 21, "Press any key to exit");
	Render(); 
	
	_getch();
}