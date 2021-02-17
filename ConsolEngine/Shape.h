#pragma once

#include <Windows.h>
#include "BaseApp.h"


class Shape 
{
public:
	//������ ��������� ������
	virtual void changePosition(BaseApp &base) = 0;
	//������ ������ ��������� �������� �� � ����������� �����������
	void SetShape(BaseApp &base, wchar_t symbol);
	//������ ������ ��������� �������� � ��������� �����
	void SetShape(BaseApp &base, wchar_t symbol, COORD c_);
	//��������� ����� ������� �� ������ �������
	bool checkPosition(COORD new_a, COORD new_b, COORD new_c, COORD new_d, BaseApp &base) const;
	//��������� ������� ������� 
	bool checkPosition(BaseApp &base) const;

	void moveLeft(BaseApp &base);
	void moveRight(BaseApp &base);
	bool moveDown(BaseApp &base); // ���������� bool
	void moveUp(BaseApp &base);

protected:
	COORD a;
	COORD b;
	COORD c;
	COORD d;

	int position = 0; 
};

class Quadrate : public Shape
{
public:
	Quadrate(COORD spawn);

	void changePosition(BaseApp &base);
};

class Line : public Shape
{
public:
	Line(COORD spawn);

	void changePosition(BaseApp &base);
};

class Calipers : public Shape
{
public:
	Calipers(COORD spawn);

	void changePosition(BaseApp &base);
};
//Forward
class F_Calipers : public Shape
{
public:
	F_Calipers(COORD spawn);

	void changePosition(BaseApp &base);
};

class T_Form : public Shape
{
public:
	T_Form(COORD spawn);

	void changePosition(BaseApp &base);
};

class G_Form : public Shape
{
public:
	G_Form(COORD spawn);

	void changePosition(BaseApp &base);
};

class F_G_Form : public Shape
{
public:
	F_G_Form(COORD spawn);

	void changePosition(BaseApp &base);
};



