#include <gtest/gtest.h>

// #include <utility>
#include <set>

#include "../src/sorted_container/red_black_tree.h"

using namespace s21;

class Tree_test : public ::testing::Test {
protected:
  void SetUp() override {
    //        tree_int.Insert(6);
    //        tree_int.Insert(20);
    //        tree_int.Insert(4);
    //        tree_int.Insert(1);
    //        tree_int.Insert(5);
    //        tree_int.Insert(-4);
    //        tree_int.Insert(80);
    //        tree_int.Insert(80);
    //        tree_int.Insert(32);
    //        tree_int.Insert(-8);
    //        tree_int.Insert(16);
    //        tree_int.Insert(38);
    //        tree_int.Insert(-19);
    //        tree_int.Insert(63);
    //        tree_int.Insert(18);
    //        tree_int.Insert(35);
  }
  std::set<int> set_empty;
  Tree<int> tree_null_;
  Tree<int> tree_int;
  Tree<int> tree_left_round;
  //  RBT<int>* RBT_null = new RBT<int>;
  //  Node<int> node_data(1);
};

// TEST_F(Tree_test, Node_insert) {
//   RBT_null->Insert(5);
////  std::cout << node_null.data_ << std::endl;
//  RBT_null->Insert(3);
////  node_null->Insert(7);
//  RBT_null->RBTPrint();
//}

TEST_F(Tree_test, GetRoot) { EXPECT_EQ(tree_null_.GetRoot(), nullptr); }

TEST_F(Tree_test, Insert) {
  tree_null_.Insert(6);
  EXPECT_EQ(tree_null_.GetRoot()->data_, 6);
  tree_null_.Insert(20);
  EXPECT_EQ(tree_null_.GetRoot()->right_->data_, 20);
  tree_null_.Insert(4);
  EXPECT_EQ(tree_null_.GetRoot()->left_->data_, 4);
  tree_null_.Insert(1);
  tree_null_.Insert(5);
  EXPECT_EQ(tree_null_.GetRoot()->left_->data_, 4);
  tree_null_.Insert(-4);
  tree_null_.Insert(80);
  tree_null_.Insert(80);
  tree_null_.Insert(32);
  tree_null_.Insert(-8);
  tree_null_.Insert(16);
  //  tree_null_.TreePrint();
  //  tree_null_.WalkInWidth();
  //  tree_null_.Remove(-8);
  //  tree_null_.Remove(-4);
  //  tree_null_.Remove(20);
  //    tree_null_.Remove(6);
  tree_null_.print2D();
}

TEST_F(Tree_test, FindMin) {
  tree_int.print2D();
  std::cout << tree_int.FindMin(reinterpret_cast<RBT<int> *&>(tree_int))->data_
            << std::endl;
}

TEST_F(Tree_test, Remove) {
  //  tree_int.Remove(6);
  tree_int.print2D();
  //  tree_int.TreePrint();
}

TEST_F(Tree_test, GetBrother) {
  tree_int.print2D();
  std::cout << tree_int.GetBrother(tree_int.GetRoot()->left_->right_)->data_
            << std::endl;
}

// TEST_F(Tree_test, IsRoot) {
//   tree_int.print2D();
//   std::cout << tree_int.IsRoot(tree_int.GetRoot()) << std::endl;
// }

TEST_F(Tree_test, tree_left_round) {
  tree_left_round.Insert(50);

//  tree_left_round.Insert(60);
//  tree_left_round.Insert(55);

//    tree_left_round.Insert(40);
//    tree_left_round.Insert(45);


  tree_left_round.Insert(40);
  tree_left_round.Insert(30);
  tree_left_round.Insert(20);
  tree_left_round.Insert(60);
  tree_left_round.Insert(70);
  tree_left_round.Insert(80);
  tree_left_round.Insert(75);
  tree_left_round.Insert(81);
  tree_left_round.Insert(82);
  tree_left_round.Insert(83);
  tree_left_round.Insert(84);
  tree_left_round.Insert(85);
  tree_left_round.Insert(86);
  tree_left_round.Insert(6);
  tree_left_round.Insert(4);
  tree_left_round.Insert(1);
  tree_left_round.Insert(5);
  tree_left_round.Insert(-4);
  tree_left_round.Insert(32);
  tree_left_round.Insert(-8);
  tree_left_round.Insert(-6);
//  tree_left_round.Insert(16);
  tree_left_round.print2D();
}

TEST_F(Tree_test, segfolt) {
  tree_left_round.Insert(6);
  tree_left_round.Insert(20);
  tree_left_round.Insert(4);
  tree_left_round.Insert(1);
  tree_left_round.Insert(5);
  tree_left_round.Insert(-4);
  tree_left_round.Insert(80);
  tree_left_round.Insert(80);
  tree_left_round.Insert(32);
  tree_left_round.Insert(-8);
//  tree_left_round.Insert(16);
//  tree_left_round.Insert(38);
//  tree_left_round.Insert(-19);
//  tree_left_round.Insert(63);
//  tree_left_round.Insert(18);
//  tree_left_round.Insert(35);
  tree_left_round.print2D();
}

//          GetParent(balance_RBT)->parent_ = temp->parent_; // A.p = B.p
//          temp->parent_ = GetParent(balance_RBT); // B.p = A
//          temp->left_ = GetParent(balance_RBT)->right_; // B.l = A.r
//          GetParent(balance_RBT)->right_ = temp;