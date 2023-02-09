//
// Created by Qyburn Bongo on 2/7/23.
//

#include <gtest/gtest.h>

//#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
//#include <random>
//#include <string>
//#include <vector>

#include "../src/sorted_container/set_container/s21_set.h"

using namespace s21;
using std::cout;
using std::endl;

class S21Set_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Set<int> set_empty;
  S21Set<int> set{1, 0, 4, 7, -5};
  S21Set<int> set3{10, 8, 6};
  S21Set<std::string> set_s;
  std::set<int> std_set_empty;
  std::set<int> std_set{1, 0, 4, 7, -5};
  std::set<int> std_set3{10, 8, 6};
  std::set<std::string> std_set_s;
};

TEST_F(S21Set_test, construct_il) {
  EXPECT_EQ(set.size(), std_set.size());
  auto it = set.begin();
  for (const auto &std_data : std_set) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, construct_copy) {
  S21Set<int> set4(set3);
  std::set<int> std_set4(std_set3);
  EXPECT_EQ(set4.size(), std_set4.size());
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, construct_move) {
  S21Set<int> set4(std::move(set3));
  std::set<int> std_set4(std::move(std_set3));
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, operator_copy) {
  set_empty = set3;
  std_set_empty = std_set3;
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, operator_move) {
  set_empty = std::move(set3);
  std_set_empty = std::move(std_set3);
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, swap) {
  S21Set<int> set5{15, 12, 20};
  std::set<int> std_set5{15, 12, 20};
  set3.swap(set5);
  std_set3.swap(std_set5);
  auto it = set3.begin();
  for (const auto &std_data : std_set3) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }

  auto it2 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(it2->first, std_data);
    ++it2;
  }

  set_empty.swap(set5);
  std_set_empty.swap(std_set5);
  auto it3 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(it3->first, std_data);
    ++it3;
  }

  auto it4 = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it4->first, std_data);
    ++it4;
  }
}

TEST_F(S21Set_test, size) {
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  EXPECT_EQ(set.size(), std_set.size());
}

//TEST_F(S21Set_test, max_size) { EXPECT_EQ(set.max_size(), std_set.max_size()); }

TEST_F(S21Set_test, clear) {
  EXPECT_EQ(set.size(), std_set.size());
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  set.clear();
  std_set.clear();
  set_empty.clear();
  std_set_empty.clear();
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  EXPECT_EQ(set.size(), std_set.size());
}

TEST_F(S21Set_test, it_begin) {
  auto it = set.begin();
  auto std_it = std_set.begin();
  EXPECT_EQ(it->first, *std_it);
}

TEST_F(S21Set_test, it_end) {
  auto it = set.end();
  auto std_it = std_set.end();
  --it;
  --std_it;
  EXPECT_EQ(it->first, *std_it);
}

TEST_F(S21Set_test, empty) {
  EXPECT_TRUE(set_empty.empty());
  EXPECT_TRUE(std_set_empty.empty());
}

//TEST_F(S21Set_test, insert_value_type) {
//  auto pr1 = set_s.insert(std::pair(1, "25"));
//  auto pr2 = set_s.insert(std::pair(2, "55"));
//  auto std_pr1 = std_set_s.insert(std::pair(1, "25"));
//  auto std_pr2 = std_set_s.insert(std::pair(2, "55"));
//  EXPECT_EQ((*pr1.first).first, (*std_pr1.first).first);
//  EXPECT_EQ((*pr2.first).first, (*std_pr2.first).first);
//  EXPECT_EQ((*pr1.first).second, (*std_pr1.first).second);
//  EXPECT_EQ((*pr2.first).second, (*std_pr2.first).second);
//}
//
//TEST_F(S21Set_test, insert_key_value) {
//  auto pr1 = set_s.insert(1, "25");
//  auto pr2 = set_s.insert(2, "55");
//  auto std_pr1 = std_set_s.insert(std::pair(1, "25"));
//  auto std_pr2 = std_set_s.insert(std::pair(2, "55"));
//  EXPECT_EQ((*pr1.first).first, (*std_pr1.first).first);
//  EXPECT_EQ((*pr2.first).first, (*std_pr2.first).first);
//  EXPECT_EQ((*pr1.first).second, (*std_pr1.first).second);
//  EXPECT_EQ((*pr2.first).second, (*std_pr2.first).second);
//}
//
//
TEST_F(S21Set_test, erase) {
//  set_s.insert("1");
//  set_s.insert("2");
//  std_set_s.insert("1");
//  std_set_s.insert("2");
  set3.erase((set3.begin()));
  std_set3.erase((std_set3.begin()));
//  set_s.erase((set_s.begin()));
//  std_set_s.erase((std_set_s.begin()));

  auto it = set3.begin();
  for (const auto &std_data : std_set3) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }

//  auto it2 = set_s.begin();
//  for (const auto &std_data : std_set_s) {
//    EXPECT_EQ(it2->first, std_data);
//    ++it2;
//  }

}

//TEST_F(S21Set_test, emplace) {
//  auto pr3 = set_s.emplace(1, "a");
//  auto std_pr3 = std_set_s.emplace(1, "a");
//  EXPECT_EQ((*pr3[0].first).first, (*std_pr3.first).first);
//  EXPECT_EQ((*pr3[0].first).second, (*std_pr3.first).second);
//}
//
//TEST_F(S21Set_test, merge) {
//  S21Set<int, std::string> ma_{{1, "apple"}, {5, "pear"}, {10, "banana"}};
//  S21Set<int, std::string> mb_{
//      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
//  S21Set<int, std::string> u_;
//  std::set<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
//  std::set<int, std::string> mb{
//      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
//  std::set<int, std::string> std_u;
//  u_.merge(ma_);
//  std_u.merge(ma);
//  EXPECT_EQ(ma_.size(), ma.size());
//  u_.merge(mb_);
//  std_u.merge(mb);
//  EXPECT_EQ(mb_.size(), mb.size());
//  EXPECT_EQ(mb_.at(5), mb.at(5));
//
//  for (auto const &kv : u_)
//    EXPECT_EQ(u_.at(kv.first), std_u.at(kv.first));
//}
//
//TEST_F(S21Set_test, contains) {
//  S21Set<int, char> example = {{1, 'a'}, {2, 'b'}};
//  std::set<int, char> std_example = {{1, 'a'}, {2, 'b'}};
//  EXPECT_TRUE(example.contains(2));
//  EXPECT_FALSE(example.contains(5));
//}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

