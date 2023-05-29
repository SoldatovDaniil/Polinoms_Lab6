#include<gtest.h>
#include "Avl.h"
#include "Polinom.h"
TEST(AVL_tree, can_insert) {
	AVL_tree<string, int> v;
	ASSERT_NO_THROW(v.insert("aba", 1));

}

TEST(AVL_tree, can_get_value) {
	AVL_tree<string, int> v;
	v.insert("ab", 13);
	EXPECT_EQ(13, v["ab"]);
}

TEST(AVL_tree, can_erase_) {
	AVL_tree<string, int> v;
	v.insert("ac", 42);
	ASSERT_NO_THROW(v.erase("ac"));
}

TEST(AVL_tree, many_inserts_and_erases) {
	AVL_tree<int, int> v;
	vector<int> nods({ 5,2,55,1,6,15,30 });
	for (int i = 0; i < nods.size(); i++) {
		v.insert(nods[i], i);
	}

	for (int i = 0; i < nods.size(); i++) {
		EXPECT_EQ(i, v[nods[i]]);
	}
}

TEST(AVL_tree, balance1) {
	vector<int> nods({ 5,2,55,1,6,15,30 });
	AVL_tree<int, int> v;
	v.insert(nods[0], 3);
	v.insert(nods[1], 4);
	v.insert(nods[2], 15);
	EXPECT_EQ(5, v.root->key);
}

TEST(AVL_tree, balance2) {
	vector<int> nods({ 10, 1, 3, 17, 19, 11, 55, 30 });
	AVL_tree<int, int> v;
	v.insert(nods[0], 1);
	v.insert(nods[1], 1);
	v.insert(nods[2], 1);
	v.insert(nods[3], 1);
	v.insert(nods[4], 1);
	v.insert(nods[5], 1);
	v.insert(nods[6], 1);
	v.insert(nods[7], 1);
	EXPECT_EQ(10, v.root->key);
	EXPECT_EQ(17, v.root->right->key);
	EXPECT_EQ(3, v.root->left->key);
}

TEST(AVL_tree, correct_erases) {
	vector<int> nods({ 9, 1, 2, 15, 18, 10, 30, 27 });
	AVL_tree<int, int> v;
	for (int i = 0; i < nods.size(); i++) {
		v.insert(nods[i], i);
	}

	for (int i = 0; i < nods.size(); i++) {
		v.erase(nods[i]);
	}

	EXPECT_EQ(nullptr, v.root);
}