#include <gtest.h>
#include <iostream>
#include <vector>
#include "HashOpen.h"


TEST(HashOpenAdress, table_hash_check)
{
	HashTableOpenAdress<int> testTable;
	ASSERT_NO_THROW(testTable.hash(12));
}

TEST(HashOpenAdress, table_can_push)
{
	HashTableOpenAdress<int> testTable;
	testTable.push(1, 121);
	testTable.push(2, 46);
	testTable.push(3, 168);
	testTable.push(4, 93);
	testTable.push(5, 17);
	testTable.push(6, 139);
	SUCCEED();
}

TEST(HashOpenAdress, table_can_erase)
{
	HashTableOpenAdress<int> testTable;
	testTable.push(1, 121);
	testTable.push(2, 46);
	testTable.erase(1);
	testTable.push(3, 168);
	testTable.push(4, 93);
	testTable.push(5, 17);
	testTable.push(6, 139);
	testTable.erase(4);
	SUCCEED();
}

TEST(HashOpenAdress, table_can_push_with_collision)
{
	HashTableOpenAdress<int> testTable;
	testTable.push(1, 121);
	testTable.push(2, 46);
	testTable.push(3, 168);
	testTable.push(4, 93);
	testTable.push(5, 17);
	testTable.push(6, 139);
	testTable.push(25, 17);
	testTable.push(169, 139);
	SUCCEED();
}

TEST(HashOpenAdress, table_can_push_with_collision_2)
{
	HashTableOpenAdress<int> testTable;
	testTable.push(1, 121);
	testTable.push(2, 46);
	testTable.push(3, 168);
	testTable.push(4, 93);
	testTable.push(5, 17);
	testTable.push(6, 139);
	testTable.push(25, 17);
	testTable.push(169, 139);
	testTable.erase(169);
	SUCCEED();
}