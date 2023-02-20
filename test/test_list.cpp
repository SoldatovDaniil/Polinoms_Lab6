#include<gtest.h>
#include"List.h"


TEST(List_Iterator, iter_can_been_maked)
{
	List<int> l1(5);
	ASSERT_NO_THROW(List<int>::iterator iter(l1.root));
}

TEST(List_Iterator, iter_operator_star_work)
{
	List<int> l1(5);
	l1.push_front(1);
	List<int>::iterator iter(l1.root);
	EXPECT_EQ(1, *iter);
}

TEST(List_Iterator, iter_can_find_begin)
{
	List<int> l1(5);
	l1.push_front(1);
	List<int>::iterator iter = l1.begin();
	EXPECT_EQ(1, *iter);
}

TEST(List_Iterator, iter_can_find_end)
{
	List<int> l1(5);
	l1.push_back(2);
	List<int>::iterator iter = l1.end();
	EXPECT_EQ(2, *iter);
}

TEST(List_Iterator, iter_can_postfix_inc)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	List<int>::iterator it = l1.begin();
	++it;
	EXPECT_EQ(2, *(it++));
	EXPECT_EQ(3, *it);
}

TEST(List_Iterator, iter_can_prefix_inc)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	List<int>::iterator it = l1.begin();
	++it;
	EXPECT_EQ(2, *it);
}

TEST(List_Iterator, iter_can_step)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	List<int>::iterator it = l1.begin();
	it = it + 2;
	EXPECT_EQ(3, *it);
}

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> l1(5));
}

TEST(List, can_push_front_right)
{
	List<int> l1(3);
	l1.push_front(2);
	List<int>::iterator iter = l1.begin();
	EXPECT_EQ(2, *iter);
}

TEST(List, can_push_back_right)
{
	List<int> l1(3);
	l1.push_back(2);
	List<int>::iterator iter = l1.end();
	EXPECT_EQ(2, *iter);
}

TEST(List, can_pop_front_right)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	l1.pop_front();
	List<int>::iterator iter = l1.begin();
	EXPECT_EQ(2, *iter);
}

TEST(List, can_pop_back_right)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	l1.pop_back();
	List<int>::iterator iter = l1.end();
	EXPECT_EQ(2, *iter);
}

TEST(List, can_get_size_right)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	EXPECT_EQ(3, l1.getSize());
}

TEST(List, can_been_maked_how_copy)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	List<int> l2(l1);
	for (List<int>::iterator it1 = l1.begin(), it2 = l2.begin(); it1 != l1.end(), it2 != l2.end(); it1++, it2++)
	{
		EXPECT_EQ(*it1, *it2);
	}
}

TEST(List, can_erase_after_right)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	List<int>::iterator iter = l1.begin();
	l1.erase_after(iter);
	iter++;
	EXPECT_EQ(1, *(iter));
}

TEST(List, can_insert_after_right)
{
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	List<int>::iterator iter = l1.end();
	l1.insert_after(iter, 100);
	iter++;
	EXPECT_EQ(100, *(iter));
}

TEST(List, can_check_empty)
{
	List<int> l1;
	EXPECT_EQ(true, l1.empty());
}

TEST(List, can_clear)
{
	List<int> l1(4);
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	l1.clear();
	EXPECT_EQ(true, l1.empty());
}

TEST(List, can_check_true)
{
	List<int> l1;
	l1.push_front(5);
	l1.push_front(4);
	l1.push_front(3);
	l1.push_front(2);
	l1.push_front(1);
	EXPECT_EQ(true, l1.check());
}

TEST(List, can_check_false)
{
	List<int> l1;
	l1.push_front(5);
	l1.push_front(4);
	l1.push_front(3);
	l1.push_front(2);
	l1.push_front(1);
	l1.push_front(6);
	EXPECT_EQ(false, l1.check());
}

TEST(List, can_merge_sort)
{
	List<int> l1;
	l1.push_front(65);
	l1.push_front(4);
	l1.push_front(12);
	l1.push_front(1);
	l1.push_front(45);
	l1.push_front(0);
	l1.mergeSort();
	EXPECT_EQ(true, l1.check());
}

TEST(List, can_find_middle_1)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(7);
	l1.push_back(8);
	l1.push_back(9);
	EXPECT_EQ(5, (l1.findMiddle()->elem));
}

TEST(List, can_find_middle_0)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(7);
	l1.push_back(8);
	EXPECT_EQ(4, (l1.findMiddle()->elem));
}

TEST(List, can_delete_middle_elements)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(7);
	l1.push_back(8);
	l1.delMiddle();
	EXPECT_EQ(6, ((l1.findMiddle()->next)->elem));
}