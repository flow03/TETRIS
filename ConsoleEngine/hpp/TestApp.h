#pragma once
//#define NDEBAG //DEBAG и NDEBAG

#include <random>
#include <cassert>
#include <conio.h>

#include "..\hpp\BaseApp.h"
#include "..\hpp\Shape.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		float sum = 0.0;
		float speed;
		bool isDown = false;
		//int score;


		Shape * shape_ptr = nullptr;
		Shape * next_shape_ptr = nullptr;
		bool isShape = false;

		std::vector<std::vector<wchar_t>> Blocks;
		std::vector<wchar_t> new_row;

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
		void DrawShape(Shape * _ptr, COORD c);
};
