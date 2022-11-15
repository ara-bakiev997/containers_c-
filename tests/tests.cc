#include <gtest/gtest.h>

// #include <utility>
#include <list>

#include "../src/sequence/s21_list.h"

using namespace s21;

class S21List_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21List<int> list_empty;
  //  S21List<int> list_1_ = {1, 2, 3, 4, 5};
  //  S21List<int> list_2_ = S21List<int>(10);
  std::list<int> test_empty;
  std::list<int> test = {1, 2, 3, 4, 5};
  std::list<int> test2 = {5, 4, 3, 2, 1};
};

TEST_F(S21List_test, experiment_orig) {
  list_empty.push_back(10);

  //    for (auto i : test) {
  //      std::cout << i << ' ';
  //    }
  //    std::cout << std::endl;
  //
  //    std::cout << "size = " << test.size() << std::endl;
  //
  //    for (auto i : test2) {
  //      std::cout << i << ' ';
  //    }
  //    std::cout << std::endl;
  //    test2.sort();
  //    for (auto i : test2) {
  //      std::cout << i << ' ';
  //    }
  //    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}