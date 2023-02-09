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
//  S21Set<int> set_empty;
  S21Set<int> set{1, 0, 4, 7, -5};
//  S21Set<int> set3{10, 8, 6};
//  S21Set<std::string> set_s;
  std::set<int> std_set_empty;
  std::set<int> std_set{1, 0, 4, 7, -5};
  std::set<int> std_set3{10, 8, 6};
  std::set<std::string> std_set_s;
};

TEST_F(S21Set_test, construct_il) {

  S21Set<int> set{1, 0, 4, 7, -5};
    EXPECT_EQ(set.size(), std_set.size());
//    cout << *std_set.begin() << " ";
//    cout << (*set.begin()).first << " ";
  for (const auto &std_data : std_set) {
    cout << std_data << " ";
  }
    cout << endl;
  for (auto i = set.begin(); i != set.end();++i) {
    cout << (*i).first << " ";
  }

  for (auto i = std_set.begin(); i != std_set.end();++i) {
    cout << *i << " ";
  }
  cout << endl;
//  for (auto i = (--set.end()); ;--i) {
//    cout << *i << " ";
//    if (i == set.begin()) break;
//  }
//  cout << endl;
//  for (const auto &data : set) {
//    cout << data.first << " ";
//  }
}

//TEST_F(S21Set_test, construct_copy) {
//  S21Set<int, int> set4(set3);
//  std::set<int, int> std_set4(std_set3);
//  for (auto &pair : std_set4) {
//    EXPECT_EQ(set4.at(pair.first), std_set4.at(pair.first));
//  }
//}
//
//TEST_F(S21Set_test, construct_move) {
//  S21Set<int, int> set4(std::move(set3));
//  std::set<int, int> std_set4(std::move(std_set3));
//  for (const auto &pair : std_set4) {
//    EXPECT_EQ(set4.at(pair.first), std_set4.at(pair.first));
//  }
//}
//
//TEST_F(S21Set_test, operator_copy) {
//  set_empty = set3;
//  std_set_empty = std_set3;
//  for (auto &pair : std_set_empty) {
//    EXPECT_EQ(set_empty.at(pair.first), std_set_empty.at(pair.first));
//  }
//}
//
//TEST_F(S21Set_test, operator_move) {
//  set_empty = std::move(set3);
//  std_set_empty = std::move(std_set3);
//  for (const auto &pair : std_set_empty) {
//    EXPECT_EQ(set_empty.at(pair.first), std_set_empty.at(pair.first));
//  }
//}
//
//TEST_F(S21Set_test, swap) {
//  S21Set<int, int> set5{{15, 25}, {12, 30}, {20, 50}};
//  std::set<int, int> std_set5{{15, 25}, {12, 30}, {20, 50}};
//  set3.swap(set5);
//  std_set3.swap(std_set5);
//  for (const auto &pair : std_set3) {
//    EXPECT_EQ(set3.at(pair.first), std_set3.at(pair.first));
//  }
//
//  for (const auto &pair : std_set5) {
//    EXPECT_EQ(set5.at(pair.first), std_set5.at(pair.first));
//  }
//
//  set_empty.swap(set5);
//  std_set_empty.swap(std_set5);
//  for (const auto &pair : std_set_empty) {
//    EXPECT_EQ(set_empty.at(pair.first), std_set_empty.at(pair.first));
//  }
//
//  for (const auto &pair : std_set5) {
//    EXPECT_EQ(set5.at(pair.first), std_set5.at(pair.first));
//  }
//}
//
//TEST_F(S21Set_test, size) {
//  EXPECT_EQ(set_empty.size(), std_set_empty.size());
//  EXPECT_EQ(set.size(), std_set.size());
//}
//
//TEST_F(S21Set_test, max_size) { EXPECT_EQ(set.max_size(), std_set.max_size()); }
//
//TEST_F(S21Set_test, clear) {
//  EXPECT_EQ(set.size(), std_set.size());
//  EXPECT_EQ(set_empty.size(), std_set_empty.size());
//  set.clear();
//  std_set.clear();
//  set_empty.clear();
//  std_set_empty.clear();
//  EXPECT_EQ(set_empty.size(), std_set_empty.size());
//  EXPECT_EQ(set.size(), std_set.size());
//  EXPECT_ANY_THROW(set.at(1));
//  EXPECT_ANY_THROW(std_set.at(1));
//}
//
//TEST_F(S21Set_test, it_begin) {
//  auto it = set.begin();
//  auto std_it = std_set.begin();
//  EXPECT_EQ(it->first, std_it->first);
//}
//
//TEST_F(S21Set_test, it_end) {
//  auto it = set.end();
//  auto std_it = std_set.end();
//  --it;
//  --std_it;
//  EXPECT_EQ(it->first, std_it->first);
//}
//
//TEST_F(S21Set_test, at) {
//  for (const auto &pair : std_set) {
//    EXPECT_EQ(set.at(pair.first), std_set.at(pair.first));
//  }
//  EXPECT_ANY_THROW(set.at(9));
//  EXPECT_ANY_THROW(set.at(9));
//}
//
//TEST_F(S21Set_test, operator_brkt) {
//  set[0];
//  set = std::move(set);
//  set[1] = 35;
//  set[9];
//  std_set[0];
//  std_set[1] = 35;
//  std_set[9];
//  EXPECT_EQ(set[1], 35);
//  EXPECT_EQ(set[0], std_set[0]);
//  EXPECT_EQ(set[1], std_set[1]);
//  EXPECT_EQ(set[9], std_set[9]);
//
//  set_s.insert(std::pair(1, "25"));
//  set_s.insert(std::pair(3, "50"));
//  std_set_s.insert(std::pair{1, "25"});
//  std_set_s.insert(std::pair{3, "50"});
//  set_s[1] = "43";
//  set_s[3];
//  set_s[9];
//  std_set_s[1] = "43";
//  std_set_s[3];
//  std_set_s[9];
//  EXPECT_EQ(set_s[1], std_set_s[1]);
//  EXPECT_EQ(set_s[3], std_set_s[3]);
//  EXPECT_EQ(set_s[9], std_set_s[9]);
//}
//
//TEST_F(S21Set_test, empty) {
//  EXPECT_TRUE(set_empty.empty());
//  EXPECT_TRUE(std_set_empty.empty());
//}
//
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
//TEST_F(S21Set_test, insert_or_assign) {
//  auto pr1 = set.insert_or_assign(9, 35);
//  auto pr2 = std_set.insert_or_assign(9, 35);
//
//  EXPECT_EQ(pr1.second, pr2.second);
//  EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);
//  auto pr3 = set.insert_or_assign(9, 48);
//  auto pr4 = std_set.insert_or_assign(9, 48);
//  EXPECT_EQ(pr3.second, pr4.second);
//  EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);
//
//  set_s.insert(std::pair(1, "25"));
//  auto pr_s1 = set_s.insert_or_assign(9, "35");
//  std_set_s.insert(std::pair{1, "25"});
//  auto pr_s2 = std_set_s.insert_or_assign(9, "35");
//
//  EXPECT_EQ(pr_s1.second, pr_s2.second);
//  EXPECT_EQ((*(pr_s1.first)).second, (*(pr_s2.first)).second);
//  auto pr_s3 = set_s.insert_or_assign(9, "48");
//  auto pr_s4 = std_set_s.insert_or_assign(9, "48");
//  EXPECT_EQ(pr_s3.second, pr_s4.second);
//  EXPECT_EQ((*(pr_s3.first)).second, (*(pr_s4.first)).second);
//}
//
//TEST_F(S21Set_test, erase) {
//  set_s.insert(1, "25");
//  set_s.insert(2, "55");
//  std_set_s.insert(std::pair(1, "25"));
//  std_set_s.insert(std::pair(2, "55"));
//  set3.erase((set3.begin()));
//  std_set3.erase((std_set3.begin()));
//  set_s.erase((set_s.begin()));
//  std_set_s.erase((std_set_s.begin()));
//
//  for (auto const &it : set3) {
//    EXPECT_EQ(set3.at(it.first),std_set3.at(it.first));
//  }
//
//  for (auto const &it : set_s) {
//    EXPECT_EQ(set_s.at(it.first),std_set_s.at(it.first));
//  }
//
//}
//
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

