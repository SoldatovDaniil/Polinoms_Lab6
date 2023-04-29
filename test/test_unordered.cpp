#include <gtest.h>
#include <iostream>
#include "Unordered.h"

TEST(Unordered_table, can_push)
{
	unordered_table<int, int> a( 1,1);
	ASSERT_NO_THROW(a.push(2, 2));
}
TEST(Unordered_table, can_push_correct)
{
	unordered_table<int, int> a(1, 1);
	a.push(7, 5);
	EXPECT_EQ(a[7],5);
}

TEST(Unordered_table, can_find_element1)
{
	unordered_table<int, int> a(1, 1);
	a.push(2, 2);
	a.push(3, 3);
	EXPECT_EQ(a.find(2),true);
}
TEST(Unordered_table, can_find_element2)
{
	unordered_table<int, int> a(1, 1);
	a.push(2, 2);
	a.push(3, 3);
	EXPECT_EQ(a.find(4), false);
}
TEST(Unordered_table, can_give_element_with_key)
{
	unordered_table<int, int> a(1, 2);
	a.push(3, 4);
	a.push(5, 6);
	a.push(7, 8);
	EXPECT_EQ(a[1],2);
	EXPECT_EQ(a[3], 4);
	EXPECT_EQ(a[5], 6);
	EXPECT_EQ(a[7], 8);
}

TEST(Unordered_table, can_give_element_with_key_if_not_only_elem)
{
	unordered_table<int, int> a(1, 2);
	a.push(3, 4);
	a.push(3, 6);
	a.push(3, 5);
	EXPECT_EQ(a[3], 5);
}

TEST(Unordered_table, can_erase_element_with_key)
{
	unordered_table<int, int> a(1, 2);
	a.push(3, 4);
	a.push(5, 6);
	a.push(7, 8);
	ASSERT_NO_THROW(a.erase(5));
}