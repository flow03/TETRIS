#include "..\hpp\Shape.h"

//-------------Shape-----------------

void Shape::SetShape(BaseApp &base, wchar_t symbol) {
	base.SetChar(a.X, a.Y, symbol);
	base.SetChar(b.X, b.Y, symbol);
	base.SetChar(c.X, c.Y, symbol);
	base.SetChar(d.X, d.Y, symbol);
}

void Shape::SetShape(BaseApp &base, COORD c_, wchar_t symbol) {
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
		COORD{ a.X - 1, a.Y }, 
		COORD{ b.X - 1, b.Y }, 
		COORD{ c.X - 1, c.Y },
		COORD{ d.X - 1, d.Y },
		base))
	{
		a.X -= 1;
		b.X -= 1;
		c.X -= 1;
		d.X -= 1;
	}
}

void Shape::moveRight(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X + 1, a.Y) == L' ') &&
		(base.GetChar(b.X + 1, b.Y) == L' ') &&
		(base.GetChar(c.X + 1, c.Y) == L' ') &&
		(base.GetChar(d.X + 1, d.Y) == L' '))
	{
		a.X += 1;
		b.X += 1;
		c.X += 1;
		d.X += 1;
	}
}

bool Shape::moveDown(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X, a.Y + 1) == L' ') &&
		(base.GetChar(b.X, b.Y + 1) == L' ') &&
		(base.GetChar(c.X, c.Y + 1) == L' ') &&
		(base.GetChar(d.X, d.Y + 1) == L' '))
	{
		a.Y += 1;
		b.Y += 1;
		c.Y += 1;
		d.Y += 1;
		return true;
	}
	else return false;
}

void Shape::moveUp(BaseApp &base) {
	SetShape(base, L' ');
	if ((base.GetChar(a.X, a.Y - 1) == L' ') &&
		(base.GetChar(b.X, b.Y - 1) == L' ') &&
		(base.GetChar(c.X, c.Y - 1) == L' ') &&
		(base.GetChar(d.X,d.Y - 1) == L' '))
	{
		a.Y -= 1;
		b.Y -= 1;
		c.Y -= 1;
		d.Y -= 1;
	}
}

//----------Quadrate---------------

Quadrate::Quadrate(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += 1;
	c = spawn; c.X += 1;
	d = spawn; d.X += 1; d.Y += 1;
	position = 0;
}

void Quadrate::changePosition(BaseApp &base) {}

//------------Line------------------

Line::Line(COORD spawn)
{
	a = spawn; 
	b = spawn; b.X += 1;
	c = spawn; c.X += 2;
	d = spawn; d.X -= 1; 
	position = 0;
}

void Line::changePosition(BaseApp &base) {
	if (!position) //position == 0
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X - 1, b.Y + 1 },
			COORD{ c.X - 2, c.Y + 2 },
			COORD{ d.X + 1, d.Y - 1 },
			base))
		{
			b.X -= 1; b.Y += 1;
			c.X -= 2; c.Y += 2;
			d.X += 1; d.Y -= 1;
			position = 1;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X + 1, b.Y - 1 },
			COORD{ c.X + 2, c.Y - 2 },
			COORD{ d.X - 1, d.Y + 1 },
			base))
		{
			b.X += 1; b.Y -= 1;
			c.X += 2; c.Y -= 2;
			d.X -= 1; d.Y += 1;
			position = 0;
		}
	}
}

//----------Calipers----------------

Calipers::Calipers(COORD spawn)
{
	a = spawn; 
	b = spawn; b.Y += 1;
	c = spawn; c.X -= 1;
	d = spawn; d.X += 1; d.Y += 1;
	position = 0;
}

void Calipers::changePosition(BaseApp &base) { //Z
	if (!position) 
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y + 1 },
			COORD{ d.X - 2, d.Y + 1 },
			base))
		{
			c.Y += 1;
			d.X -= 2; d.Y += 1;
			position = 1;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X , a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y - 1 },
			COORD{ d.X + 2, d.Y - 1 },
			base))
		{
			c.Y -= 1;
			d.X += 2; d.Y -= 1;
			position = 0;
		}
	}
}


//-------Forward_Calipers-----------

F_Calipers::F_Calipers(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += 1;
	c = spawn; c.X += 1;
	d = spawn; d.X -= 1; d.Y += 1;
	position = 0;
}

void F_Calipers::changePosition(BaseApp &base) {
	if (!position)
	{
		if (checkPosition(
			COORD{ a.X - 1, a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y + 2 },
			COORD{ d.X , d.Y},
			base))
		{
			a.X -= 1;
			c.X -= 1; c.Y += 2;
			position = 1;
		}
	}
	else
	{
		if (checkPosition(
			COORD{ a.X + 1, a.Y },
			COORD{ b.X , b.Y },
			COORD{ c.X + 1 , c.Y - 2 },
			COORD{ d.X , d.Y },
			base))
		{
			a.X += 1;
			c.X += 1; c.Y -= 2;
			position = 0;
		}
	}
}

//-----------T_Form-----------------

T_Form::T_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += 1;
	c = b; c.X -= 1;
	d = b; d.X += 1;
	position = 0;
}

void T_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + 1, a.Y + 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X + 1, c.Y - 1 },
			COORD{ d.X - 1 , d.Y + 1},
			base))
		{
			a.X += 1; a.Y += 1;
			c.X += 1; c.Y -= 1;
			d.X -= 1; d.Y += 1;
			position = 1;
		}
	}
	else if (position == 1)
	{
		if (checkPosition(
			COORD{ a.X - 1, a.Y + 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X + 1 , c.Y + 1 },
			COORD{ d.X - 1 , d.Y - 1 },
			base))
		{
			a.X -= 1; a.Y += 1;
			c.X += 1; c.Y += 1;
			d.X -= 1; d.Y -= 1;
			position = 2;
		}
	}
	else if (position == 2)
	{
		if (checkPosition(
			COORD{ a.X - 1 , a.Y - 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y + 1 },
			COORD{ d.X + 1, d.Y - 1},
			base))
		{
			a.X -= 1; a.Y -= 1;
			c.X -= 1; c.Y += 1;
			d.X += 1; d.Y -= 1;
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + 1 , a.Y - 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y - 1 },
			COORD{ d.X + 1, d.Y + 1},
			base))
		{
			a.X += 1; a.Y -= 1;
			c.X -= 1; c.Y -= 1;
			d.X += 1; d.Y += 1;
			position = 0;
		}
	}
}

//-----------G_Form-----------------

G_Form::G_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += 1;
	c = spawn; c.Y += 2;
	d = c;  d.X -= 1;
}

void G_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + 1, a.Y + 1},
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y - 1},
			COORD{ d.X , d.Y - 2 },
			base))
		{
			a.X += 1; a.Y += 1;
			c.X -= 1; c.Y -= 1;
			d.Y -= 2;
			position = 1;
		}
	}
	else if (position == 1)
	{
		if (checkPosition(
			COORD{ a.X - 1, a.Y + 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X + 2, c.Y - 1 },
			COORD{ d.X + 1, d.Y },
			base))
		{
			a.X -= 1; a.Y += 1;
			c.X += 2; c.Y -= 1;
			d.X += 1;
			position = 2;
		}
	}
	else if (position == 2)
	{
		if (checkPosition(
			COORD{ a.X - 1 , a.Y - 1},
			COORD{ b.X , b.Y },
			COORD{ c.X , c.Y + 1 },
			COORD{ d.X + 1, d.Y + 2 },
			base))
		{
			a.X -= 1; a.Y -= 1;
			c.Y += 1;
			d.X += 1; d.Y += 2;
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + 1 , a.Y - 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y + 1 },
			COORD{ d.X - 2 , d.Y },
			base))
		{
			a.X += 1; a.Y -= 1;
			c.X -= 1; c.Y += 1;
			d.X -= 2; 
			position = 0;
		}
	}
}

//----------F_G_Form----------------

F_G_Form::F_G_Form(COORD spawn)
{
	a = spawn;
	b = spawn; b.Y += 1;
	c = spawn; c.Y += 2;
	d = c; d.X += 1;
}

void F_G_Form::changePosition(BaseApp &base) {
	if (position == 0)
	{
		if (checkPosition(
			COORD{ a.X + 1, a.Y + 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y - 1 },
			COORD{ d.X - 2, d.Y },
			base))
		{
			a.X += 1; a.Y += 1;
			c.X -= 1; c.Y -= 1;
			d.X -= 2;
			position = 1;
		}
	}
	else if (position == 1)
	{
		if (checkPosition(
			COORD{ a.X - 1, a.Y + 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X + 1, c.Y - 1 },
			COORD{ d.X , d.Y - 2 },
			base))
		{
			a.X -= 1; a.Y += 1;
			c.X += 1; c.Y -= 1;
			d.Y -= 2;
			position = 2;
		}
	}
	else if (position == 2)
	{
		if (checkPosition(
			COORD{ a.X - 1 , a.Y - 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X + 1, c.Y + 1 },
			COORD{ d.X + 2 , d.Y },
			base))
		{
			a.X -= 1; a.Y -= 1;
			c.X += 1; c.Y += 1;
			d.X += 2; 
			position = 3;
		}
	}
	else if (position == 3)
	{
		if (checkPosition(
			COORD{ a.X + 1 , a.Y - 1 },
			COORD{ b.X , b.Y },
			COORD{ c.X - 1 , c.Y + 1 },
			COORD{ d.X , d.Y + 2},
			base))
		{
			a.X += 1; a.Y -= 1;
			c.X -= 1; c.Y += 1;
			d.Y += 2;
			position = 0;
		}
	}
}