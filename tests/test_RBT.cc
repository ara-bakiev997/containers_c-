#include <gtest/gtest.h>

// #include <utility>
#include <set>

#include "../src/sorted_container/red_black_tree.h"

using namespace s21;

class Tree_test : public ::testing::Test {
protected:
  std::set<int> set_empty;
  Tree<int> tree_null_;
//  RBT<int>* RBT_null = new RBT<int>;
//  Node<int> node_data(1);

};

//TEST_F(Tree_test, Node_insert) {
//  RBT_null->Insert(5);
////  std::cout << node_null.data_ << std::endl;
//  RBT_null->Insert(3);
////  node_null->Insert(7);
//  RBT_null->RBTPrint();
//}

TEST_F(Tree_test, GetRoot) {
  EXPECT_EQ(tree_null_.GetRoot(), nullptr);

}

TEST_F(Tree_test, Insert) {
  tree_null_.Insert(5);
  EXPECT_EQ(tree_null_.GetRoot()->data_, 5);
  tree_null_.Insert(7);
  EXPECT_EQ(tree_null_.GetRoot()->right_->data_, 7);
  tree_null_.Insert(4);
  EXPECT_EQ(tree_null_.GetRoot()->left_->data_, 4);
}

