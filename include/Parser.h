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
	waiting_coef_var_plus_minus
};


enum class nstatusCheck
{
	error,
	w_number,
	w_number_or_point,
	w_number_a_point
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
			else if (str[i] >= 49 && str[i] <= 57)
			{
				status = statusPolinomCheck::waiting_var_or_plus_or_minus;
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
				status = statusPolinomCheck::waiting_coef;
			}
			else
			{
				status = statusPolinomCheck::error;
			}
			break;
		case statusPolinomCheck::waiting_coef:
			if ((str[i] >= 49 && str[i] <= 57) || str[i] == '.')
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
			if ((str[i] >= 49 && str[i] <= 57) || str[i] == '.')
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
			if ((str[i] >= 49 && str[i] <= 57) || str[i] == '.')
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
		}
	}
	return true;
}


class PolinomParse
{
public:
	List<Polinom> polinoms;
	string str;


	PolinomParse(const string& inpStr)
	{
		List<Polinom> polTmp;
		string tmp;
		string polStr;
		List<char> nameList;
		for (int i = 97; i <= 122; i++)
		{
			nameList.push_back(i);
		}
		List<char>::iterator nameCounter = nameList.begin();

		//обозначение интеграла и производной(в строке для expr можно хранить один чар типа I(x) и d (x))?
		for (int i = 0; i < inpStr.size(); i++)
		{
			if (inpStr[i] == '(')
			{
				tmp += inpStr[i];
			}
			else
			{
				while ((inpStr[i] != '/' && inpStr[i] != '*' && inpStr[i] != ')' && inpStr[i] != '(') && i < inpStr.size())
				{
					polStr += inpStr[i];
					i++;
				}
				if (checkPolinom(polStr))
				{
					polTmp.push_back(Polinom(*nameCounter, polStr));
					nameCounter++;
					tmp += *nameCounter;
				}
				else
				{
					throw ("Error: wrong polinom!");
				}
				polStr = "";
				if (inpStr[i] == '/' || inpStr[i] == '*' || inpStr[i] == ')' || inpStr[i] == '(' || inpStr[i] == '+')
				{
					tmp += inpStr[i];
				}
			}
		}
		polinoms = polTmp;
		str = tmp;
	}
};



