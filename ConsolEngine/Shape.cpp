#include "Shape.h"

//-------------Shape-----------------

short one = 1;
short two = 2;

void Shape::SetShape(BaseApp &base, wchar_t symbol) {
	base.SetChar(a.X, a.Y, symbol);
	base.SetChar(b.X, b.Y, symbol);
	base.SetChar(c.X, c.Y, symbol);
	base.SetChar(d.X, d.Y, symbol);
}

void Shape::SetShape(BaseApp &base, wchar_t symbol, COORD c_) {
	short x_diff = c_.X - b.X;
	short y_diff = c_.Y - b.Y;

	base.SetChar(a.X + x_diff, a.Y + y_diff, symbol);
	base.SetChar(b.X + x_diff, b.Y + y_diff, symbol);
	base.SetChar(c.X + x_diff, c.Y + y_diff, symbol);
	base.SetChar(d.X + x_diff, d.Y + y_diff, symbol);
}

bool Shape::checkPosition(COORD new_a, COORD new_b, COORD new_c, COORD new_d, BaseApp &base) const {
	return  ((base.GetChar(new_a.X, new_a.Y) == L' ') &&
			 (base.GetChar(new_b.X, new_b.Y) == L' ') &&
			 (base.GetChar(new_c.X, new_c.Y) == L' ') &&
			 (base.GetChar(new_d.X, new_d.Y) == L' '));
}

bool Shape::checkPosition(BaseApp &base) const {
	return checkPosition(a, b, c, d, base);
}

void Shape::moveLeft(BaseApp &base) {
	SetShape(base, L' ');
	if (checkPosition(
		COORD{ a.X - one, a.Y }, 
		COORD{ b.X - one, b.Y }, 
		COORD{ c.X - one, c.Y },
		COORD{ d.X - one, d.Y },
		base))
	{
		a.X -= one;
		b.X -= one;
		c.X -= one;
		d.X -= one;
	}
}

void Shape::moveRight(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X + one, a.Y) == L' ') &&
		(base.GetChar(b.X + one, b.Y) == L' ') &&
		(base.GetChar(c.X + one, c.Y) == L' ') &&
		(base.GetChar(d.X + one, d.Y) == L' '))
	{
		a.X += one;
		b.X += one;
		c.X += one;
		d.X += one;
	}
}

bool Shape::moveDown(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X, a.Y + one) == L' ') &&
		(base.GetChar(b.X, b.Y + one) == L' ') &&
		(base.GetChar(c.X, c.Y + one) == L' ') &&
		(base.GetChar(d.X, d.Y + one) == L' '))
	{
		a.Y += one;
		b.Y += one;
		c.Y += one;
		d.Y += one;
		return true;
	}
	else return false;
}

void Shape::moveUp(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X, a.Y - one) == L' ') &&
		(base.GetChar(b.X, b.Y - one) == L' ') &&
		(base.GetChar(c.X, c.Y - one) == L' ') &&
		(base.GetChar(d.X,d.Y - one) == L' '))
	{
		a.Y -= one;
		b.Y -= one;
		c.Y -= one;
		d.Y -= one;
	}
}

//----------Quadrate---------------

Quadrate::Quadrate(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += one;
	c = spawn; c.X += one;
	d = spawn; d.X += one; d.Y += one;
	position = 0;
}

void Quadrate::changePosition(BaseApp &base) {}

//------------Line------------------

Line::Line(COORD spawn)
{
	a = spawn; 
	b = spawn; b.X += one;
	c = spawn; c.X += two;
	d = spawn; d.X -= one; 
	position = 0;
}

void Line::changePosition(BaseApp &base) {
	if (!position) //position == 0
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X - one, b.Y + one },
			COORD{ c.X - two, c.Y + two },
			COORD{ d.X + one, d.Y - one },
			base))
		{
			b.X -= one; b.Y += one;
			c.X -= two; c.Y += two;
			d.X += one; d.Y -= one;
			position = one;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X + one, b.Y - one },
			COORD{ c.X + two, c.Y - two },
			COORD{ d.X - one, d.Y + one },
			base))
		{
			b.X += one; b.Y -= one;
			c.X += two; c.Y -= two;
			d.X -= one; d.Y += one;
			position = 0;
		}
	}
}

//----------Calipers----------------

Calipers::Calipers(COORD spawn)
{
	a = spawn; 
	b = spawn; b.Y += one;
	c = spawn; c.X -= one;
	d = spawn; d.X += one; d.Y += one;
	position = 0;
}

void Calipers::changePosition(BaseApp &base) { //Z
	if (!position) 
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y + one },
			COORD{ d.X - two, d.Y + one },
			base))
		{
			c.Y += one;
			d.X -= two; d.Y += one;
			position = one;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y - one },
			COORD{ d.X + two, d.Y - one },
			base))
		{
			c.Y -= one;
			d.X += two; d.Y -= one;
			position = 0;
		}
	}
}


//-------Forward_Calipers-----------

F_Calipers::F_Calipers(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += one;
	c = spawn; c.X += one;
	d = spawn; d.X -= one; d.Y += one;
	position = 0;
}

void F_Calipers::changePosition(BaseApp &base) {
	if (!position)
	{
		if (checkPosition(
			COORD{ a.X - one, a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y + two },
			COORD{ d.X , d.Y},
			base))
		{
			a.X -= one;
			c.X -= one; c.Y += two;
			position = one;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X + one, a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X + one , c.Y - two },
			COORD{ d.X , d.Y },
			base))
		{
			a.X += one;
			c.X += one; c.Y -= two;
			position = 0;
		}
	}
}

//-----------T_Form-----------------

T_Form::T_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += one;
	c = b; c.X -= one;
	d = b; d.X += one;
	position = 0;
}

void T_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + one, a.Y + one },
			COORD{ b.X , b.Y },
			COORD{ c.X + one, c.Y - one },
			COORD{ d.X - one , d.Y + one},
			base))
		{
			a.X += one; a.Y += one;
			c.X += one; c.Y -= one;
			d.X -= one; d.Y += one;
			position = one;
		}
	}
	else if (position == one)
	{
		if (checkPosition(
			COORD{ a.X - one, a.Y + one },
			COORD{ b.X , b.Y },
			COORD{ c.X + one , c.Y + one },
			COORD{ d.X - one , d.Y - one },
			base))
		{
			a.X -= one; a.Y += one;
			c.X += one; c.Y += one;
			d.X -= one; d.Y -= one;
			position = two;
		}
	}
	else if (position == two)
	{
		if (checkPosition(
			COORD{ a.X - one , a.Y - one },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y + one },
			COORD{ d.X + one, d.Y - one},
			base))
		{
			a.X -= one; a.Y -= one;
			c.X -= one; c.Y += one;
			d.X += one; d.Y -= one;
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + one , a.Y - one },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y - one },
			COORD{ d.X + one, d.Y + one},
			base))
		{
			a.X += one; a.Y -= one;
			c.X -= one; c.Y -= one;
			d.X += one; d.Y += one;
			position = 0;
		}
	}
}

//-----------G_Form-----------------

G_Form::G_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += one;
	c = spawn; c.Y += two;
	d = c;  d.X -= one;
}

void G_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + one, a.Y + one},
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y - one},
			COORD{ d.X , d.Y - two },
			base))
		{
			a.X += one; a.Y += one;
			c.X -= one; c.Y -= one;
			d.Y -= two;
			position = one;
		}
	}
	else if (position == one)
	{
		if (checkPosition(
			COORD{ a.X - one, a.Y + one },
			COORD{ b.X , b.Y },
			COORD{ c.X + two, c.Y - one },
			COORD{ d.X + one, d.Y },
			base))
		{
			a.X -= one; a.Y += one;
			c.X += two; c.Y -= one;
			d.X += one;
			position = two;
		}
	}
	else if (position == two)
	{
		if (checkPosition(
			COORD{ a.X - one , a.Y - one},
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y + one },
			COORD{ d.X + one, d.Y + two },
			base))
		{
			a.X -= one; a.Y -= one;
			c.Y += one;
			d.X += one; d.Y += two;
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + one , a.Y - one },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y + one },
			COORD{ d.X - two , d.Y },
			base))
		{
			a.X += one; a.Y -= one;
			c.X -= one; c.Y += one;
			d.X -= two; 
			position = 0;
		}
	}
}

//----------F_G_Form----------------

F_G_Form::F_G_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += one;
	c = spawn; c.Y += two;
	d = c; d.X += one;
}

void F_G_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + one, a.Y + one },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y - one },
			COORD{ d.X - two, d.Y },
			base))
		{
			a.X += one; a.Y += one;
			c.X -= one; c.Y -= one;
			d.X -= two;
			position = one;
		}
	}
	else if (position == one)
	{
		if (checkPosition(
			COORD{ a.X - one, a.Y + one },
			COORD{ b.X , b.Y },
			COORD{ c.X + one, c.Y - one },
			COORD{ d.X , d.Y - two },
			base))
		{
			a.X -= one; a.Y += one;
			c.X += one; c.Y -= one;
			d.Y -= two;
			position = two;
		}
	}
	else if (position == two)
	{
		if (checkPosition(
			COORD{ a.X - one , a.Y - one },
			COORD{ b.X , b.Y },
			COORD{ c.X + one, c.Y + one },
			COORD{ d.X + two , d.Y },
			base))
		{
			a.X -= one; a.Y -= one;
			c.X += one; c.Y += one;
			d.X += two; 
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + one , a.Y - one },
			COORD{ b.X , b.Y },
			COORD{ c.X - one , c.Y + one },
			COORD{ d.X , d.Y + two},
			base))
		{
			a.X += one; a.Y -= one;
			c.X -= one; c.Y += one;
			d.Y += two;
			position = 0;
		}
	}
}