#include <gtest.h>
#include "Ariphmetic.h"


using namespace std;


TEST(Expressions, can_make_exp)
{
	ASSERT_NO_THROW(Expression exp("1+3+4"));
}

TEST(Expressions, can_make_exp_right)
{
	Expression exp("1+3");
	vector<pair<string, Expression::priority>> tmp;
	tmp.push_back(make_pair("1", Expression::priority::number));
	tmp.push_back(make_pair("+", Expression::priority::add_or_sub));
	tmp.push_back(make_pair("3", Expression::priority::number));
	EXPECT_EQ(tmp, exp.data);
}

TEST(Expressions, can_throw_except_when_wrong_string) 
{
	ASSERT_ANY_THROW(Expression exp("1+3+4*6/9*12%2-0+2*3"));
}

TEST(Expressions, can_check_expr)
{
	Expression exp("1+3");
	ASSERT_NO_THROW(exp.check());
}

TEST(Expressions, can_check_return_true)
{
	Expression exp("1+3");
	EXPECT_EQ(true, exp.check());
}

TEST(Expressions, can_check_return_false1)
{
	Expression exp("1+)3");
	EXPECT_EQ(false, exp.check());
}

TEST(Expressions, can_check_return_false2)
{
	Expression exp("1+3)");
	EXPECT_EQ(false, exp.check());
}

TEST(Expressions, can_check_return_false3)
{
	Expression exp("1++3");
	EXPECT_EQ(false, exp.check());
}

TEST(Expressions, can_check_return_false4)
{
	Expression exp("1+3(2+3)");
	EXPECT_EQ(false, exp.check());
}

TEST(Expressions, can_check_return_false5)
{
	Expression exp("1-");
	EXPECT_EQ(false, exp.check());
}

TEST(Expressions, can_get_polish)
{
	Expression exp("1+3");
	Calculator calc(exp);
	calc.getPolish();
	ASSERT_NO_THROW(calc.getPolish());
}

TEST(Expressions, can_get_polish_right)
{
	Expression exp("2+3*4");
	string st1 = "234*+";
	Calculator calc(exp);
	calc.getPolish();
	string st2 = calc.polishToString();
	EXPECT_EQ(st1, st2);
}

TEST(Expressions, can_throw_except_when_div_by_zero)
{
	Expression exp("1+9/0");
	Calculator calc(exp);
	calc.getPolish();
	ASSERT_ANY_THROW(calc.perform());
}

TEST(Expressions, can_calculated) 
{
	Expression exp("1+9/3+12*(0.5)");
	Calculator calc(exp);
	calc.getPolish();
	EXPECT_EQ(calc.perform(), "10.000000");
}

TEST(Expressions, can_calculated_double) 
{
	Expression exp("2.5+3.23");
	Calculator calc(exp);
	calc.getPolish();
	EXPECT_EQ(calc.perform(), "5.730000");
}

TEST(Expressions, can_create_with_polinom_list)
{
	PolinomParse parse("4x^2+5z^6/89z^-1");
	ASSERT_NO_THROW(Expression(parse.getString(), parse.getPolinomList()));
}

TEST(Expressions, can_get_polish_with_polinom)
{
	PolinomParse parse("4x^2+5z^6/89z^-1");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	ASSERT_NO_THROW(calc.getPolish());
}

TEST(Expressions, can_get_polish_with_polinom_right)
{
	PolinomParse parse("4x^2+5z^6/89z^-1");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	EXPECT_EQ("ab/", calc.polishToString());
}

TEST(Expressions, can_get_polish_with_polinom_2)
{
	PolinomParse parse("4x^3-y^6-1z^4+5x^67y^-34-9/(5y^-69.6)");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	EXPECT_EQ("ab/", calc.polishToString());
}

TEST(Expressions, can_get_polish_with_polinom_and_function)
{
	PolinomParse parse("4x^3-y^6-1z^4+5x^67y^-34-9/(5y^-69.6)-Iz(4x^3-y^6-1z^4+5x^67y^-34-9)+4x^3-y^6-1z^4+5x^67y^-34-9");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	EXPECT_EQ("ab/cIz-d+", calc.polishToString());
}

TEST(Expressions, can_get_polish_with_polinom_and_function_2)
{
	PolinomParse parse("Dx(4x^3-y^6-1z^4+5x^67y^-34-9)-Iz(4x^3-y^6-1z^4+5x^67y^-34-9)");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	EXPECT_EQ("aDxbIz-", calc.polishToString());
}

TEST(Expressions, can_get_polinom)
{
	PolinomParse parse("Dx(4x^3-y^6-1z^4+5x^67y^-34-9)-Iz(4x^3-y^6-1z^4+5x^67y^-34-9)");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	ASSERT_NO_THROW(expr.getPolinom('a'));
}

TEST(Expressions, can_get_polinom_2)
{
	PolinomParse parse("(5)-(x^2)+(-4y^3)");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	ASSERT_NO_THROW(expr.getPolinom('c'));
}


TEST(Expressions, can_calculate_with_polinom)
{
	PolinomParse parse("4x^2-(-3x^2)");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	string answer = string(1, calc.performWithPolinom().getName());
	EXPECT_EQ("b", answer);
}

TEST(Expressions, can_calculate_with_polinom_2)
{
	PolinomParse parse("4x^2*3");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	string answer = string(1, calc.performWithPolinom().getName());
	EXPECT_EQ("b", answer);
}

TEST(Expressions, can_calculate_with_polinom_3)
{
	PolinomParse parse("4x^2/x^1");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	Calculator calc = Calculator(expr);
	calc.getPolish();
	string answer = string(1, calc.performWithPolinom().getName());
	EXPECT_EQ("b", answer);
}

TEST(Expressions, can_calculate_with_polinom_4)
{
	PolinomParse parse("(10x^2+3y^2)-(4x^2)*3");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	ASSERT_NO_THROW(GetAnswerWithPolinom(expr));
}

TEST(Expressions, can_calculate_with_polinom_5)
{
	PolinomParse parse("(10x^2+3y^2)-(4x^2)*3-60x^2z^3+64x^2z^3");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	ASSERT_NO_THROW(GetAnswerWithPolinom(expr));
}

TEST(Expressions, can_calculate_with_polinom_6)
{
	PolinomParse parse("Dx(2x^2+3y^2)-(4x^2)*3");
	Expression expr = Expression(parse.getString(), parse.getPolinomList());
	ASSERT_NO_THROW(GetAnswerWithPolinom(expr));
}

TEST(Parser, string_to_monom_1)
{
	ASSERT_NO_THROW(stringToMonom("+4x^45y^-4.45"));
}

TEST(Parser, string_to_monom_2)
{
	Monom res(4, 7, 1, -4.78);
	EXPECT_EQ(res, stringToMonom("4x^7y^1z^-4.78"));
}

TEST(Parser, string_to_monom_3)
{
	Monom res(4, 7, 1, -4);
	EXPECT_EQ(res, stringToMonom("+4x^7y^1z^-4"));
}

TEST(Parser, string_to_monom_4)
{
	Monom res(-1, 0, 0, 4);
	EXPECT_EQ(res, stringToMonom("-1z^4"));
}

TEST(Parser, string_to_monom_list_1)
{
	ASSERT_NO_THROW(stringToMonomList("+4x^45y^-4.45+6.89x^-89.9-z^78-4x^7y^1z^-4-5"));
}

TEST(Parser, string_to_monom_list_2)
{
	ASSERT_NO_THROW(stringToMonomList("-4x^45+6.89x^-89.9-z^78"));
}

TEST(Parser, can_check_string_like_polinom_1)
{
	string tmp = "-4x^3+6.78z^3.45-45";
	EXPECT_EQ(true, checkPolinom(tmp));
}

TEST(Parser, can_check_string_like_polinom_2)
{
	string tmp = "-4x^3++6.78z^3.45-45";
	EXPECT_EQ(false, checkPolinom(tmp));
}

TEST(Parser, can_check_string_like_polinom_3)
{
	string tmp = "-4x^3-z^3.45-45x^3+6.767";
	EXPECT_EQ(true, checkPolinom(tmp));
}

TEST(Parser, can_check_string_like_polinom_4)
{
	string tmp = "-4x^3+6.7.8z^3.45-45";
	EXPECT_EQ(false, checkPolinom(tmp));
}

TEST(Parser, can_check_string_like_polinom_5)
{
	EXPECT_EQ(true, checkPolinom("+4x^45y^-4.45+6.89x^-89.9+z^78-4x^7y^1z^-4-5"));
}

TEST(Parser, can_check_string_like_polinom_6)
{
	EXPECT_EQ(true, checkPolinom("69.7x^-34+y^0.23"));
}

TEST(Parser, can_parse_1)
{
	ASSERT_NO_THROW(PolinomParse(string("4x^3/(5y^-69.6)")));
}

TEST(Parser, can_parse_2)
{
	ASSERT_NO_THROW(PolinomParse(string("-4x^3/(-5y^-69.6)*Ix(5y^-69.6)")));
}

TEST(Parser, can_parse_3)
{
	ASSERT_NO_THROW(PolinomParse(string("4x^3-y^6-1z^4+5x^67y^-34-9/(5y^-69.6)-Dy(69.7x^-34+y^0.23)-67.7")));
}

