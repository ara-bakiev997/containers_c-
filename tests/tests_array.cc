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
  S21Array<double, 5> array_1_ = {1.5, 2.5, 3.5, 4, 5};
  S21Array<int, 10> array_2_ = {5, 4, 3, 2, 1};
  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
};

TEST_F(S21Array_test, test_constructor_il) {
  array_1_.fill(5.5);
//  array_empty.fill(5);
//  test_empty.fill(5);
  for (auto i = 0; i <= array_empty.size(); ++i) std::cout << array_empty[i] << " ";
  std::cout<<"\n";
//  for (auto i = 0; i <= test_empty.size(); ++i) std::cout << test_empty[i] << " ";
//    for (auto i = 0; i <= test_empty.size(); ++i) std::cout << test_empty.at(i) << " ";

}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}