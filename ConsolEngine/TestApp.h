#pragma once
//#define NDEBAG //DEBAG и NDEBAG

#include <random>
#include <cassert>
#include <conio.h>

#include "BaseApp.h"
#include "Shape.h"
//#include "Main_Menu.hpp"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		float sum = 0.0;	// связано с фпс
		float speed;
		bool isDown = false;
		//int score;


		Shape * shape_ptr = nullptr;
		Shape * next_shape_ptr = nullptr;
		bool isShape = false;

		std::vector<std::vector<wchar_t>> Blocks;
		std::vector<wchar_t> new_row;
		bool isMenuActive = false;	// меню

		//рандом
		std::default_random_engine engine; //minstd_rand, mt19937, mt19937_64, default_random_engine
		std::random_device device;

	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		bool isCellEmpty(int x, int y);
		Shape * GetRandShape(COORD coord);
		void CheckBlocks();
		//int GetScore() const;
		void DrawShape(Shape * _ptr, wchar_t symbol, COORD c);
		void ClearBlocks();	// очищает игровое поле
		//void MainMenu();
};
