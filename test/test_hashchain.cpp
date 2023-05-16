#include<gtest.h>
#include<iostream>
#include"HashChain.h"
#include <string>
TEST(hash_chains, can_insert)
{
	hash_table<std::string, int> b;
	ASSERT_NO_THROW(b.insert({ "ab",3 }));
}

TEST(hash_chains, can_find_element)
{
	hash_table<std::string, int> b;
	b.insert({ "ab",3 });
	b.insert({ "aba",5 });
	b.insert({ "abc",4 });
	auto it = b.find("abc");
	EXPECT_EQ(4, (*it).second);
}

TEST(hash_chains, can_insert_correct)
{
	hash_table<std::string, int> b;
	b.insert({ "ab",3 });
	b.insert({ "aba",5 });
	auto it = b.find("ab");
	EXPECT_EQ(3, (*it).second);
}

TEST(hash_chains, can_erase)
{
	hash_table<std::string, int> b;
	b.insert({ "ab",3 });
	b.insert({ "aba",5 });
	ASSERT_NO_THROW(b.erase("aba"));
}

TEST(hash_chains, can_give_any_element_in_list)
{
	hash_table<std::string, int> b;
	b.insert({ "2222",3 });// hash2222=hash22
	b.insert({ "22",5 });
	b.insert({ "aba",67 });
	auto it = b.find("2222");
	EXPECT_EQ(3, (*it).second);
	auto it1 = b.find("22");
	EXPECT_EQ(5, (*it1).second);
}
/*
hash_table<string, int> b;
b.insert({ "ab",3 });
b.insert({ "abc",5 });
b.insert({ "aba",6 });
b.insert({ "abcd",1 });
b.erase("abcd");
auto it = b.find("aba");
std::cout << (*it).second;
*/