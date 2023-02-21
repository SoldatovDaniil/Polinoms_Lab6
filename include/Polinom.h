#pragma once
#include"List.h"
#include<math.h>
#include<iostream>
#include<string>

using namespace std;


class Monom
{
public:
	double coef;
	double degX;
	double degY;
	double degZ;


	Monom(double c = 1., double x = 0., double y = 0., double z = 0.) : coef{ c }, degX{ x }, degY{ y }, degZ{ z }
	{}

	Monom(const Monom& mOther)
	{
		coef = mOther.coef;
		degX = mOther.degX;
		degY = mOther.degY;
		degZ = mOther.degZ;
	}

	~Monom()
	{
		coef = 0;
		degX = 0;
		degY = 0;
		degZ = 0;
	}

	Monom& operator=(const Monom& mOther)
	{
		coef = mOther.coef;
		degX = mOther.degX;
		degY = mOther.degY;
		degZ = mOther.degZ;
		return *this;
	}

	Monom operator+(const Monom& mOther)
	{	
		Monom res(*this);
		res.coef += mOther.coef;
		return res;
	}

	Monom operator*(const Monom& mOther)
	{
		Monom res(*this);
		res.coef *= mOther.coef;
		res.degX += mOther.degX;
		res.degY += mOther.degY;
		res.degZ += mOther.degZ;
		return res;
	}

	Monom operator/(const Monom& mOther)
	{
		Monom res(*this);
		res.coef /= mOther.coef;
		res.degX -= mOther.degX;
		res.degY -= mOther.degY;
		res.degZ -= mOther.degZ;
		return res;
	}

	Monom operator*(double n)
	{
		Monom res(*this);
		res.coef *= n;
		return res;
	}

	Monom operator/(double n)
	{
		Monom res(*this);
		res.coef /= n;
		return res;
	}

	bool operator==(const Monom& mOther) const 
	{
		if ((coef == mOther.coef) && (degX == mOther.degX) && (degY == mOther.degY) && (degZ == mOther.degZ))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const Monom& mOther) const
	{
		return(!(*this == mOther));
	}

	//ѕроизводна€ по переменной
	Monom deriv(char var)
	{
		Monom res(*this);
		switch (var)
		{
		case 'x':
			res.coef *= res.degX;
			res.degX -= 1.;
			break;
		case 'y':
			res.coef *= res.degY;
			res.degY -= 1.;
			break;
		case 'z':
			res.coef *= res.degZ;
			res.degZ -= 1.;
			break;
		}
		return res; 
	}

	//»нтеграл по переменной
	Monom integral(char var)
	{
		Monom res(*this);
		switch (var)
		{
		case 'x':
			res.coef /= res.degX + 1.;
			res.degX += 1.;
			break;
		case 'y':
			res.coef /= res.degY + 1.;
			res.degY += 1.;
			break;
		case 'z':
			res.coef /= res.degZ + 1.;
			res.degZ += 1.;
			break;
		}
		return res;
	}

	//«начение в точке(«начение при известных только х, у, z, х и у, х и z, и т.д)
	Monom pointValue(double x = 1, double y = 1, double z = 1)
	{
		Monom res(coef);
		res.coef *= (pow(x, degX) * pow(y, degY) * pow(z, degZ));
		return res;
	}

	//¬ывод(—делать без лишних нулей у коэфициентов)
	friend ostream& operator<<(ostream& ostr, const Monom& m)
	{
		if (m.coef != 1)
		{
			ostr << m.coef << "x^" << m.degX << "y^" << m.degY << "z^" << m.degZ;
		}
		else
		{
			ostr << "x^" << m.degX << "y^" << m.degY << "z^" << m.degZ;
		}
		return ostr;
	}

};


class Polinom
{
public:
	char name;
	List<Monom> monoms;

	//на вход будет приходить строка(гарантировано правильна€) и им€ полинома
	//коснтруктор по умолчанию,с параметрами, копировани€, оператор = и деструктор
	Polinom()
	{
		name = ' ';
	}

	Polinom(char& n, string& inpStr)
	{
		name = n;
	}

	/*Polinom operator+(const Polinom& pOther)
	{
		условие на равенство степеней
	}*/

	/*Polinom operator*(const Polinom& pOther)
	{
	}*/

	/*Polinom operator/(const Polinom& pOther)
	{
	}*/

	char getName()
	{
		return this->name;
	}

	//¬ывод
	/*friend ostream& operator<<(ostream& ostr, const Polinom& p)
	{
	}*/
};

//на вход прога получает строку с полиномами.
//парсим строку, находим полиномы, создаЄм массив полиномов, в исходной строке полиномы замен€ем именами(типа a, b, c, d и т.д.).
//получаем выражение из полиномов, его + массив полиномов отправл€ем в трансл€тор.