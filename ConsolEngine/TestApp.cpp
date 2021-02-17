#include "TestApp.h"



TestApp::TestApp() : Parent(28, 24)
{
	sum = 0.0;

	isDown = false;
	isShape = false;
	speed = 450;
	score = 0;
	
	new_row.assign(15, L' ');

	Blocks.resize(20);
	for (auto it = Blocks.begin(); it != Blocks.end(); ++it)
		*it = new_row;
}

void TestApp::DrawShape(Shape * _ptr, wchar_t symbol, COORD c) {
	for (int y = c.Y - 2; y <= c.Y + 3; ++y)
		for (int x = c.X - 2; x <= c.X + 2; ++x)
			SetChar(x, y, L' ');

	_ptr->SetShape(*this, symbol, c);
}

//int TestApp::GetScore() const { return score; }

void TestApp::CheckBlocks() {
	//запись в массив
	for (int y = 0; y < Blocks.size(); ++y)
	{
		for (int x = 0; x < Blocks.at(0).size(); ++x)
		{
			if (GetChar(x + 2, 21 - y) != L' ')
			{
				Blocks[y][x] = GetChar(x + 2, 21 - y);
			}
		}
	}
	//проверка строк
	bool isChanged = false;
	int count = 0;
	for (int y = 0; y < Blocks.size(); ++y)
	{
		for (int x = 0; x < Blocks.at(0).size(); ++x)
		{
			if (Blocks[y][x] != L' ') 
				++count;
		}
		if (count == 15) 
		{ 
			score += 100; //плюсуем результат
			auto iter = Blocks.begin() + y; //создаём итератор на текущую строку
			Blocks.erase(iter); //передаём строку в erase
			Blocks.push_back(new_row); //добавляем в конец массива(в верх поля) чистую строку
			isChanged = true; //маркер для последующей перерисовки поля
			--y;   //смещаемся на строку назад, чтобы на следующей итерации попасть на строку, 
		}          //которая сместилась на место текущей строки
		count = 0; //обнуляем счётчик
	}
	
	//перерисовка поля
	if(isChanged)
	for (int y = 0; y < Blocks.size(); ++y)
	{
		for (int x = 0; x < Blocks.at(0).size(); ++x)
		{
			SetChar(x + 2, 21 - y, Blocks[y][x]);
		}
	}
}

Shape * TestApp::GetRandShape(COORD coord) {
	Shape * _ptr = nullptr;
	engine.seed(device());

	switch (engine() % (7u)) //unsigned int
	{
	case 0:
		_ptr = new Quadrate(coord);
		break;
	case 1:
		_ptr = new Line(coord);
		break;
	case 2:
		_ptr = new Calipers(coord);
		break;
	case 3:
		_ptr = new F_Calipers(coord);
		break;
	case 4:
		_ptr = new T_Form(coord);
		break;
	case 5:
		_ptr = new G_Form(coord);
		break;
	case 6:
		_ptr = new F_G_Form(coord);
		break;
	default:
		isShape = false;
		//assert(false && "engine() rand > 7");
		break;
	}
	return _ptr;
}

bool TestApp::isCellEmpty(int x, int y) { return (GetChar(x, y) == L' '); }

void TestApp::KeyPressed(int btnCode)
{
	//управление(Unicode)
	switch (btnCode)
	{
	//-----------Shape--------------
	//case 69:  //E
	//case 101: //e
	//case 119: //w
	//case 87:  //W
	//	isShape = false;
	//	shape_ptr->SetShape(*this, L' ');
	//	break;
	//case 72:  //↑
	//	shape_ptr->moveUp(*this);
	//	break;
	case 83:  //S 
	case 115: //s
	case 80:  //↓
		isDown = true;
		break;
	case 65:  //A
	case 97:  //a
	case 75:  //←
		if (!isDown)
			shape_ptr->moveLeft(*this);
		break;
	case 68:  //D
	case 100: //d
	case 77:  //→
		if (!isDown)
			shape_ptr->moveRight(*this);
		break;
	case 72:  //↑
	//case 32:  //Space
	case 119: //w
	case 87:  //W
		if (!isDown) {
			shape_ptr->SetShape(*this, L' ');
			shape_ptr->changePosition(*this);

			//перерисовываем текущую фигуру
			DrawShape(shape_ptr, 10, COORD{ 22, 13 });
		}
		break;
	case 27:  //Esc
	case 32:  //Space
		SetConsoleCursor(7, 10);
		std::cout << "PAUSE";
		int temp = 0;
		do temp = _getch();
		while ((temp != 32) && (temp != 27));
		break;
	//------------------------------
	/*default:
		break;*/
	}
}
//обновление игрового поля
void TestApp::UpdateF(float deltaTime)
{
	if (!next_shape_ptr)
	{
		next_shape_ptr = GetRandShape(COORD{ 8 , 2 });

		//рисуем следующую фигуру
		DrawShape(next_shape_ptr, 10, COORD{ 22, 6 });
	}

	if (!isShape)
	{
		if (shape_ptr) 
			delete shape_ptr;

		shape_ptr = next_shape_ptr;
		next_shape_ptr = nullptr;
		isShape = true;

		//рисуем текущую фигуру
		DrawShape(shape_ptr, 10, COORD{ 22, 13 });
	}

	if (shape_ptr)
	shape_ptr->SetShape(*this, 10);

	//-----------------------------

	//RenderSystemDrawText(20, 10, (std::to_string(deltaTime)).c_str());
	RenderSystemDrawText(21, 3, "NEXT");
	RenderSystemDrawText(19, 10, "CURRENT");
	RenderSystemDrawText(20, 17, "SCORE");
	if (score == 0)
		RenderSystemDrawText(22, 19, (std::to_string(score).c_str()));
	else if ((score >= 100) && (score < 1000))
		RenderSystemDrawText(21, 19, (std::to_string(score).c_str()));
	else if (score >= 1000)
		RenderSystemDrawText(20, 19, (std::to_string(score).c_str()));

	//-----------------------------
	if (isDown) speed = 10; 
	else speed = 450;

	sum += deltaTime;
	if (sum >= speed)
	{
		if (!shape_ptr->moveDown(*this))
		{
			isDown = false;
			isShape = false;
			shape_ptr->SetShape(*this, 10);
			CheckBlocks();

			//завершает главный цикл игры
			if (next_shape_ptr && !(next_shape_ptr->checkPosition(*this))) 
				isGameActive = false;
		}
		else shape_ptr->SetShape(*this, 10);
		sum = 0;
	}
}




