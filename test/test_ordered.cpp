#include <gtest.h>
#include <iostream>
#include "Ordered.h"


TEST(Ordered, can_push_to_empty_table)
{
	OrderedTable<char, int> testtable;
	ASSERT_NO_THROW(testtable.push('1', 1));
}

TEST(Ordered, can_push_to_no_empty_table)
{
	OrderedTable<char, int> testtable;
	testtable.push('1', 1);
	testtable.push('2', 2);
	ASSERT_NO_THROW(testtable.push('3', 3));
}

TEST(Ordered, can_erase_table)
{
	OrderedTable<char, int> testtable;
	testtable.push('1', 1);
	testtable.push('2', 2);
	ASSERT_NO_THROW(testtable.erase('2'););
}

TEST(Ordered, can_print_table)
{
	OrderedTable<char, int> testtable;
	testtable.push('1', 1);
	testtable.push('2', 2);
	testtable.push('3', 3);
	testtable.push('4', 4);
	testtable.erase('2');
	ASSERT_NO_THROW(testtable.print());
}