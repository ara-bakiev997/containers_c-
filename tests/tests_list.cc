#include <gtest/gtest.h>

// #include <utility>
#include <cstring>
#include <list>

#include "../src/sequence/list/s21_list.h"

using namespace s21;

class S21List_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21List<int> list_empty;
  S21List<int> list_1_ = S21List<int>(5);
  S21List<int> list_2_ = {1, 2, 3, 4, 5};
  S21List<std::string> list_string = {"a", "b", "c", "d"};

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  std::list<std::string> test_string = {"a", "b", "c", "d"};
};

TEST_F(S21List_test, constructors) {
  ASSERT_EQ(list_empty.size(), test_empty.size());
  ASSERT_EQ(list_1_.size(), test1.size());
  ASSERT_EQ(list_2_.size(), test2.size());
  // Copy
  S21List<int> list_3_(list_2_);
  std::list<int> test3(test2);
  auto it = list_3_.begin();
  auto it_or = test3.begin();
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  // Move
  S21List<int> list_4_ = std::move(list_3_);
  std::list<int> test4 = std::move(test3);
  ASSERT_EQ(list_4_.size(), test4.size());
  ASSERT_EQ(list_3_.size(), test3.size());
  it = list_4_.begin();
  it_or = test4.begin();
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
}

TEST_F(S21List_test, Access) {
  ASSERT_EQ(list_1_.front(), test1.front());
  ASSERT_EQ(list_1_.back(), test1.back());
  ASSERT_EQ(list_2_.front(), test2.front());
  ASSERT_EQ(list_2_.back(), test2.back());
}

TEST_F(S21List_test, Iterators) {
  auto it = list_string.begin();
  auto it_or = test_string.begin();
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
  ASSERT_EQ(*(it++), *(it_or++));
  it++, ++it_or;
  ASSERT_EQ(*it, *it_or);
  it = list_string.end();
  it_or = test_string.end();
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
  ASSERT_EQ(*(it--), *(it_or--));
  --it, --it_or;
  ASSERT_EQ(*it, *it_or);
}

TEST_F(S21List_test, Capacity) {
  ASSERT_EQ(list_empty.empty(), test_empty.empty());
  ASSERT_EQ(list_1_.empty(), test1.empty());
  ASSERT_EQ(list_2_.empty(), test2.empty());
  ASSERT_EQ(list_empty.empty(), test_empty.empty());
  ASSERT_EQ(list_1_.empty(), test1.empty());
  ASSERT_EQ(list_2_.empty(), test2.empty());
  ASSERT_EQ(list_string.empty(), test_string.empty());
  ASSERT_EQ(list_string.size(), test_string.size());
}

TEST_F(S21List_test, ModifiersClear) {
  list_2_.clear();
  test2.clear();
  ASSERT_EQ(list_2_.empty(), test2.empty());
  list_2_.push_front(1);
  list_2_.push_back(5);
  test2.push_front(1);
  test2.push_back(5);
  ASSERT_EQ(list_empty.size(), test_empty.size());
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  ASSERT_EQ(*it, *it_or);
  ++it, ++it_or;
  ASSERT_EQ(*it, *it_or);
}

TEST_F(S21List_test, ModifiersInsert) {
  S21List<int> test5 = {1, 2, 3, 4, 5};
  for (auto i : test5) std::cout << i << ' ';
  std::cout << '\n';
  auto it = test5.end();
//  ++it;
  test5.insert(it, 6);
  for (auto i : test5) std::cout << i << ' ';
  it = test5.end();
  std::cout << '\n';
  test5.insert(it, 7);
  for (auto i : test5) std::cout << i << ' ';

}

TEST_F(S21List_test, ModifiersPush) {
  list_empty.push_front(10);
  test_empty.push_front(10);
  ASSERT_EQ(list_empty.empty(), test_empty.empty());
  ASSERT_EQ(list_empty.front(), test_empty.front());
  list_empty.push_back(20);
  test_empty.push_back(20);
  ASSERT_EQ(list_empty.back(), test_empty.back());
  ASSERT_EQ(list_empty.size(), test_empty.size());

  list_string.push_front("bro");
  test_string.push_front("bro");
  ASSERT_EQ(list_string.empty(), test_string.empty());
  ASSERT_EQ(list_string.front(), test_string.front());
  list_string.push_back("s21");
  test_string.push_back("s21");
  ASSERT_EQ(list_string.back(), test_string.back());
  ASSERT_EQ(list_string.size(), test_string.size());
}

TEST_F(S21List_test, ModifiersPop) {
  list_string.pop_front();
  test_string.pop_front();
  ASSERT_EQ(list_string.empty(), test_string.empty());
  ASSERT_EQ(list_string.front(), test_string.front());
  list_string.pop_back();
  test_string.pop_back();
  ASSERT_EQ(list_string.back(), test_string.back());
  ASSERT_EQ(list_string.size(), test_string.size());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}