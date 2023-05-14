#include<gtest.h>
#include<iostream>
#include"Polinom.h"

TEST(Monom, can_be_maked)
{
	ASSERT_NO_THROW(Monom m(3, 4, 5, 6));
}

TEST(Monom, can_be_maked_right)
{
	Monom m(3, 4, 5, 6);
	bool flag = true;
	if (m.coef != 3 || m.degX != 4 || m.degY != 5 || m.degZ != 6)
	{
		flag = false;
	}
	EXPECT_EQ(true, flag);
}

TEST(Monom, operator_plus_check)
{
	Monom m1(11, 1, 2, 3);
	Monom m2(8, 1, 2, 3);
	Monom m3(3, 1, 2, 3);
	EXPECT_EQ(m1, m2 + m3);
}

TEST(Monom, operator_mult_check)
{
	Monom m1(3, 2, 2, -9);
	Monom m2(4, 1, 2, 3);
	Monom m3(12, 3, 4, -6);
	EXPECT_EQ(m3, m1 * m2);
}

TEST(Monom, operator_div_check)
{
	Monom m1(12, 4.5, 2, -140);
	Monom m2(-3, 2, 2, 70);
	Monom m3(-4, 2.5, 0, -210);
	EXPECT_EQ(m3, m1 / m2);
}

TEST(Monom, operator_const_mult_check)
{
	Monom m1(12, 1, 2, 3);
	Monom m2(3, 1, 2, 3);
	EXPECT_EQ(m1, m2 * 4);
}

TEST(Monom, operator_const_div_check)
{
	Monom m1(3, 1, 2, 3);
	Monom m2(12, 1, 2, 3);
	EXPECT_EQ(m1, (m2 / 4));
}

TEST(Monom, operator_compare_check_1)
{
	Monom m1(12, 1, 2, 3);
	Monom m2(12, 1, 2, 3);
	EXPECT_EQ(true, m1 == m2);
}

TEST(Monom, operator_compare_check_2) // по степеням
{
	Monom m1(12, 1, 2, 3);
	Monom m2(12, 2, 2, 3);
	EXPECT_EQ(false, m1 == m2);
}

TEST(Monom, derivative_check_1)
{
	Monom m1(12, 3, 0, 0);
	Monom res(36, 2, 0, 0);
	EXPECT_EQ(res, m1.deriv('x'));
}

TEST(Monom, derivative_check_2)
{
	Monom m1(12, 3, 4, 0);
	Monom res(48, 3, 3, 0);
	EXPECT_EQ(res, m1.deriv('y'));
}

TEST(Monom, derivative_check_3)
{
	Monom m1(12, 3, 0, 2);
	Monom res(24, 3, 0, 1);
	EXPECT_EQ(res, m1.deriv('z'));
}

TEST(Monom, derivative_check)
{
	Monom m1(12, -3, 0, 0);
	Monom res(-36, -4, 0, 0);
	EXPECT_EQ(res, m1.deriv('x'));
}


TEST(Monom, integral_check_1)
{
	Monom m1(12, 3, 0, 0);
	Monom res(3, 4, 0, 0);
	EXPECT_EQ(res, m1.integral('x'));
}

TEST(Monom, integral_check_2)
{
	Monom m1(12, 3, 0, 0);
	Monom res(12, 3, 1, 0);
	EXPECT_EQ(res, m1.integral('y'));
}

TEST(Monom, integral_check_3)
{
	Monom m1(12, 3, 0, -0.5);
	Monom res(24, 3, 0, 0.5);
	EXPECT_EQ(res, m1.integral('z'));
}

TEST(Monom, pointValue_check)
{
	Monom m1(1, 2, 2, 1);
	Monom res(64, 0, 0, 0);
	EXPECT_EQ(res, m1.pointValue(2, 4, 1));
}
TEST(Polinom, can_be_maked)
{
	Monom m(1, 2, 3, 4);
	ASSERT_NO_THROW(Polinom k(m));
}
/*
TEST(Polinom, operator_compare)
{
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 3, 3, 4);
	Monom m3(2, 6, 3, 4);
	Polinom p1(m1);
	Polinom p2(m1);
	p1.addMonominPolinom(m2);
	p2.addMonominPolinom(m3);
	EXPECT_EQ(true, p1 != p2);
}
*/
TEST(Polinom, operator_plus_with_similar_terms)
{
	Monom m1(1, 2, 3, 4);
	Monom m2(3, 2, 3, 4);
	Monom m3(4, 2, 3, 4);
	Polinom p1(m1);
	Polinom p2(m2);
	Polinom res(m3);
	EXPECT_EQ(p1 + p2, res);
}

TEST(Polinom, operator_plus_without_similar_terms)
{
	Monom m1(1, 2, 3, 4);
	Monom m2(3, 5, 6, 7);
	Monom m3(4, 2, 3, 4);
	Polinom p1(m1);
	Polinom p2(m2);
	Polinom res(m1);
	res.addMonominPolinom(m2);
	EXPECT_EQ(p1 + p2, res);
}

TEST(Polinom, operator_minus_without_similar_terms)
{
	Monom m1(1, 1, 2, 3);
	Monom m2(5, 4, 5, 6);
	Monom m3(-5, 4, 5, 6);
	Monom m4(4, 2, 3, 4);
	Polinom p1(m1);
	p1.addMonominPolinom(m4);
	Polinom p2(m2);
	Polinom res(m3);
	res.addMonominPolinom(m4);
	res.addMonominPolinom(m1);
	EXPECT_EQ(p1 - p2, res);
}
TEST(Polinom, operator_mult)
{
	Monom m1(1, 1, 2, 3);
	Monom m2(5, 4, 5, 6);
	Monom m3(3, 5, 3, 2);
	Polinom p1(m1);
	p1.addMonominPolinom(m2);
	Polinom p2(m3);
	Polinom res;
	res.addMonominPolinom(m1 * m3);
	res.addMonominPolinom(m2 * m3);
	EXPECT_EQ(p1 * p2, res);
}

TEST(Polinom, operator_div)
{
	Monom m1(1, 1, 2, 3);
	Monom m2(5, 4, 5, 6);
	Monom m3(3, 4, 3, 2);
	Polinom p1(m1);
	p1.addMonominPolinom(m2);
	Polinom p2(m3);
	Polinom res;
	res.addMonominPolinom(m2 / m3);
	EXPECT_EQ(p1 / p2, res);
}

TEST(Polinom, operator_div_2)
{
	Monom m1(4, 2, 0, 0);
	Monom m2(1, 1, 0, 0);
	Polinom p1(m1);
	Polinom p2(m2);
	Polinom res;
	res.addMonominPolinom(m1 / m2);
	EXPECT_EQ(p1 / p2, res);
}

TEST(Polinom, can_take_integral)
{
	Monom m1(3, 1, 2, 3);
	Monom m2(12, 4, 5, 6);
	Polinom p1(m1);
	p1.addMonominPolinom(m2);
	Monom m3(1, 1, 3, 3);
	Monom m4(2, 4, 6, 6);
	Polinom res(m3);
	res.addMonominPolinom(m4);
	EXPECT_EQ(p1.integral('y'), res);
}
TEST(Polinom, can_derivate)
{
	Monom m1(3, 1, 2, 3);
	Monom m2(12, 4, 5, 6);
	Polinom p1(m1);
	p1.addMonominPolinom(m2);
	Monom m3(9, 1, 2, 2);
	Monom m4(72, 4, 5, 5);
	Polinom res(m3);
	res.addMonominPolinom(m4);
	EXPECT_EQ(p1.deriv('z'), res);
}

TEST(Polinom, pointValue_check)
{
	Monom m1(3, 1, 2, 3);
	Monom m2(12, 4, 5, 6);
	Polinom p1(m1);
	p1.addMonominPolinom(m2);
	double res = 6168;
	EXPECT_EQ(p1.pointValue(2, 2, 1), res);
}

TEST(Polinom, can_do_simple_similar_terms)
{
	Monom m1(3, 1, 2, 3);
	Monom m2(12, 1, 2, 3);
	Monom m3(15, 1, 2, 3);
	Polinom p1(m1);
	p1.addfortest(m2);
	p1.addfortest(m3);
	p1.doSimple();
	Polinom res(m1 + m2 + m3);
	EXPECT_EQ(p1, res);
}