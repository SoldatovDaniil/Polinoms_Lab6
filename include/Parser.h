#pragma once
#include"Polinom.h"
#include<iostream>
#include<string>


using namespace std;


enum class statusPolinomCheck
{
	start,
	error,
	waiting_plus_or_minus,
	waiting_var,
	waiting_var_or_plus_or_minus,
	waiting_symbol_deg,
	waiting_coef,
	waiting_coef_or_var,
	waiting_coef_var_plus_minus,
	waiting_coef_or_plus_minus
};

enum class nstatusCheck
{
	error,
	w_number,
	w_number_or_point,
	w_number_a_point
};

enum class await
{
	start,
	coef,
	degx,
	degy,
	degz
};


bool checkDoubValue(const string& num)
{
	nstatusCheck status = nstatusCheck::w_number;
	for (int i = 0; i <= num.size(); i++)
	{
		switch (status)
		{
		case nstatusCheck::error:
			return false;
		case nstatusCheck::w_number:
			if (num[i] == '.')
			{
				status = nstatusCheck::error;
			}
			else
			{
				status = nstatusCheck::w_number_or_point;
			}
			break;
		case nstatusCheck::w_number_or_point:
			if (num[i] == '.')
			{
				status = nstatusCheck::w_number_a_point;
			}
			break;
		case nstatusCheck::w_number_a_point:
			if (num[i] == '.')
			{
				status = nstatusCheck::error;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

bool checkPolinom(const string& str)
{
	statusPolinomCheck status = statusPolinomCheck::start;
	string tmp;
	for (int i = 0; i <= str.size(); i++)
	{
		switch (status)
		{
		case statusPolinomCheck::error:
			return false;
		case statusPolinomCheck::start:
			if (str[i] == '+' || str[i] == '-')
			{
				status = statusPolinomCheck::waiting_coef;
			}
			else if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
			{
				status = statusPolinomCheck::waiting_symbol_deg;
			}
			else if (str[i] >= 48 && str[i] <= 57)
			{
				status = statusPolinomCheck::waiting_coef_var_plus_minus;
				tmp += str[i];
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_plus_or_minus:
			if (str[i] == '+' || str[i] == '-')
			{
				status = statusPolinomCheck::waiting_coef_or_var;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_var:
			if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
			{
				status = statusPolinomCheck::waiting_symbol_deg;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_symbol_deg:
			if (str[i] == '^')
			{
				status = statusPolinomCheck::waiting_coef_or_plus_minus;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_coef:
			if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
			{
				status = statusPolinomCheck::waiting_coef_var_plus_minus;
				tmp += str[i];
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_var_or_plus_or_minus:
			if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
			{
				status = statusPolinomCheck::waiting_symbol_deg;
			}
			else if (str[i] == '+' || str[i] == '-')
			{
				status = statusPolinomCheck::waiting_coef_or_var;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_coef_or_var:
			if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
			{
				status = statusPolinomCheck::waiting_coef_var_plus_minus;
				tmp += str[i];
			}
			else if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
			{
				status = statusPolinomCheck::waiting_symbol_deg;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_coef_var_plus_minus:
			if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
			{
				status = statusPolinomCheck::waiting_coef_var_plus_minus;
				tmp += str[i];
			}
			else if ((str[i] == 'x' || str[i] == 'y' || str[i] == 'z') && checkDoubValue(tmp))
			{
				status = statusPolinomCheck::waiting_symbol_deg;
				tmp = "";
			}
			else if ((str[i] == '+' || str[i] == '-') && checkDoubValue(tmp))
			{
				status = statusPolinomCheck::waiting_coef_or_var;
				tmp = "";
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_coef_or_plus_minus:
			if (str[i] == '+' || str[i] == '-')
			{
				status = statusPolinomCheck::waiting_coef;
			}
			else if (str[i] >= 48 && str[i] <= 57)
			{
				status = statusPolinomCheck::waiting_coef;
				i--;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		}
	}
	return true;
}

Monom stringToMonom(const string& inptStr)
{
	double degx = 0;
	double degy = 0;
	double degz = 0;
	int mdegx = 1;
	int mdegy = 1;
	int mdegz = 1;
	int mcoef = 1;
	double coef = 1;
	string tmp;
	await status = await::start;

	for (int i = 0; i < inptStr.size(); i++)
	{
		if (inptStr[i] == '+' && status == await::start)
		{
				status = await::coef;
		}

		if (inptStr[i] == '-')
		{
			if (status == await::start)
			{
				mcoef = -1;
				status = await::coef;
			}
			else if (status == await::degx)
			{
				mdegx = -1;
			}
			else if (status == await::degy)
			{
				mdegy = -1;
			}
			else if (status == await::degz)
			{
				mdegz = -1;
			}
		}

		if (inptStr[i] == 'x')
		{
			status = await::degx;
		}
		if (inptStr[i] == 'y')
		{
			status = await::degy;
		}
		if (inptStr[i] == 'z')
		{
			status = await::degz;
		}

		if (inptStr[i] == '^')
		{
			continue;
		}

		if (inptStr[i] >= 48 && inptStr[i] <= 57)
		{
			while (((inptStr[i] >= 48 && inptStr[i] <= 57) || inptStr[i] == '.') && i < inptStr.size())
			{
				tmp += inptStr[i];
				i++;
			}
			if (status == await::degx)
			{
				degx = stod(tmp) * mdegx;
			}
			else if (status == await::degy)
			{
				degy = stod(tmp) * mdegy;
			}
			else if (status == await::degz)
			{
				degz = stod(tmp) * mdegz;
			}
			else if (status == await::coef || status == await::start)
			{
				coef *= stod(tmp);
			}
			tmp = "";
			i--;
		}
	}
	coef *= mcoef;
	Monom res(coef, degx, degy, degz);
	return res;
}

List<Monom> stringToMonomList(const string& inptStr)
{
	List<Monom> res;
	string tmp;
	bool flag = false;

	if (!checkPolinom(inptStr))
	{
		throw ("Error: false checkPolinom!"); 
	}

	for (int i = 0; i < inptStr.size(); i++)
	{
		if (flag && inptStr[i] != '+' && inptStr[i] != '-')
		{
			flag = false;
		}

		if (inptStr[i] == '+' || inptStr[i] == '-')
		{
			if (flag)
			{
				res.push_back(stringToMonom(tmp));
				tmp = inptStr[i];
				flag = false;
				continue;
			}
		}
		
		if (inptStr[i] >= 48 && inptStr[i] <= 57)
		{
			while (((inptStr[i] >= 48 && inptStr[i] <= 57) || inptStr[i] == '.') && i < inptStr.size())
			{
				tmp += inptStr[i];
				i++;
			}
			flag = true;
			i--;
			continue;
		}

		tmp += inptStr[i];
	}
	res.push_back(stringToMonom(tmp));
	return res;
}

class PolinomParse
{
public:
	List<Polinom> polinoms;
	string str;

	//обозначение интеграла и производной Ix и Dx
	PolinomParse(const string& inpStr)
	{
		List<Polinom> polTmp;
		string tmp;
		string polStr;
		List<char> nameList;
		bool flagTwo = false;

		for (int i = 97; i <= 122; i++)
		{
			nameList.push_back(i);
		}

		List<char>::iterator nameCounter = nameList.begin();

		for (int i = 0; i < inpStr.size(); i++)
		{

			/*if (inpStr[i] == 'I' || inpStr[i] == 'D')
			{
				if (i + 2 >= inpStr.size())
				{
					throw ("Error: wrong view of input string!");
				}
				else if((inpStr[i + 1] == 'x' || inpStr[i + 1] == 'y' || inpStr[i + 1] == 'z') && inpStr[i + 2] == '(')
				{
					tmp += inpStr[i] + inpStr[i + 1] + inpStr[i + 2];
					i += 3;
				}
			}*/

			if (inpStr[i] == 'I' || inpStr[i] == 'D')
			{
				tmp += inpStr[i];
				flagTwo = true;
				continue;
			}

			if ((inpStr[i] == 'x' || inpStr[i] == 'y' || inpStr[i] == 'z') && flagTwo)
			{
				tmp += inpStr[i];
				flagTwo = false; 
				continue;
			}

			if (inpStr[i] == '+' || inpStr[i] == '-')
			{
				if (i + 1 >= inpStr.size())
				{
					throw ("Error: wrong value of input string!");
				}
				else
				{
					if (inpStr[i + 1] == '(' || inpStr[i + 1] == 'I' || inpStr[i + 1] == 'D')
					{
						tmp += inpStr[i];
					}
					else
					{
						polStr += inpStr[i];
					}
				}
				continue;
			}

			if (inpStr[i] == '(' || inpStr[i] == '*' || inpStr[i] == '/' || inpStr[i] == ')')
			{
				tmp += inpStr[i];
				continue;
			}

			if ((inpStr[i] >= 48 && inpStr[i] <= 57) || inpStr[i] == 'x' || inpStr[i] == 'y' || inpStr[i] == 'z')
			{
				while (inpStr[i] != '*' && inpStr[i] != '/' && inpStr[i] != '(' && inpStr[i] != ')' && inpStr[i] != 'I' && inpStr[i] != 'D' && i < inpStr.size())
				{
					if (inpStr[i] == '+' || inpStr[i] == '-')
					{
						if (i + 1 >= inpStr.size())
						{
							throw ("Error: wrong string!");
						}
						else if (inpStr[i + 1] == 'I' || inpStr[i + 1] == '(' || inpStr[i + 1] == 'D')
						{
							break;
						}
					}
					polStr += inpStr[i];
					i++;
				}

				Polinom tmpPol(*nameCounter, stringToMonomList(polStr));
				polTmp.push_back(tmpPol);

				if (tmp.size() >= 1)
				{
					if (tmp.back() == ')')
					{
						if (polStr[0] == '-')
						{
							tmp += '-';
						}
						else
						{
							tmp += '+';
						}
					}
				}

				tmp += *nameCounter;
				nameCounter++;
				tmp += inpStr[i];
				polStr = "";
				continue;
			}
		}

		polinoms = polTmp;
		str = tmp;
	}

	void print()
	{
		cout << "\nParse elem:\n polinomy \n";
		polinoms.print();
		cout << "\n names of var: { " << str << " }\n";
	}
};



