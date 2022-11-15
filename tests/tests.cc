#include <gtest/gtest.h>

// #include <utility>
#include <array>

#include "../src/sequence/s21_array.h"

using namespace s21;

class S21Array_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Array<int, 0> array_empty;
  S21Array<int, 5> array_1_ = {1, 2, 3, 4, 5};
//  S21Array<int, 5> array_2_ = S21Array<int, 5>;
  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
};

TEST_F(S21Array_test, test_constructor_il) {
  for (auto i = 0; i < array_1_.size(); ++i) std::cout << array_1_[i] << " ";



}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}