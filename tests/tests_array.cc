#include <gtest/gtest.h>

// #include <utility>
#include <array>

#include "../src/sequence/s21_array.h"

using namespace s21;

class S21Array_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Array<int, 0> array_empty;
  S21Array<int, 5> array = {1, 2, 3, 4, 5};
  S21Array<int, 5> array_2 = {5, 4, 3, 2, 1};
  S21Array<int, 5> array_3 = array;
  S21Array<int, 5> array_4 = std::move(array);

  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
  std::array<int, 5> test3 = test;
  std::array<int, 5> test4 = std::move(test);

};

TEST_F(S21Array_test, test_constructor_def) {
  EXPECT_EQ(array_empty.size(), test_empty.size());
  for (auto i = 0; i < array_empty.size(); ++i)
    EXPECT_EQ(array_empty.at(i), test_empty.at(i));
  std::cout<<"test_constructor_def = ok"<<"\n";
}

TEST_F(S21Array_test, test_constructor_il) {
  EXPECT_EQ(array_empty.size(), test_empty.size());
  for (auto i = 0; i < array_empty.size(); ++i)
    EXPECT_EQ(array.at(i), test.at(i));
  std::cout<<"test_constructor_il = ok"<<"\n";
}

TEST_F(S21Array_test, test_constructor_cpy) {
  EXPECT_EQ(array_3.size(), test3.size());
  for (auto i = 0; i < array_3.size(); ++i)
    EXPECT_EQ(array_3.at(i), test3.at(i));
  std::cout<<"test_constructor_cpy = ok"<<"\n";
}

TEST_F(S21Array_test, test_constructor_move) {
  EXPECT_EQ(array_4.size(), test4.size());
  for (auto i = 0; i < array_4.size(); ++i)
    EXPECT_EQ(array_4.at(i), test4.at(i));
  std::cout<<"test_constructor_move = ok"<<"\n";
}

TEST_F(S21Array_test, test_op_move) {
  S21Array<int, 5> arr= {1, 2, 3, 4, 5};
  array_2 = std::move(arr);
  test2 = std::move(test);
  EXPECT_EQ(array_2.size(), test2.size());
  for (auto i = 0; i < array_2.size(); ++i)
    EXPECT_EQ(array_2.at(i), test2.at(i));
  std::cout<<"test_op_move = ok"<<"\n";
}

//TEST_F(S21Array_test, test_constructor_) {
////  array_1.fill(5.5);
////  array_empty.fill(5);
////  test_empty.fill(5);
//S21Array<int, 5> arr= {1, 2, 3, 4, 5};
//array_2 = std::move(arr);
//test2 = std::move(test);
//
//  for (auto i = 0; i < array_2.size(); ++i) std::cout << array_2[i] << " ";
//  std::cout<<"\n"<<"size = "<< array_2.size();
//  std::cout<<"\n";
//  for (auto i = 0; i < array_2.size(); ++i) std::cout << array_2[i] << " ";
//  std::cout<<"\n"<<"data = "<< &(*array.end());
//  std::cout<<"\n";
////  for (auto i = 0; i <= test_empty.size(); ++i) std::cout << test_empty[i] << " ";
////  test3 = test;
//    for (auto i = 0; i < test2.size(); ++i) std::cout << test2.at(i) << " ";
//    std::cout<<"\n";
//    for (auto i = 0; i < test.size(); ++i) std::cout << test.at(i) << " ";
//    std::cout<<"\n"<<"beg = "<< test.begin();
//
//}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}