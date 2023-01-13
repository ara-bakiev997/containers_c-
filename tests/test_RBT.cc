#include <gtest/gtest.h>

// #include <utility>
#include <set>

#include "../src/sorted_container/red_black_tree.h"

using namespace s21;

class Tree_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  std::set<int> set_empty;
  Tree<int> tree_null_;
};

TEST_F(Tree_test, Insert) {
  tree_null_.insert(5);
  tree_null_.insert(6);
  tree_null_.insert(7);
  tree_null_.insert(8);
  tree_null_.print2D();
}

TEST_F(Tree_test, Erase) {
  tree_null_.insert(3);
  tree_null_.insert(2);
  tree_null_.insert(5);
  tree_null_.insert(10);
  tree_null_.insert(5);
  tree_null_.insert(4);
  tree_null_.insert(7);
  tree_null_.insert(8);
  tree_null_.insert(11);

  tree_null_.print2D();
  std::cout << "____AFTER_CHANGE____" << std::endl;
  tree_null_.erase_node(3);
  tree_null_.print2D();
}

