#include<gtest.h>
#include<string>
#include"Parser.h"

TEST(Parse, string_to_monom_1)
{
	ASSERT_NO_THROW(stringToMonom("+4x^45y^-4.45"));
}

TEST(Parse, string_to_monom_2)
{
	Monom res(4, 7, 1, -4.78);
	EXPECT_EQ(res, stringToMonom("4x^7y^1z^-4.78"));
}

TEST(Parse, string_to_monom_3)
{
	Monom res(4, 7, 1, -4);
	EXPECT_EQ(res, stringToMonom("+4x^7y^1z^-4"));
}

TEST(Parse, string_to_monom_4)
{
	Monom res(-4, 7, 1, -4);
	EXPECT_EQ(res, stringToMonom("-4x^7y^1z^-4"));
}

TEST(Parse, string_to_monom_list)
{
	ASSERT_NO_THROW(stringToMonomList("+4x^45y^-4.45+6.89x^-89.9+z^78-4x^7y^1z^-4-5"));
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
	checkPolinom("69.7x^-34+y^0.23");
	EXPECT_EQ(true, checkPolinom("69.7x^-34+y^0.23"));
}

TEST(Parser, can_parse_1)
{
	ASSERT_NO_THROW(PolinomParse(std::string("4x^3/(5y^-69.6)")));
}

TEST(Parser, can_parse_2)
{
	ASSERT_NO_THROW(PolinomParse(std::string("-4x^3/(5y^-69.6)")));
}

TEST(Parser, can_parse_3)
{
	ASSERT_NO_THROW(PolinomParse(std::string("4x^3/(5y^-69.6)*(69.7x^-34+y^0.23)-67.7")));
}