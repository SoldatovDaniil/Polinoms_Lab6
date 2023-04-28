#include <gtest.h>
#include <iostream>
#include "Unordered.h"

TEST(Unordered_table, can_push)
{
	unordered_table<int, int> a({ 1,1 });
	ASSERT_NO_THROW(a.push(2, 2));
}
