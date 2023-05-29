#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "Parser.h"


using namespace std;


class Expression
{
public:
	enum class priority
	{
		number,
		brecket,
		div_or_mul,
		add_or_sub,
		function,
		polinom
	};

	enum class statusCheck //add
	{
		start,
		erorr,
		w_operator,
		w_number,
		w_operator_or_close_bracket, 
		w_number_or_open_bracket,
		w_number_or_polinom,
		w_number_or_polinom_or_function,
		w_open_bracket,
		w_number_or_open_bracket_or_function_or_polinom
	};

	enum class nstatusCheck
	{
		erorr,
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
			case nstatusCheck::erorr:
				return false;
			case nstatusCheck::w_number:
				if (num[i] == '.')
				{
					status = nstatusCheck::erorr;
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
					status = nstatusCheck::erorr;
				}
				break;
			default:
				break;
			}
		}
		return true;
	}

	vector<pair<string, priority>> data;
	List<Polinom> polinomData;

	Expression() = default;

	Expression(const string& str, const List<Polinom>& polList)
	{
		polinomData = polList;
		bool flag = false;
		for (int i = 0; i < str.size(); i++)
		{
			pair<string, priority> tmp;
			tmp.first = "";
			if (str[i] == '\0')
			{
				break;
			}
			if (str[i] == '+' || str[i] == '-')
			{
				tmp.first = str[i];
				tmp.second = priority::add_or_sub;
				data.push_back(tmp);
				flag = false;
			}
			else if (str[i] == '*' || str[i] == '/')
			{
				tmp.first = str[i];
				tmp.second = priority::div_or_mul;
				data.push_back(tmp);
				flag = false;
			}
			else if (str[i] == '(' || str[i] == ')')
			{
				tmp.first = str[i];
				tmp.second = priority::brecket;
				data.push_back(tmp);
				flag = false;
			}
			else if (((str[i] >= 48) && (str[i] <= 57)) || str[i] == '.')
			{
				tmp.second = priority::number;
				flag = false;
				do
				{
					tmp.first += str[i];
					i++;
				} while ((((str[i] >= 48) && (str[i] <= 57)) || str[i] == '.') && i < str.size());
				if (checkDoubValue(tmp.first) == true)
				{
					data.push_back(tmp);
					i--;
				}
				else
				{
					throw ("Error: wrong real number!");
				}
			}
			else if (str[i] == 'I' || str[i] == 'D')
			{
				tmp.first = str[i];
				tmp.second = priority::function;
				data.push_back(tmp);
				flag = true;
			}
			else if ((str[i] == 'x' || str[i] == 'y' || str[i] == 'z') && flag)
			{
				data[data.size() - 1].first += str[i];
			}
			else if (str[i] >= 97 && str[i] <= 122)
			{
				tmp.second = priority::polinom;
				tmp.first = str[i];
				data.push_back(tmp);
			}
			else
			{
				throw ("Error: unidentified symbol!");
			}
		}
	}

	Expression(const string& str)
	{
		bool flag = false;
		for (int i = 0; i < str.size(); i++)
		{
			pair<string, priority> tmp;
			tmp.first = "";
			if (str[i] == '+' || str[i] == '-')
			{
				tmp.first = str[i];
				tmp.second = priority::add_or_sub;
				data.push_back(tmp);
				flag = false;
			}
			else if (str[i] == '*' || str[i] == '/')
			{
				tmp.first = str[i];
				tmp.second = priority::div_or_mul;
				data.push_back(tmp);
				flag = false;
			}
			else if (str[i] == '(' || str[i] == ')')
			{
				tmp.first = str[i];
				tmp.second = priority::brecket;
				data.push_back(tmp);
				flag = false;
			}
			else if (((str[i] >= 48) && (str[i] <= 57)) || str[i] == '.')
			{
				tmp.second = priority::number;
				flag = false;
				do
				{
					tmp.first += str[i];
					i++;
				} while ((((str[i] >= 48) && (str[i] <= 57)) || str[i] == '.') && i < str.size());
				if (checkDoubValue(tmp.first) == true)
				{
					data.push_back(tmp);
					i--;
				}
				else
				{
					throw ("Error: wrong real number!");
				}
			}
			else if (str[i] == 'I' || str[i] == 'D')
			{
				tmp.first = str[i];
				tmp.second = priority::function;
				data.push_back(tmp);
				flag = true;
			}
			else if ((str[i] == 'x' || str[i] == 'y' || str[i] == 'z') && flag)
			{
				data[-1].first += str[i];
			}
			else if (str[i] >= 97 && str[i] <= 122)
			{
				tmp.second = priority::polinom;
				tmp.first = str[i];
				data.push_back(tmp);
			}
			else
			{
				throw ("Error: unidentified symbol!");
			}
		}
	}

	Expression& operator=(const Expression& expr)
	{
		if (this == &expr)
		{
			return *this;
		}

		if (!expr.polinomData.empty())
		{
			polinomData = expr.polinomData;
		}
		
		data = expr.data;
		return *this;
	}

	Polinom* getPolinom(char n)
	{
		List<Polinom>::iterator iter;
		for (List<Polinom>::iterator it = polinomData.begin(); it != polinomData.end(); it++)
		{
			iter = it;
			if ((*it).getName() == n)
			{
				return &(*it);
			}
		}
		iter++;
		if ((*iter).getName() == n)
		{
			return &(*iter);
		}
		return &(*iter);
	}

	bool check()
	{
		statusCheck status = statusCheck::start;
		int breck_count = 0;
		pair<string, priority> lastElem;
		for (int i = 0; i < data.size(); ++i)
		{
			lastElem = data[i];
			switch (status)
			{
			case Expression::statusCheck::start:
				if (data[i].first == ")" || data[i].second == priority::div_or_mul || data[i].second == priority::add_or_sub)
				{
					status = statusCheck::erorr;
				}
				else if (data[i].second == priority::number)
				{
					status = statusCheck::w_operator;
				}
				else if (data[i].first == "(")
				{
					status = statusCheck::w_number_or_polinom_or_function;
					breck_count++;
				}
				else if (data[i].second == priority::polinom)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else if (data[i].second == priority::function)
				{
					status = statusCheck::w_open_bracket;
				}
				break;
			case Expression::statusCheck::w_number:
				if (data[i].second == priority::number)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_operator:
				if (data[i].second == priority::div_or_mul || data[i].second == priority::add_or_sub)
				{
					status = statusCheck::w_number_or_open_bracket_or_function_or_polinom;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_number_or_open_bracket:
				if (data[i].second == priority::number)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else if (data[i].first == "(")
				{
					status = statusCheck::w_number_or_polinom_or_function;
					breck_count++;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_operator_or_close_bracket:
				if (data[i].first == ")")
				{
					status = statusCheck::w_operator;
					breck_count--;
				}
				else if (data[i].second == priority::add_or_sub || data[i].second == priority::div_or_mul)
				{
					status = statusCheck::w_number_or_open_bracket_or_function_or_polinom;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_number_or_polinom:
				if (data[i].second == priority::number || data[i].second == priority::polinom)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_number_or_polinom_or_function:
				if (data[i].second == priority::number || data[i].second == priority::polinom)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else if (data[i].second == priority::function)
				{
					status = statusCheck::w_open_bracket;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_number_or_open_bracket_or_function_or_polinom:
				if (data[i].second == priority::number || data[i].second == priority::polinom)
				{
					status = statusCheck::w_operator_or_close_bracket;
				}
				else if (data[i].second == priority::function)
				{
					status = statusCheck::w_open_bracket;
				}
				else if (data[i].first == "(")
				{
					status = statusCheck::w_number_or_polinom_or_function;
					breck_count++;
				}
				else
				{
					status = statusCheck::erorr;
				}
				break;
			case Expression::statusCheck::w_open_bracket:
				if (data[i].first != "(")
				{
					status = statusCheck::erorr;
				}
				else
				{
					status = statusCheck::w_number_or_polinom_or_function;
					breck_count++;
				}
				break;
			case Expression::statusCheck::erorr:
				return false;
			default:
				break;
			}
		}
		if (status == statusCheck::erorr)
		{
			return false;
		}
		if (lastElem.second == priority::div_or_mul || lastElem.second == priority::add_or_sub || lastElem.first == "(")
		{
			return false;
		}

		if (breck_count == 0)
		{
			return true;
		}
		
		
		return false;
	}

	int size()
	{
		return data.size();
	}

	List<Polinom> getPolinomList()
	{
		return polinomData;
	}

	friend ostream& operator<<(ostream& out, const Expression& expres)
	{
		cout << "\nExpression: \n";
		for (int i = 0; i < expres.data.size(); i++)
		{
			pair<string, priority> tmp = expres.data[i];
			out << tmp.first;
		}
		cout << "\n Polinoms: ";
		List<Polinom>::iterator iter;
		for (auto it = expres.polinomData.begin(); it != expres.polinomData.end(); it++)
		{
			iter = it;
			cout << *it << '\n';
		}
		cout << *(++iter);
		return out;
	}

};


class Calculator : private Expression
{
private:
	Expression express;
	vector<pair<string, priority>> polish;
public:
	Calculator(const Expression& expr)
	{
		express = expr;
		if (express.check() == false)
		{
			throw ("Error: wrong expression");
		}
	}

	vector<pair<string, priority>> getPolish()
	{
		stack<pair<string, priority>> tmpStack;
		for (int i = 0; i < express.data.size(); i++)
		{
			if (express.data[i].second == priority::number || express.data[i].second == priority::polinom)
			{
				polish.push_back(express.data[i]);
			}
			else if (express.data[i].second == priority::function)
			{
				tmpStack.push(express.data[i]);
			}
			else if (express.data[i].first == "(")
			{
				tmpStack.push(express.data[i]);
			}
			else if (express.data[i].first == ")")
			{
				while (tmpStack.top().first != "(")
				{
					polish.push_back(tmpStack.top());
					tmpStack.pop();
				}
				tmpStack.pop();
			}
			else if (express.data[i].second == priority::add_or_sub || express.data[i].second == priority::div_or_mul)
			{
				while (!tmpStack.empty() && (((express.data[i].second == priority::add_or_sub && (tmpStack.top().second == priority::add_or_sub || tmpStack.top().second == priority::div_or_mul)) || (express.data[i].second == priority::div_or_mul && tmpStack.top().second == priority::div_or_mul)) || tmpStack.top().second == priority::function))
				{
					polish.push_back(tmpStack.top());
					tmpStack.pop();
				}
				tmpStack.push(express.data[i]);
			}
		}

		while (!tmpStack.empty())
		{
			polish.push_back(tmpStack.top());
			tmpStack.pop();
		}

		return polish;
	}

	string perform()
	{
		stack<pair<string, priority>> tmpStack;
		for (int i = 0; i < polish.size(); i++)
		{
			if (polish[i].second == priority::number)
			{
				tmpStack.push(polish[i]);
			}
			else if (polish[i].second == priority::add_or_sub || polish[i].second == priority::div_or_mul)
			{
				double rOper = stod(tmpStack.top().first);
				tmpStack.pop();
				double lOper = stod(tmpStack.top().first);
				tmpStack.pop();

				if (polish[i].first == "+")
				{

					tmpStack.push(make_pair(to_string(lOper + rOper), priority::add_or_sub));
				}
				else if (polish[i].first == "-")
				{
	
					tmpStack.push(make_pair(to_string(lOper - rOper), priority::add_or_sub));
				}
				else if (polish[i].first == "*")
				{

					tmpStack.push(make_pair(to_string(lOper * rOper), priority::add_or_sub));
				}
				else if (polish[i].first == "/")
				{
					if (rOper == 0)
					{
						throw ("Error: division by zero!!!");
					}
					tmpStack.push(make_pair(to_string(lOper / rOper), priority::add_or_sub));
				}
			}
		}
		return tmpStack.top().first;
	}

	Polinom performWithPolinom() //rbt + out
	{
		stack<pair<string, priority>> tmpStack;
		for (int i = 0; i < polish.size(); i++)
		{
			if (polish[i].second == priority::polinom)
			{
				tmpStack.push(polish[i]);
			}
			else if (polish[i].second == priority::add_or_sub || polish[i].second == priority::div_or_mul)
			{
				Polinom* rOper = express.getPolinom(tmpStack.top().first[0]);
				tmpStack.pop();
				Polinom* lOper = express.getPolinom(tmpStack.top().first[0]);
				tmpStack.pop();
				
				if (polish[i].first == "+")
				{
					*rOper = *rOper + *lOper;
					tmpStack.push(make_pair(string(1, (*rOper).getName()), priority::polinom));
				}
				else if (polish[i].first == "-")
				{
					*rOper = *lOper - *rOper;
					tmpStack.push(make_pair(string(1, (*rOper).getName()), priority::polinom));
				}
				else if (polish[i].first == "*")
				{
					*rOper = *rOper * *lOper;
					tmpStack.push(make_pair(string(1, (*rOper).getName()), priority::polinom));
				}
				else if (polish[i].first == "/")
				{
					*rOper = *lOper / *rOper;
					tmpStack.push(make_pair(string(1, (*rOper).getName()), priority::polinom));
				}
			}
			else if (polish[i].second == priority::function)
			{
				string arg = tmpStack.top().first;
				tmpStack.pop();
				Polinom* argPolinom = express.getPolinom(arg[0]);

				if (polish[i].first[0] == 'I')
				{
					*argPolinom = (*argPolinom).integral(polish[i].first[1]);
					tmpStack.push(make_pair(arg, priority::polinom));
				}
				else if (polish[i].first[0] == 'D')
				{
					*argPolinom = (*argPolinom).deriv(polish[i].first[1]);
					tmpStack.push(make_pair(arg, priority::polinom));
				}
			}
		}
		return *express.getPolinom(tmpStack.top().first[0]);
	}

	string polishToString()
	{
		string tmp = "";
		for (int i = 0; i < polish.size(); i++)
			tmp += polish[i].first;
		return tmp;
	}

	void printPolish() {
		cout << "\nPolish of this expression: \n";
		for (int i = 0; i < polish.size(); i++)
		{
			cout << polish[i].first;
		}
	}
};

string GetAnswer(const Expression& expr)
{
	Calculator calc(expr);
	calc.getPolish();
	return(calc.perform());
}

void GetAnswerWithPolinom(Expression& expr)
{
	Calculator calc(expr);
	calc.getPolish();
	cout << calc.performWithPolinom();
}

Expression GetExpr()
{
	string str;
	cout << "Input your expression: ";
	cin >> str;
	Expression expr(str);
	return expr;
}





