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
  S21List<int> list_3_ = {6, 7, 8, 9, 10};
  S21List<int> list_4_ = {1, 2, 3, 8, 9};
  S21List<int> list_5_ = {1, 1, 2, 3, 2, 4, 5, 5, 6};
  S21List<std::string> list_string = {"a", "b", "c", "d"};

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  std::list<int> test3 = {6, 7, 8, 9, 10};
  std::list<int> test4 = {1, 2, 3, 8, 9};
  std::list<int> test5 = {1, 1, 2, 3, 2, 4, 5, 5, 6};
  std::list<std::string> test_string = {"a", "b", "c", "d"};
};

TEST_F(S21List_test, constructors) {
  EXPECT_EQ(list_empty.size(), test_empty.size());
  EXPECT_EQ(list_1_.size(), test1.size());
  EXPECT_EQ(list_2_.size(), test2.size());
  // Copy
  S21List<int> list_3_(list_2_);
  std::list<int> test3(test2);
  auto it = list_3_.begin();
  auto it_or = test3.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  //  // Move
  S21List<int> list_4_ = std::move(list_3_);
  std::list<int> test4 = std::move(test3);
  EXPECT_EQ(list_4_.size(), test4.size());
  EXPECT_EQ(list_3_.size(), test3.size());
  it = list_4_.begin();
  it_or = test4.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
}

TEST_F(S21List_test, Access) {
  EXPECT_EQ(list_1_.front(), test1.front());
  EXPECT_EQ(list_1_.back(), test1.back());
  EXPECT_EQ(list_2_.front(), test2.front());
  EXPECT_EQ(list_2_.back(), test2.back());
}

TEST_F(S21List_test, Iterators) {
  auto it = list_string.begin();
  auto it_or = test_string.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  EXPECT_EQ(*(it++), *(it_or++));
  it++, ++it_or;
  EXPECT_EQ(*it, *it_or);
  it = list_string.end();
  it_or = test_string.end();
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  EXPECT_EQ(*(it--), *(it_or--));
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
}

TEST_F(S21List_test, Capacity) {
  EXPECT_EQ(list_empty.empty(), test_empty.empty());
  EXPECT_EQ(list_1_.empty(), test1.empty());
  EXPECT_EQ(list_2_.empty(), test2.empty());
  EXPECT_EQ(list_empty.empty(), test_empty.empty());
  EXPECT_EQ(list_1_.empty(), test1.empty());
  EXPECT_EQ(list_2_.empty(), test2.empty());
  EXPECT_EQ(list_string.empty(), test_string.empty());
  EXPECT_EQ(list_string.size(), test_string.size());
}

TEST_F(S21List_test, ModifiersClear) {
  list_2_.clear();
  test2.clear();
  EXPECT_EQ(list_2_.empty(), test2.empty());
  list_2_.push_front(1);
  list_2_.push_back(5);
  test2.push_front(1);
  test2.push_back(5);
  EXPECT_EQ(list_empty.size(), test_empty.size());
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
}

TEST_F(S21List_test, ModifiersInsert) {
  auto it = list_string.begin();
  auto it_or = test_string.begin();
  auto ret = list_string.insert(it, "qwerty");
  auto ret_or = test_string.insert(it_or, "qwerty");
  EXPECT_EQ(*it, *it_or);
  EXPECT_EQ(*ret, *ret_or);
  EXPECT_EQ(*(++it), *(++it_or));
  EXPECT_EQ(*(++ret), *(++ret_or));
  it = list_string.end();
  it_or = test_string.end();
  ret = list_string.insert(it, "asdf");
  ret_or = test_string.insert(it_or, "asdf");
  EXPECT_EQ(*ret, *ret_or);
  EXPECT_EQ(*(--ret), *(--ret_or));
  // Empty list
  auto it_em = list_empty.begin();
  auto it_em_or = test_empty.begin();
  auto ret_em = list_empty.insert(it_em, 1);
  auto ret_em_or = test_empty.insert(it_em_or, 1);
  EXPECT_EQ(*ret_em, *ret_em_or);
  list_empty.insert(it_em, 10);
  test_empty.insert(it_em_or, 10);
  EXPECT_EQ(*(++it_em), *(++it_em_or));

  // Another object iterator
  auto an = list_1_.begin();
  auto an_or = test1.begin();
  EXPECT_EQ(list_2_.size(), test2.size());
  ret_em = list_2_.insert(an, 11);
  ret_em_or = test2.insert(an_or, 11);
  EXPECT_EQ(list_2_.size(), test2.size());  // ha-ha, orig ++size
  EXPECT_EQ(*ret_em, *ret_em_or);
}

TEST_F(S21List_test, ModifiersErase) {
  auto it = list_string.begin();
  auto it_or = test_string.begin();
  list_string.erase(it);
  test_string.erase(it_or);
  EXPECT_EQ(list_string.size(), test_string.size());
  it = list_string.begin();
  it_or = test_string.begin();
  EXPECT_EQ(*it, *it_or);
  // Another list
  auto an = list_1_.begin();
  auto an_or = test1.begin();
  EXPECT_EQ(list_2_.size(), test2.size());
  list_2_.erase(an);
  test2.erase(an_or);
  EXPECT_EQ(list_2_.size(), test2.size());
}

TEST_F(S21List_test, ModifiersPush) {
  list_empty.push_front(10);
  test_empty.push_front(10);
  EXPECT_EQ(list_empty.empty(), test_empty.empty());
  EXPECT_EQ(list_empty.front(), test_empty.front());
  list_empty.push_back(20);
  test_empty.push_back(20);
  EXPECT_EQ(list_empty.back(), test_empty.back());
  EXPECT_EQ(list_empty.size(), test_empty.size());

  list_string.push_front("bro");
  test_string.push_front("bro");
  EXPECT_EQ(list_string.empty(), test_string.empty());
  EXPECT_EQ(list_string.front(), test_string.front());
  list_string.push_back("s21");
  test_string.push_back("s21");
  EXPECT_EQ(list_string.back(), test_string.back());
  EXPECT_EQ(list_string.size(), test_string.size());
}

TEST_F(S21List_test, ModifiersPop) {
  list_string.pop_front();
  test_string.pop_front();
  EXPECT_EQ(list_string.empty(), test_string.empty());
  EXPECT_EQ(list_string.front(), test_string.front());
  list_string.pop_back();
  test_string.pop_back();
  EXPECT_EQ(list_string.back(), test_string.back());
  EXPECT_EQ(list_string.size(), test_string.size());
}

TEST_F(S21List_test, ModifiersSwap) {
  EXPECT_EQ(*list_2_.begin(), *test2.begin());
  EXPECT_EQ(*list_1_.begin(), *test1.begin());
  list_1_.swap(list_2_);
  test1.swap(test2);
  EXPECT_EQ(*list_2_.begin(), *test2.begin());
  EXPECT_EQ(*list_1_.begin(), *test1.begin());
  EXPECT_EQ(list_1_.size(), test1.size());
  EXPECT_EQ(list_1_.size(), test2.size());
}

TEST_F(S21List_test, ModifiersMerge) {
  EXPECT_EQ(list_3_.size(), test3.size());
  EXPECT_EQ(list_4_.size(), test4.size());
  list_3_.merge(list_4_);
  test3.merge(test4);
  auto it_or = list_3_.begin();
  auto it = test3.begin();
  while (it_or != list_3_.end() || it != test3.end()) {
    EXPECT_EQ(*it_or, *it);
    ++it_or, ++it;
  }
  EXPECT_EQ(list_3_.size(), test3.size());
  EXPECT_EQ(list_4_.size(), test4.size());
}

TEST_F(S21List_test, ModifiersSplice) {
  EXPECT_EQ(list_1_.size(), test1.size());
  EXPECT_EQ(list_2_.size(), test2.size());
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  ++it;
  ++it_or;
  list_2_.splice(it, list_1_);
  test2.splice(it_or, test1);
  EXPECT_EQ(list_1_.size(), test1.size());
  EXPECT_EQ(list_2_.size(), test2.size());
  EXPECT_EQ(*list_2_.begin(), *test2.begin());
  EXPECT_EQ(*(++list_2_.begin()), *(++test2.begin()));
}

TEST_F(S21List_test, ModifiersReverse) {
  EXPECT_EQ(*list_2_.begin(), *test2.begin());
  EXPECT_EQ(*(++list_2_.begin()), *(++test2.begin()));
  list_2_.reverse();
  test2.reverse();
  EXPECT_EQ(*list_2_.begin(), *test2.begin());
  EXPECT_EQ(*(++list_2_.begin()), *(++test2.begin()));
}

TEST_F(S21List_test, ModifiersUnique) {
  EXPECT_EQ(list_5_.size(), test5.size());
  list_5_.unique();
  test5.unique();
  auto it_or = list_5_.begin();
  auto it = test5.begin();
  while (it_or != list_5_.end() || it != test5.end()) {
    EXPECT_EQ(*it_or, *it);
    ++it_or, ++it;
  }
  EXPECT_EQ(list_5_.size(), test5.size());
}

TEST_F(S21List_test, ModifiersSort) {
  S21List<int> test_sort = {3, 1};
  for (auto i : test_sort) std::cout << i << ' '; std::cout << std::endl;
  test_sort.sort();

  for (auto i : test_sort) std::cout << i << ' '; std::cout << std::endl;

}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}