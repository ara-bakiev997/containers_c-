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

#include "../src/sorted_container/set_container/s21_multiset.h"

using namespace s21;
using std::cout;
using std::endl;

class S21Multiset_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Multiset<int, int> multiset_empty;
  S21Multiset<int, int> multiset{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  S21Multiset<int, int> multiset3{{10, 50}, {8, 60}, {6, 70}};
  S21Multiset<int, std::string> map_s;
  std::map<int, int> std_multiset_empty;
  std::map<int, int> std_multiset{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  std::map<int, int> std_multiset3{{10, 50}, {8, 60}, {6, 70}};
  std::map<int, std::string> std_map_s;
};

TEST_F(S21Multiset_test, construct_il) {
  S21Multiset<int, int, std::less_equal<int>> multiset3{{10, 50}, {8, 60}, {6, 70}, {6, 70}};
  std::multiset<int, std::less_equal<int>> std_multiset = {{10}, {8}, {6}, {6}};

  for (auto i : multiset3) {std::cout << i.first << ' ';} std::cout << std::endl;
  for (auto i : std_multiset) {std::cout << i << ' ';} std::cout << std::endl;

}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}