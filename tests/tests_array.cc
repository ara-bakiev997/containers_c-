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
  S21Array<double, 5> array_1 = {1.5, 2.5, 3.5, 4, 5};
  S21Array<int, 10> array_2 = {5, 4, 3, 2, 1};
  S21Array<double, 5> array_3 = array_1;
  S21Array<double, 5> array_4 = std::move(array_1);

  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
  std::array<int, 5> test3 = std::move(test2);

};

TEST_F(S21Array_test, test_constructor_il) {
//  array_1_.fill(5.5);
//  array_empty.fill(5);
//  test_empty.fill(5);
  for (auto i = 0; i < array_4.size(); ++i) std::cout << array_4[i] << " ";
  std::cout<<"\n"<<"size = "<< array_3.size();
  std::cout<<"\n";
  for (auto i = 0; i < array_1.size(); ++i) std::cout << array_1[i] << " ";
  std::cout<<"\n"<<"size = "<< array_1.size();
  std::cout<<"\n";
//  for (auto i = 0; i <= test_empty.size(); ++i) std::cout << test_empty[i] << " ";
//  test3 = test;
    for (auto i = 0; i < test3.size(); ++i) std::cout << test3.at(i) << " ";
    std::cout<<"\n";
    for (auto i = 0; i < test2.size(); ++i) std::cout << test2.at(i) << " ";
    std::cout<<"\n"<<"size = "<< test2.size();

}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}