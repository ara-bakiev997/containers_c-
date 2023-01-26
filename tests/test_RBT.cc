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

// test 1
TEST_F(Tree_test, Insert) {
  tree_null_.insert_node(0);
  tree_null_.insert_node(2);
  tree_null_.insert_node(1);
  tree_null_.insert_node(3);
  tree_null_.insert_node(4);
  tree_null_.insert_node(6);
  tree_null_.insert_node(5);
  tree_null_.insert_node(8);

// збс проходит, так же как и в визуализации
  tree_null_.erase_node(2); // 2.1.2
  tree_null_.erase_node(4);
  tree_null_.erase_node(0);
  tree_null_.erase_node(1);
  tree_null_.erase_node(8);
  tree_null_.erase_node(6);
  tree_null_.erase_node(5);
  tree_null_.erase_node(3);

  tree_null_.print2D();
}
// test 2
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
  tree_null_.insert_node(75);

  // збс проходит, так же как и в визуализации
  tree_null_.erase_node(50);
  tree_null_.erase_node(60);
  tree_null_.erase_node(32);
  tree_null_.erase_node(53);
  tree_null_.erase_node(75);
  tree_null_.erase_node(70);
  tree_null_.erase_node(55);
  tree_null_.erase_node(35);
  tree_null_.erase_node(33);
  tree_null_.erase_node(17);
  tree_null_.erase_node(20);
  tree_null_.erase_node(18);
  tree_null_.erase_node(65);
  tree_null_.erase_node(15);
  tree_null_.erase_node(5);
  tree_null_.erase_node(6);
  tree_null_.erase_node(7);
  tree_null_.erase_node(10);
  tree_null_.erase_node(45);
  tree_null_.erase_node(30);
  tree_null_.erase_node(16);

  tree_null_.print2D();
}
// test 3
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

  // збс проходит, так же как и в визуализации
  tree_null_.erase_node(40);
  tree_null_.erase_node(30);
  tree_null_.erase_node(20);
  tree_null_.erase_node(50);
  tree_null_.erase_node(75);
  tree_null_.erase_node(60);
  tree_null_.erase_node(4);
  tree_null_.erase_node(80);
  tree_null_.erase_node(83);
  tree_null_.erase_node(81);
  tree_null_.erase_node(85);
  tree_null_.erase_node(84);
  tree_null_.erase_node(82);
  tree_null_.erase_node(6);
  tree_null_.erase_node(86);
  tree_null_.erase_node(70);
  tree_null_.erase_node(1);
  tree_null_.erase_node(5);

  tree_null_.print2D();
}
// test 4
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

  tree_null_.erase_node(40);
  tree_null_.erase_node(30);
  tree_null_.erase_node(50);
  tree_null_.erase_node(60);
  tree_null_.erase_node(80);
  tree_null_.erase_node(83);
  tree_null_.erase_node(70);
  tree_null_.erase_node(81); // смотри зайдет ли в gcov
  tree_null_.erase_node(85);
  tree_null_.erase_node(5);
  tree_null_.erase_node(84);
  tree_null_.erase_node(6);
  tree_null_.erase_node(1);
  tree_null_.erase_node(4);
  tree_null_.erase_node(75);
  tree_null_.erase_node(86);
  tree_null_.erase_node(82);
  tree_null_.erase_node(20);

  tree_null_.print2D();
}
// test 5
TEST_F(Tree_test, EraseARA) {
  tree_null_.insert_node(6);
  tree_null_.insert_node(20);
  tree_null_.insert_node(4);
  tree_null_.insert_node(1);
  tree_null_.insert_node(5);
  tree_null_.insert_node(-4);
  tree_null_.insert_node(80);
  tree_null_.insert_node(32);
  tree_null_.insert_node(16);
  tree_null_.insert_node(38);
  tree_null_.insert_node(63);
  tree_null_.insert_node(18);
  tree_null_.insert_node(35);

  tree_null_.erase_node(5);
  tree_null_.erase_node(80);
  tree_null_.erase_node(1);
  tree_null_.erase_node(4);
  tree_null_.erase_node(18);
  tree_null_.erase_node(38);
  tree_null_.erase_node(35);
  tree_null_.erase_node(20);
  tree_null_.erase_node(-4);
  tree_null_.erase_node(63);
  tree_null_.erase_node(6);
  tree_null_.erase_node(16);
  tree_null_.erase_node(32);
  tree_null_.print2D();
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}