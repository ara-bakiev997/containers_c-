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

  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
  std::array<int, 5> test3 = test;



};

TEST_F(S21Array_test, test_constructor_def) {
  EXPECT_EQ(array_empty.size(), test_empty.size());
  std::cout<<"test_constructor_def = ok"<<"\n";
}

TEST_F(S21Array_test, test_constructor_il) {
//    S21Array<int, 3> array_4 = {1, 2, 3, 4, 5};
//    std::array<int, 4> test_4 = {1, 2, 3, 4, 5};
  EXPECT_EQ(array.size(), test.size());
  for (auto i = 0; i < array.size(); ++i)
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
  S21Array<int, 5> array_4 = std::move(array);
  std::array<int, 5> test4 = std::move(test);
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

TEST_F(S21Array_test, test_size) {
    EXPECT_EQ(array.size(), test.size());
    EXPECT_EQ(array_empty.size(), test_empty.size());
    std::cout<<"test_size = ok"<<"\n";
}

TEST_F(S21Array_test, test_empty) {
    EXPECT_EQ(array.empty(), test.empty());
    EXPECT_EQ(array_empty.empty(), test_empty.empty());
    EXPECT_NE(array.empty(), test_empty.empty());
    std::cout<<"test_empty = ok"<<"\n";
}

TEST_F(S21Array_test, test_max_size) {
    EXPECT_EQ(array.max_size(), test.max_size());
    EXPECT_EQ(array_empty.max_size(), test_empty.max_size());
    std::cout<<"test_max_size = ok"<<"\n";
}
TEST_F(S21Array_test, test_swap) {
    array.swap(array_2);
    test.swap(test2);
    EXPECT_EQ(array.size(), test.size());
    for (auto i = 0; i < array.size(); ++i)
        EXPECT_EQ(array.at(i), test.at(i));
    std::cout<<"test_swap = ok"<<"\n";
}

TEST_F(S21Array_test, test_fill) {
   array.fill(-1);
   test.fill(-1);
    for (auto i = 0; i < array.size(); ++i)
        EXPECT_EQ(array.at(i), test.at(i));
    array_empty.fill(5);
    test_empty.fill(5);
    EXPECT_NO_THROW(array_empty.fill(5));
    EXPECT_NO_THROW(test_empty.fill(5));
    std::cout<<"test_fill = ok"<<"\n";
}
// fix me: test_empty.front() sega?
TEST_F(S21Array_test, test_front) {
    EXPECT_EQ(array.front(), test.front());
//    test_empty.front();
//    EXPECT_EQ(array_empty.front(), test_empty.front());
    std::cout<<"test_front = ok"<<"\n";
}

TEST_F(S21Array_test, test_back) {
    EXPECT_EQ(array.back(), test.back());
//    EXPECT_EQ(array_empty.back(), test_empty.back());
    std::cout<<"test_back = ok"<<"\n";
}

TEST_F(S21Array_test, test_data) {
    EXPECT_EQ(array.data(), &array.front());
    EXPECT_EQ(test.data(), &test.front());
    std::cout<<"test_data = ok"<<"\n";
}

TEST_F(S21Array_test, test_it_begin) {
    EXPECT_EQ(*array.begin(), *test.begin());
    std::cout<<"test_it_begin = ok"<<"\n";
}
//fix me: test_empty.front() sega?
TEST_F(S21Array_test, test_it_end) {
    EXPECT_EQ(*(array.end() - 1), *(test.end() - 1));
    std::cout<<"test_it_end = ok"<<"\n";
}

TEST_F(S21Array_test, test_op_brck) {
    EXPECT_EQ(array[3], test[3]);
    EXPECT_NO_THROW(array[10]);
    EXPECT_NO_THROW(test[10]);
//    EXPECT_EQ(array_empty[0], test_empty[0]); // sega
    std::cout<<"test_op_brck = ok"<<"\n";
}

TEST_F(S21Array_test, test_at) {
    EXPECT_EQ(array.at(3), test.at(3));
    EXPECT_ANY_THROW(array.at(10));
    EXPECT_ANY_THROW(test.at(10));
    EXPECT_ANY_THROW(array_empty.at(0));
    EXPECT_ANY_THROW(test_empty.at(0));
    std::cout<<"test_at = ok"<<"\n";
}

//TEST_F(S21Array_test, test) {
//    S21Array<int, 5> arr7= {1, 2, 3, 4, 5};
//    std::cout<<"test = ok"<<arr7[5]<<"\n";
//}


int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}