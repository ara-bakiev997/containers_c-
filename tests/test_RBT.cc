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
  tree_null_.insert(0);
  tree_null_.insert(2);
  tree_null_.insert(1);
  tree_null_.insert(3);
  tree_null_.insert(4);
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

TEST_F(Tree_test, rotate) {
  tree_null_.insert(10);
  tree_null_.insert(20);
  tree_null_.insert(5);
  tree_null_.insert(7);
  tree_null_.insert(6);
  tree_null_.insert(15);
  tree_null_.insert(16);
  tree_null_.insert(18);
  tree_null_.insert(17);
  tree_null_.insert(30);
  tree_null_.insert(35);
  tree_null_.insert(32);
  tree_null_.insert(33);
  tree_null_.insert(45);
  tree_null_.insert(50);
  tree_null_.insert(55);
  tree_null_.insert(53);
  tree_null_.insert(60);
  tree_null_.insert(65);
  tree_null_.insert(70);
  tree_null_.insert(70);

  tree_null_.print2D();
}

TEST_F(Tree_test, Sasha_tests) {
  tree_null_.insert(50);
  tree_null_.insert(40);
  tree_null_.insert(30);
  tree_null_.insert(20);
  tree_null_.insert(60);
  tree_null_.insert(70);
  tree_null_.insert(80);
  tree_null_.insert(75);
  tree_null_.insert(81);
  tree_null_.insert(82);
  tree_null_.insert(83);
  tree_null_.insert(84);
  tree_null_.insert(85);
  tree_null_.insert(86);
  tree_null_.insert(6);
  tree_null_.insert(4);
  tree_null_.insert(1);
  tree_null_.insert(5);
  tree_null_.insert(-4);
  tree_null_.insert(32);
  tree_null_.insert(-8);
  tree_null_.insert(-6);
  tree_null_.insert(16);

  tree_null_.print2D();
}
