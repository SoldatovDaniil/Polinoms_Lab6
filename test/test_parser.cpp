#include<gtest.h>
#include<string>
#include"Parser.h"


//TEST(Parser, can_parse)
//{
//	ASSERT_NO_THROW(PolinomParse(std::string("4x^3")));
//}

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