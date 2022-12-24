#include <gtest/gtest.h>

#include <queue>

#include "../src/container_adaptor/queue.h"
using namespace s21;

class S21Queue_test : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(S21Queue_test, constucors_tests) {
  std::queue<int> orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  std::cout << orig.front() << std::endl;
  std::cout << orig.back() << std::endl;

  S21Queue<int> queue1;
  queue1.push(1);
  queue1.push(2);
  queue1.push(3);
  std::cout << queue1.front() << std::endl;
  std::cout << queue1.back() << std::endl;
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}