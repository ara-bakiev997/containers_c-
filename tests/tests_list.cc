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
//  S21List<int> list_3_(S21List<int> list_2_);

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  std::list<std::string> test_string = {"a", "b", "c", "d"};
  //  std::list<int> test3 =  std::list<int>(10);
};

TEST_F(S21List_test, constructors) {
  ASSERT_EQ(list_empty.size(), test_empty.size());
  ASSERT_EQ(list_1_.size(), test1.size());
  ASSERT_EQ(list_2_.size(), test2.size());
//  const S21List<int> list_temp_ = {1, 2, 3, 4, 5};
//  S21List<int> list_3_(list_temp_);
//  list_3_

}

TEST_F(S21List_test, Access) {
  ASSERT_EQ(list_1_.front(), test1.front());
  ASSERT_EQ(list_1_.back(), test1.back());
  ASSERT_EQ(list_2_.front(), test2.front());
  ASSERT_EQ(list_2_.back(), test2.back());
}

TEST_F(S21List_test, Iterators) {
//  S21List<int>::iterator it =  list_2_.begin();
//  std::cout << *it << std::endl;
//  ++it;
//  ++it;
//  ++it;
//  std::cout << *it << std::endl;
//
//  auto it_or =  test2.begin();
//
//  std::cout << *it_or << std::endl;
//  ++it_or;
//  ++it_or;
//  ++it_or;
//  std::cout << *it_or << std::endl;
//
//

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