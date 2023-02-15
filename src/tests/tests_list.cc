#include <gtest/gtest.h>

#include <list>

#include "../sequence/s21_list.h"

using namespace s21;

struct A {
  std::string s;
  A(std::string str) : s(std::move(str)) {}
  A(const A &o) : s(o.s) {}
  A(A &&o) : s(std::move(o.s)) {}
  A &operator=(const A &other) {
    s = other.s;
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    return *this;
  }
};

struct President {
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {}
  President(President &&other)
      : name(std::move(other.name)), country(std::move(other.country)),
        year(other.year) {}
  President &operator=(const President &other) = default;
};

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
  S21List<int> list_sort = {9, 8, 7, 6, 6, 6,    5,  8, 8,
                            9, 4, 3, 2, 1, -153, -1, 0};
  S21List<std::string> list_sort_string = {"ad", "bc", "bd", "ac"};
  S21List<A> list_obj;
  S21List<President> list_elections;

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  std::list<int> test3 = {6, 7, 8, 9, 10};
  std::list<int> test4 = {1, 2, 3, 8, 9};
  std::list<int> test5 = {1, 1, 2, 3, 2, 4, 5, 5, 6};
  std::list<std::string> test_string = {"a", "b", "c", "d"};
  std::list<int> test_sort = {9, 8, 7, 6, 6, 6,    5,  8, 8,
                              9, 4, 3, 2, 1, -153, -1, 0};
  std::list<std::string> test_sort_string = {"ad", "bc", "bd", "ac"};
  std::list<A> test_obj;
  std::list<President> test_elections;
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

TEST_F(S21List_test, operatorAssignments) {
  list_2_ = list_3_;
  test2 = test3;
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  while (it != list_2_.end() && it_or != test2.end()) {
    EXPECT_EQ(*(it++), *(it_or++));
  }
  auto it2 = list_3_.begin();
  auto it_or2 = test3.begin();
  while (it2 != list_3_.end() && it_or2 != test3.end()) {
    EXPECT_EQ(*(it2++), *(it_or2++));
  }
}

TEST_F(S21List_test, operatorAssignmentsMoving) {
  list_2_ = std::move(list_3_);
  test2 = std::move(test3);
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  while (it != list_2_.end() && it_or != test2.end()) {
    EXPECT_EQ(*(it++), *(it_or++));
  }
  auto it2 = list_3_.begin();
  auto it_or2 = test3.begin();
  while (it2 != list_3_.end() && it_or2 != test3.end()) {
    EXPECT_EQ(*(it2++), *(it_or2++));
  }
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
  //  EXPECT_EQ(list_string.max_size(), test_string.max_size());
  //  EXPECT_EQ(list_elections.max_size(), test_elections.max_size());
  //  EXPECT_EQ(list_obj.max_size(), test_obj.max_size());
  EXPECT_EQ(list_1_.max_size(), test1.max_size());
  EXPECT_EQ(list_2_.max_size(), test2.max_size());
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
  EXPECT_EQ(list_2_.size(), test2.size()); // ha-ha, orig ++size
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
  std::string temp = {"bro"};
  list_string.push_front(temp);
  test_string.push_front(temp);
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
  auto it_or = test_sort.begin();
  auto it = list_sort.begin();
  test_sort.sort();
  list_sort.sort();
  while (it_or != test_sort.end() || it != list_sort.end()) {
    EXPECT_EQ(*it_or, *it);
    ++it_or, ++it;
  }
  auto it_or_string = test_sort_string.begin();
  auto it_string = list_sort_string.begin();
  test_sort_string.sort();
  list_sort_string.sort();
  while (it_or_string != test_sort_string.end() ||
         it_string != list_sort_string.end()) {
    EXPECT_EQ(*it_or_string, *it_string);
    ++it_or_string, ++it_string;
  }
}

TEST_F(S21List_test, BonusEmplace) {
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  list_2_.emplace(it, 2);
  test2.emplace(it_or, 2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
  // test obj N1
  A two{"two"};
  A three{"three"};
  A three_or{"three"};
  list_obj.emplace(list_obj.end(), "one");
  test_obj.emplace(test_obj.end(), "one");
  auto it_obj = list_obj.begin();
  auto it_obj_or = test_obj.begin();
  while (it_obj != list_obj.end() || it_obj_or != test_obj.end()) {
    EXPECT_EQ((*it_obj).s, (*it_obj_or).s);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(list_obj.size(), test_obj.size());
  //   test obj N2
  list_obj.emplace(list_obj.end(), two);
  test_obj.emplace(test_obj.end(), two);
  it_obj = list_obj.begin();
  it_obj_or = test_obj.begin();
  while (it_obj != list_obj.end() || it_obj_or != test_obj.end()) {
    EXPECT_EQ((*it_obj).s, (*it_obj_or).s);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(list_obj.size(), test_obj.size());
  //   test obj N3
  list_obj.emplace(list_obj.end(), std::move(three));
  test_obj.emplace(test_obj.end(), std::move(three_or));
  it_obj = list_obj.begin();
  it_obj_or = test_obj.begin();
  while (it_obj != list_obj.end() || it_obj_or != test_obj.end()) {
    EXPECT_EQ((*it_obj).s, (*it_obj_or).s);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(list_obj.size(), test_obj.size());
}

TEST_F(S21List_test, BonusEmplaceBack) {
  list_2_.emplace_back(2);
  test2.emplace_back(2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
  // test obj N1
  list_elections.emplace_back("Nelson Mandela", "South Africa", 1994);
  test_elections.emplace_back("Nelson Mandela", "South Africa", 1994);
  auto it_obj = list_elections.begin();
  auto it_obj_or = test_elections.begin();
  while (it_obj != list_elections.end() || it_obj_or != test_elections.end()) {
    EXPECT_EQ((*it_obj).country, (*it_obj_or).country);
    EXPECT_EQ((*it_obj).name, (*it_obj_or).name);
    EXPECT_EQ((*it_obj).year, (*it_obj_or).year);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(list_elections.size(), test_elections.size());
  // test obj N2
  S21List<President> reElections;
  std::list<President> reElections_or;
  reElections.push_back(
      President("Franklin Delano Roosevelt", "the USA", 1936));
  reElections_or.push_back(
      President("Franklin Delano Roosevelt", "the USA", 1936));
  it_obj = reElections.begin();
  it_obj_or = reElections_or.begin();
  while (it_obj != reElections.end() || it_obj_or != reElections_or.end()) {
    EXPECT_EQ((*it_obj).country, (*it_obj_or).country);
    EXPECT_EQ((*it_obj).name, (*it_obj_or).name);
    EXPECT_EQ((*it_obj).year, (*it_obj_or).year);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(reElections.size(), reElections_or.size());
}

TEST_F(S21List_test, BonusEmplaceFront) {
  list_2_.emplace_front(2);
  test2.emplace_front(2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
  // test obj N1
  list_elections.emplace_front("Nelson Mandela", "South Africa", 1994);
  test_elections.emplace_front("Nelson Mandela", "South Africa", 1994);
  auto it_obj = list_elections.begin();
  auto it_obj_or = test_elections.begin();
  while (it_obj != list_elections.end() || it_obj_or != test_elections.end()) {
    EXPECT_EQ((*it_obj).country, (*it_obj_or).country);
    EXPECT_EQ((*it_obj).name, (*it_obj_or).name);
    EXPECT_EQ((*it_obj).year, (*it_obj_or).year);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(list_elections.size(), test_elections.size());
  // test obj N2
  S21List<President> reElections;
  std::list<President> reElections_or;
  reElections.push_front(
      President("Franklin Delano Roosevelt", "the USA", 1936));
  reElections_or.push_front(
      President("Franklin Delano Roosevelt", "the USA", 1936));
  it_obj = reElections.begin();
  it_obj_or = reElections_or.begin();
  while (it_obj != reElections.end() || it_obj_or != reElections_or.end()) {
    EXPECT_EQ((*it_obj).country, (*it_obj_or).country);
    EXPECT_EQ((*it_obj).name, (*it_obj_or).name);
    EXPECT_EQ((*it_obj).year, (*it_obj_or).year);
    ++it_obj, ++it_obj_or;
  }
  EXPECT_EQ(reElections.size(), reElections_or.size());
}
