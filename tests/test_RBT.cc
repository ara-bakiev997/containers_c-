#include <gtest/gtest.h>

// #include <utility>
#include <set>

#include "../src/sorted_container/red_black_tree.h"

using namespace s21;

class Tree_test : public ::testing::Test {
protected:
  std::set<int> set_empty;
  Tree<int> tree_null_;
  Node<int> node_null;
//  Node<int> node_data(1);

};


TEST_F(Tree_test, GetRoot) {
  EXPECT_EQ(tree_null_.GetRoot(), nullptr);
//  EXPECT_EQ(tree_null_.GetRoot()->data_, nullptr);
//  EXPECT_EQ(tree_null_.GetRoot()->parent_, nullptr);
//  EXPECT_EQ(tree_null_.GetRoot()->left_, nullptr);
//  EXPECT_EQ(tree_null_.GetRoot()->right_, nullptr);
//  EXPECT_EQ(tree_null_.GetRoot()->color_, BLACK);
}

TEST_F(Tree_test, Insert) {
  tree_null_.Insert(5);
//  EXPECT_EQ(tree_null_.GetRoot(), nullptr);
  //  EXPECT_EQ(tree_null_.GetRoot()->data_, nullptr);
  //  EXPECT_EQ(tree_null_.GetRoot()->parent_, nullptr);
  //  EXPECT_EQ(tree_null_.GetRoot()->left_, nullptr);
  //  EXPECT_EQ(tree_null_.GetRoot()->right_, nullptr);
  //  EXPECT_EQ(tree_null_.GetRoot()->color_, BLACK);
}

