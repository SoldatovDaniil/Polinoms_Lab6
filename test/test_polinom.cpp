#include<gtest.h>
#include<iostream>
#include"Polinom.h"

TEST(Monom, can_be_maked)
{
	ASSERT_NO_THROW(Monom m(3,4,5,6));
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

TEST(Monom, operator_compare_check_2)
{
	Monom m1(12, 1, 2, 3);
	Monom m2(-12, 1, 2, 3);
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
	EXPECT_EQ(res, m1.pointValue(-2,4,1));
}

