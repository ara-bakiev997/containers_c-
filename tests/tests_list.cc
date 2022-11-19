#include <gtest/gtest.h>

// #include <utility>
#include <list>

#include "../src/sequence/s21_list.h"

using namespace s21;

class S21List_test : public ::testing::Test {
protected:
  void SetUp() override {}
//  S21List<int> list_empty;
//  S21List<int> list_1_ = S21List<int>(5);
//    S21List<int> list_2_ = {1, 2, 3, 4, 5};
  //  S21List<int> list_3_ = S21List<int>(10);

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  //  std::list<int> test3 =  std::list<int>(10);
};

TEST_F(S21List_test, constructors) {
//  list_2_.print();
//S21List<int> list_empty;
//S21List<int> list_1_ = S21List<int>(5);
//S21List<int> list_2_ = {1, 2};
//list_2_.print();
S21List<int> list_2_ = {1, 2, 3, 4, 5};
  list_2_.print();
  list_2_.push_back(6);
  list_2_.push_back(7);
  list_2_.print();
  list_2_.pop_back();
  list_2_.print();



  //  auto it = list_2_.begin();
  //  std::cout << *it << std::endl;
  //  std::cout << *(++it) << std::endl;
  //  std::cout << *(++it) << std::endl;

  //  std::list<int> test3{1, 2};
  //  auto it = test3.begin();
  //  std::cout << test3.front() << ' ';
  //  Используй фэйковую ноду
  //  std::cout << &(*(it)) << " " << (*(it)) << '\n';
  //  std::cout << &(*(++it)) << " " << (*(it))<< '\n';
  //  std::cout << &(*(++it)) << " " << (*(it))<< '\n';
  //  std::cout << &(*(++it)) << " " << (*(it))<< '\n';
  //  std::cout << &(*(++it)) << " " << (*(it))<< '\n';
  //  std::cout << &(*(++it)) << " " << (*(it))<< '\n';
  //
  //  for (auto i : test3) {
  //    std::cout << i << ' ';
  //  }
  //  std::cout << "\n___________\n";

//      ASSERT_EQ(list_empty.size(), test_empty.size());
//      ASSERT_EQ(list_1_.size(), test1.size());
//      ASSERT_EQ(list_2_.size(), test2.size());
//      ASSERT_EQ(list_3_.size(), test3.size());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}