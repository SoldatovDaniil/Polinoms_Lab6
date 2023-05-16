#include "Rbt.h"
#include <gtest.h>
#include <vector>

TEST(RBT, can_be_make_and_insert)
{
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	rbtTree<int> tree;
	for (auto num : nums)
		ASSERT_NO_THROW(tree.insert(num, num));
}

TEST(RBT, can_be_make_and_insert_can_search_elem)
{
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	rbtTree<int> tree;
	for (auto num : nums)
		tree.insert(num, num);
	EXPECT_EQ(30, tree.search(30)->key);
}

TEST(RBT, can_be_make_and_insert_can_remove_elem)
{
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	rbtTree<int> tree;
	for (auto num : nums)
		tree.insert(num ,num);
	ASSERT_NO_THROW(tree.remove(100));
}