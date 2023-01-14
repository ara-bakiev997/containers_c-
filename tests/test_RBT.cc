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
  tree_null_.insert_node(0);
  tree_null_.insert_node(2);
  tree_null_.insert_node(1);
  tree_null_.insert_node(3);
  tree_null_.insert_node(4);
  tree_null_.print2D();
}

TEST_F(Tree_test, rotate) {
  tree_null_.insert_node(10);
  tree_null_.insert_node(20);
  tree_null_.insert_node(5);
  tree_null_.insert_node(7);
  tree_null_.insert_node(6);
  tree_null_.insert_node(15);
  tree_null_.insert_node(16);
  tree_null_.insert_node(18);
  tree_null_.insert_node(17);
  tree_null_.insert_node(30);
  tree_null_.insert_node(35);
  tree_null_.insert_node(32);
  tree_null_.insert_node(33);
  tree_null_.insert_node(45);
  tree_null_.insert_node(50);
  tree_null_.insert_node(55);
  tree_null_.insert_node(53);
  tree_null_.insert_node(60);
  tree_null_.insert_node(65);
  tree_null_.insert_node(70);
  tree_null_.insert_node(70);

  tree_null_.print2D();
}

TEST_F(Tree_test, Sasha_tests) {
  tree_null_.insert_node(50);
  tree_null_.insert_node(40);
  tree_null_.insert_node(30);
  tree_null_.insert_node(20);
  tree_null_.insert_node(60);
  tree_null_.insert_node(70);
  tree_null_.insert_node(80);
  tree_null_.insert_node(75);
  tree_null_.insert_node(81);
  tree_null_.insert_node(82);
  tree_null_.insert_node(83);
  tree_null_.insert_node(84);
  tree_null_.insert_node(85);
  tree_null_.insert_node(86);
  tree_null_.insert_node(6);
  tree_null_.insert_node(4);
  tree_null_.insert_node(1);
  tree_null_.insert_node(5);
//  tree_null_.insert_node(-4);
//  tree_null_.insert_node(32);
//  tree_null_.insert_node(-8);
//  tree_null_.insert_node(-6);
//  tree_null_.insert_node(16);

  tree_null_.print2D();
}

TEST_F(Tree_test, Erase) {
  tree_null_.insert_node(50);
  tree_null_.insert_node(40);
  tree_null_.insert_node(30);
  tree_null_.insert_node(20);
  tree_null_.insert_node(60);
  tree_null_.insert_node(70);
  tree_null_.insert_node(80);
  tree_null_.insert_node(75);
  tree_null_.insert_node(81);
  tree_null_.insert_node(82);
  tree_null_.insert_node(83);
  tree_null_.insert_node(84);
  tree_null_.insert_node(85);
  tree_null_.insert_node(86);
  tree_null_.insert_node(6);
  tree_null_.insert_node(4);
  tree_null_.insert_node(1);
  tree_null_.insert_node(5);
//  tree_null_.print2D();
  std::cout << "____AFTER_CHANGE____" << std::endl;
  tree_null_.erase_node(86);
  tree_null_.erase_node(85);
  tree_null_.erase_node(83); // следи за цветом
  tree_null_.erase_node(81);
  tree_null_.erase_node(80);
  tree_null_.erase_node(60);
  tree_null_.erase_node(20);


  tree_null_.print2D();

}