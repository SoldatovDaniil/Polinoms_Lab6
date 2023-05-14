#pragma once
#include"List.h"
#include<math.h>
#include<iostream>
#include<string>

using namespace std;


class Monom
{
public:
	double coef = 1.;
	double degX;
	double degY;
	double degZ;

	Monom(double c = 1., double x = 0., double y = 0., double z = 0.) : coef(c), degX(x), degY(y), degZ(z) { ; }

	Monom(const Monom& mOther)
	{
		coef = mOther.coef;
		degX = mOther.degX;
		degY = mOther.degY;
		degZ = mOther.degZ;
	}

	double getX() { return degX; }
	double getY() { return degY; }
	double getZ() { return degZ; }
	double getCoef() { return coef; }
	void print() {
		std::cout << coef << "  " << degX << "  " << degY << "  " << degZ << "  " << std::endl;
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
	// false
	bool operator>=(const Monom& other)
	{
		if (degX < other.degX)
		{
			return true;

		}
		else if ((degX == other.degX) && (degY < other.degY))
		{
			return true;
		}
		else if ((degX == other.degX) && (degY == other.degY) && (degZ < other.degZ))
		{
			return true;
		}
		else
		{
			return false;
		}
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
	// по степеням
	bool operator==(const Monom& mOther) const
	{
		if ((degX == mOther.degX) && (degY == mOther.degY) && (degZ == mOther.degZ))
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
		return !((*this) == mOther);
	}

	//интеграл по переменной
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

	//производная по переменной
	Monom deriv(char var)
	{
		Monom res(*this);
		switch (var)
		{
		case 'x':
			if (degX == 0)
			{
				res.coef = 0;
				res.degX = 0;
				res.degY = 0;
				res.degZ = 0;
				break;
			}
			res.coef *= res.degX;
			res.degX -= 1.;
			break;
		case 'y':
			if (degY == 0)
			{
				res.coef = 0;
				res.degX = 0;
				res.degY = 0;
				res.degZ = 0;
				break;
			}
			res.coef *= res.degY;
			res.degY -= 1.;
			break;
		case 'z':
			if (degZ == 0)
			{
				res.coef = 0;
				res.degX = 0;
				res.degY = 0;
				res.degZ = 0;
				break;
			}
			res.coef *= res.degZ;
			res.degZ -= 1.;
			break;
		}
		return res;
	}

	//Значение в точке(Значение при известных только х, у, z, х и у, х и z, и т.д)
	double pointValue(double x = 1, double y = 1, double z = 1)
	{
		double res = 0.0;
		res = coef * (pow(x, degX) * pow(y, degY) * pow(z, degZ));
		return res;
	}

	//Вывод(Сделать без лишних нулей у коэфициентов), можно и с нулями
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

	//на вход будет приходить строка(гарантировано правильная) и имя полинома
	//коснтруктор по умолчанию,с параметрами, копирования, оператор = и деструктор

	List<Monom>::iterator begin()
	{
		return monoms.begin();
	}

	List<Monom>::iterator end()
	{
		return monoms.end();
	}

	//	List<Monom>::iterator cbegin() const
	//{
		//return monoms.cbegin();
	//}

	Polinom() : name('a') {};

	Polinom(Monom& mon)
	{
		name = 'a';
		monoms.push_back(mon);
	}

	Polinom(const Polinom& pol) {
		name = pol.name;
		monoms = pol.monoms;
	}

	Polinom(char n, List<Monom> monomy)
	{
		monoms = monomy;
		name = n;
	}

	Polinom& operator=(const Polinom& pol)
	{
		name = pol.name;
		monoms = pol.monoms;
		return *this;
	}

	void print() {
		cout << "\nPolinom " << name << " = ";
		auto it = monoms.begin();
		while (it != nullptr) {
			(*it).print();
			it++;
		}
	}
	void addMonominPolinom(const Monom& mon)
	{
		auto it = monoms.begin();
		while (it != nullptr) {
			if (((*it).degX == mon.degX) && ((*it).degY == mon.degY) && ((*it).degZ == mon.degZ))
			{
				(*it) = (*it) + mon;
				return;
			}
			it++;
		}
		monoms.push_back(mon);
		return;
	}

	Polinom operator+(const Polinom& pol)
	{
		Polinom tmp(*this);
		auto it2 = (pol.monoms).begin();
		while (it2 != nullptr) {
			tmp.addMonominPolinom(*it2);
			it2++;
		}
		return tmp;
	}

	void subMonominPolinom(const Monom& mon) {
		Monom minus(mon);
		minus = minus * (-1);
		this->addMonominPolinom(minus);
	}

	Polinom operator-(const Polinom& pol)
	{
		Polinom tmp(*this);
		tmp.name = pol.name;
		auto it2 = (pol.monoms).begin();
		while (it2 != nullptr) {
			tmp.subMonominPolinom(*it2);
			it2++;
		}
		return tmp;
	}

	void addfortest(const Monom& mon) { // for test
		monoms.push_back(mon);
	}

	void doSimple() { //привести подобные слагаемые можно сделать легче с tmp и методом addmoninpol
		auto it1 = monoms.begin();
		auto it2 = monoms.begin();
		auto it3 = monoms.begin();
		while (it1 != nullptr) {
			it2 = monoms.begin();
			while (it2 != nullptr) {
				if (((*it1).degX == (*it2).degX) && ((*it1).degY == (*it2).degY) && ((*it1).degZ == (*it2).degZ) && (it1 != it2)) {
					(*it1) = (*it1) + (*it2);
					monoms.erase_after(it3);
					it2 = it3;
				}
				else
				{
					it3 = it2;
					it2++;
				}
			}
			it1++;
		}
	}

	bool operator==(const Polinom& p) const
	{
		Polinom p1(*this);
		Polinom p2(p);
		p1.sort();
		p2.sort();
		auto it1 = p1.monoms.begin();
		auto it2 = p2.monoms.begin();
		while ((it1 != nullptr) || (it2 != nullptr))
		{
			if (((*it1) != (*it2)) || ((*it1).getCoef() != (*it2).getCoef()))
			{
				return false;
			}
			it1++;
			it2++;
		}
		if ((it1 != nullptr) || (it2 != nullptr))
		{
			return false;
		}
		return true;
	}
	bool operator!=(const Polinom& p) const
	{
		return !((*this) == p);
	}
	Polinom operator*(const Polinom& pol)
	{
		Polinom tmp;
		tmp.name = name;
		auto it1 = monoms.begin();
		auto it2 = (pol.monoms).begin();
		while (it1 != nullptr)
		{
			it2 = (pol.monoms).begin();
			while (it2 != nullptr)
			{
				tmp.addMonominPolinom((*it1) * (*it2));
				it2++;
			}
			it1++;
		}
		tmp.doSimple();
		return tmp;
	}

	Polinom operator/(const Polinom& pol)
	{
		Polinom tmp;
		tmp.name = pol.name;
		Polinom q(*this);
		Polinom p(pol);
		q.sort();
		p.sort();
		Monom t;
		auto it1 = (q.monoms).begin();
		auto it2 = (p.monoms).begin();
		while ((it1 != nullptr) && ((*it1).degX >= (*it2).degX) && ((*it1).degY >= (*it2).degY) && ((*it1).degZ >= (*it2).degZ))
		{
			t = (*it1) / (*it2);
			tmp.addMonominPolinom(t);
			q = q - (Polinom(t) * p);
			(q.monoms).pop_front();
			it1 = q.begin();
		}
		return tmp;
	}

	Polinom integral(char var)
	{
		Polinom res;
		res.name = name;
		auto it = monoms.begin();
		while (it != nullptr)
		{
			res.addMonominPolinom((*it).integral(var));
			it++;
		}
		return res;
	}

	Polinom deriv(char var)
	{
		Polinom res;
		res.name = name;
		auto it = monoms.begin();
		while (it != nullptr)
		{
			if (((var == 'x') && ((*it).degX != 0)) || ((var == 'y') && ((*it).degY != 0)) || ((var == 'z') && ((*it).degZ != 0)))
			{
				res.addMonominPolinom((*it).deriv(var));
			}
			it++;
		}
		if (res.monoms.begin() == nullptr)
		{
			Monom m(0, 0, 0, 0);
			res.addMonominPolinom(m);
		}
		return res;
	}

	double pointValue(double x = 1, double y = 1, double z = 1)
	{
		double res = 0.0;
		auto it = monoms.begin();
		while (it != nullptr)
		{
			res += (*it).pointValue(x, y, z);
			it++;
		}
		return res;
	}

	void sort()
	{
		monoms.mergeSort();
	}
	char getName()
	{
		return this->name;
	}

		//Вывод
	friend ostream& operator<<(ostream& ostr, const Polinom& p)
	{
		ostr << p.name << " = ";
		auto it = (p.monoms).begin();
		while (it != (p.monoms).end())
		{
			ostr << (*it).coef << "x^" << (*it).degX << "y^" << (*it).degY << "z^" << (*it).degZ << " + ";
			it++;
		}
		ostr << (*it).coef << "x^" << (*it).degX << "y^" << (*it).degY << "z^" << (*it).degZ;
		return ostr;
	}
};