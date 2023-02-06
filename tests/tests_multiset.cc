//
// Created by Qyburn Bongo on 1/24/23.
//

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "../src/sorted_container/set_container/multiset.h"

using namespace s21;
using std::cout;
using std::endl;

class S21Multiset_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Multiset<int, int> map_empty;
  S21Multiset<int, int> map{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  S21Multiset<int, int> map3{{10, 50}, {8, 60}, {6, 70}};
  S21Multiset<int, std::string> map_s;
  std::map<int, int> std_map_empty;
  std::map<int, int> std_map{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  std::map<int, int> std_map3{{10, 50}, {8, 60}, {6, 70}};
  std::map<int, std::string> std_map_s;
};

TEST_F(S21Multiset_test, construct_il) {
  for (const auto &pair : std_map3) {
    EXPECT_EQ(map3.at(pair.first), std_map3.at(pair.first));
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}