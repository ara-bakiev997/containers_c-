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
  std::multiset<int> std_multiset_empty;
  std::multiset<int> std_multiset{{1}, {0}, {4}, {7}, {-5}};
  std::multiset<int> std_multiset3{{10}, {8}, {6}};
  std::multiset<int> std_multiset_s;
};

TEST_F(S21Multiset_test, construct_il) {
//  S21Multiset<int, int, std::less<int>> multiset3{{10, 50}, {8, 60}, {6, 70}, {6, 70}};
//  std::multiset<int, std::less<int>> std_multiset = {{10}, {8}, {6}, {6}};
////  std::cout << multiset3.size() << std::endl;
  for (auto i : multiset) {std::cout << i.first << ' ';} std::cout << std::endl;
  for (auto i : std_multiset) {std::cout << i << ' ';} std::cout << std::endl;
}

TEST_F(S21Multiset_test, constructor_initialazer) {
  EXPECT_EQ(multiset.size(), multiset.size());
  EXPECT_EQ(multiset.size(), multiset.size());
  EXPECT_EQ(multiset.size(), multiset.size());

}


int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}