#include <gtest/gtest.h>

//#include <utility>
#include <vector>
#include <cstring>
#include "../src/sequence/s21_vector.h"

using namespace s21;

class S21Point {
public:
//    ~S21Point() {
//        vector = {"0"};
//    }
    int get_x () const {
        return x_;
    }
    void set_x (int x) {
        x_ = x;
    }
    std::string vector{"hello"};
private:
    int x_{};
};

class S21Vector_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  S21Vector<int> vector_empty;
  S21Vector<int> vector_1_ = {1, 2, 3, 4, 5};
  S21Vector<int> vector_2_ = S21Vector<int>(10);
  S21Vector<int> vector_3_ = {5, 4, 3, 2, 1};
  S21Vector<S21Point> pvector{S21Point(), S21Point(), S21Point()};
  std::vector<int> test_empty;
  std::vector<int> test = {1, 2, 3, 4, 5};
  std::vector<int> test2 = {10, 20, 30, 40};
  std::vector<int> test3 = {5, 4, 3, 2, 1};
//  std::vector<int> test8 = std::vector<int>(5);
  std::vector<S21Point> ptest = {S21Point(), S21Point(), S21Point()};
};

TEST_F(S21Vector_test, constructor_copy) {
    S21Vector<int> vector_5 = vector_1_;
    std::vector<int> test5 = test;
    EXPECT_EQ(vector_5.size(), test5.size());
    for (auto i = 0; i < vector_5.size(); ++i)
        EXPECT_EQ(vector_5.at(i), test5.at(i));
}

TEST_F(S21Vector_test, constructor_init_list) {
    S21Vector<int> vector_6 = {9, 8, 7, 6, 5};
    std::vector<int> test6 = {9, 8, 7, 6, 5};
    EXPECT_EQ(vector_6.size(), test6.size());
    for (auto i = 0; i < vector_6.size(); ++i)
        EXPECT_EQ(vector_6.at(i), test6.at(i));
    EXPECT_EQ(pvector.size(), ptest.size());
    EXPECT_EQ(pvector[1].get_x(), ptest[1].get_x());
    ptest[1].set_x(5);
    pvector[1].set_x(5);
    EXPECT_EQ(pvector[1].get_x(), ptest[1].get_x());
//    std::cout <<ptest[1].get_x() << std::endl;
//    std::cout <<ptest[2].get_x() << std::endl;
}

TEST_F(S21Vector_test, constructor_move) {
    S21Vector<int> vector_4 = std::move(vector_1_);
    std::vector<int> test4 = std::move(test);
    EXPECT_EQ(vector_4.size(), test4.size());
    for (auto i = 0; i < vector_4.size(); ++i)
        EXPECT_EQ(vector_4.at(i), test4.at(i));
//    std::cout <<ptest.size() << std::endl;
//    std::cout <<pvector.size() << std::endl;

}

TEST_F(S21Vector_test, _operatorCopy) {
  vector_empty = vector_1_;
  for (auto i = 0; i < vector_empty.size(); ++i) {
    EXPECT_EQ(vector_empty.at(i), vector_1_.at(i));
  }
}

TEST_F(S21Vector_test, _operatorMove) {
    S21Vector<int> vector_7_ = {1, 2, 3, 4, 5};
    std::vector<int> test7 = {1, 2, 3, 4, 5};
    vector_empty = std::move(vector_7_);
    test_empty = std::move(test7);
    for (auto i = 0; i < vector_empty.size(); ++i) {
        EXPECT_EQ(vector_empty.at(i), test_empty.at(i));
    }
//    std::cout <<test7.data() << std::endl;
//    std::cout <<vector_7_.data() << std::endl;
}

TEST_F(S21Vector_test, at) {
  EXPECT_EQ(vector_1_.at(0), test.at(0));
  EXPECT_EQ(vector_1_.at(1), test.at(1));
  EXPECT_ANY_THROW(vector_1_.at(7));
  EXPECT_ANY_THROW(vector_empty.at(0));
}

TEST_F(S21Vector_test, brackets) {}

TEST_F(S21Vector_test, front) { EXPECT_EQ(vector_1_.front(), 1); }

TEST_F(S21Vector_test, back) { EXPECT_EQ(vector_1_.back(), 5); }

TEST_F(S21Vector_test, data) { EXPECT_EQ(*vector_1_.data(), 1); }

TEST_F(S21Vector_test, iterator_begin) { EXPECT_EQ((*vector_1_.begin()), 1); }

TEST_F(S21Vector_test, iterator_end) { EXPECT_EQ(*(vector_1_.end() - 1), 5); }

TEST_F(S21Vector_test, empty) {
  EXPECT_TRUE(vector_empty.empty());
  EXPECT_FALSE(vector_1_.empty());
}

TEST_F(S21Vector_test, size) {
  EXPECT_EQ(vector_empty.size(), 0);
  EXPECT_EQ(vector_1_.size(), 5);
//  EXPECT_EQ(ptest.size(), pvector.size());
}

 TEST_F(S21Vector_test, max_size) {
   EXPECT_EQ(test.max_size(), vector_1_.max_size());
   std::cout << test.max_size() << std::endl;
   std::cout << vector_1_.max_size() << std::endl;
 }

TEST_F(S21Vector_test, reserve) {
    std::cout << vector_1_.data() << std::endl;
    EXPECT_ANY_THROW(vector_1_.reserve(vector_1_.max_size() + 1));
    EXPECT_EQ(vector_1_.capacity(), 5);
    vector_1_.reserve(10);
    EXPECT_EQ(vector_1_.capacity(), 10);

    for (auto i = 0; i < vector_1_.size(); ++i) {
        std::cout << vector_1_.at(i) << std::endl;
    }
    std::cout << vector_1_.capacity() << std::endl;
    std::cout << vector_1_.data() << std::endl;


    S21Vector<S21Point> vector_test(3);
    std::cout << vector_test.at(0).vector << std::endl;

    vector_test.reserve(2);
    std::cout << vector_test.at(0).vector << std::endl;
    std::cout << vector_test[2].vector << std::endl;

}

TEST_F(S21Vector_test, capasity) { EXPECT_EQ(vector_1_.capacity(), 5); }

TEST_F(S21Vector_test, shrink_to_fit) {
  vector_1_.push_back(3);
  EXPECT_EQ(vector_1_.capacity(), 10);
  vector_1_.shrink_to_fit();
  EXPECT_EQ(vector_1_.capacity(), vector_1_.size());
  EXPECT_EQ(vector_1_.size(), 6);
}

TEST_F(S21Vector_test, push_back) {
  vector_empty.push_back(0);
  vector_1_.push_back(6);
  pvector.push_back(S21Point());
  EXPECT_EQ(vector_1_.at(5), 6);
  EXPECT_EQ( pvector.size(), 4);
  std::cout <<pvector.size() << std::endl;
}

TEST_F(S21Vector_test, clear) {
  EXPECT_EQ(vector_1_.size(), 5);
  vector_1_.clear();
  EXPECT_EQ(vector_1_.size(), 0);
}

TEST_F(S21Vector_test, insert) {
  vector_1_.insert(vector_1_.end() - 1, 19);
  test.insert(test.end() - 1, 19);
  for (auto i = 0; i < vector_1_.size(); ++i)
        EXPECT_EQ(vector_1_.at(i), test.at(i));
}

TEST_F(S21Vector_test, erase) {
  vector_1_.erase(vector_1_.begin());
  test.erase(test.begin());
  EXPECT_EQ(vector_1_.at(0), test.at(0));
  vector_1_.erase(vector_1_.begin() + 1);
  test.erase(test.begin() + 1);
  EXPECT_EQ(vector_1_.at(1), test.at(1));
  vector_1_.erase(vector_1_.end() - 1);
  test.erase(test.end() - 1);
  EXPECT_EQ(vector_1_.at(vector_1_.size() - 1), test.at(test.size() - 1));
  test_empty.erase(test_empty.end() - 1);
  vector_empty.erase(vector_empty.end() - 1);
  EXPECT_EQ(test_empty.size(), vector_empty.size());
}

TEST_F(S21Vector_test, popback) {
  EXPECT_EQ(vector_1_.size(), 5);
  vector_1_.pop_back();
  EXPECT_EQ(vector_1_.size(), 4);
  test_empty.pop_back();
  vector_empty.pop_back();
  EXPECT_EQ(vector_empty.data(), test_empty.data());
  EXPECT_EQ(vector_empty.size(), test_empty.size());
  EXPECT_EQ(vector_empty.capacity(), test_empty.capacity());
}

TEST_F(S21Vector_test, swap) {
    vector_1_.swap(vector_3_);
    test.swap(test3);
    EXPECT_EQ(vector_1_.size(), test.size());
    EXPECT_EQ(vector_1_.capacity(), test.capacity());
    for (auto i = 0; i < vector_1_.size(); ++i)
        EXPECT_EQ(vector_1_.at(i), test.at(i));
}


TEST_F(S21Vector_test, emplace_back) {

}

TEST_F(S21Vector_test, emplace) {

}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}