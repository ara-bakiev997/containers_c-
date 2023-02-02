//
// Created by Qyburn Bongo on 1/24/23.
//

#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include "../src/sorted_container/associative_container/s21_map.h"

using namespace s21;
using std::cout;
using std::endl;


class S21Map_test : public ::testing::Test {
protected:
    void SetUp() override {}
    S21Map<int, int> map;
    std::map<int, int> std_map;
//    S21Map<int, int> map2({10,50});
    std::map<int, int> std_map2{{10, 50}, {8, 60}, {6, 70}, {12, 40}, {14, 30}, {16, 20}};




};

TEST_F(S21Map_test, size) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));
    EXPECT_EQ(map.size(), std_map.size());
}

TEST_F(S21Map_test, max_size) {
    EXPECT_EQ(map.max_size(), std_map.max_size());
}

TEST_F(S21Map_test, clear) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));
    EXPECT_EQ(map.size(), std_map.size());
    map.clear();
    EXPECT_EQ(map.size(), std_map.size());
    EXPECT_ANY_THROW(map.at(1));
    EXPECT_ANY_THROW(map.at(1));
}

TEST_F(S21Map_test, at) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

    for (const auto &pair : std_map) {
    EXPECT_EQ(map.at(pair.first), std_map.at(pair.first));
    }
    EXPECT_ANY_THROW(map.at(9));
    EXPECT_ANY_THROW(map.at(9));
}

TEST_F(S21Map_test, operator_brkt) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

    map[0];
    map[1] = 35;
    map[9];
    std_map[0];
    std_map[1] = 35;
    std_map[9];
    EXPECT_EQ(map[1], 35);
    EXPECT_EQ(map[0], std_map[0]);
    EXPECT_EQ(map[1], std_map[1]);
    EXPECT_EQ(map[9], std_map[9]);
}

TEST_F(S21Map_test, empty) {
    EXPECT_TRUE(map.empty());
    EXPECT_TRUE(std_map.empty());
}

TEST_F(S21Map_test, insert_delete) {

    map.insert(std::pair(1, 25));
    auto pr = map.insert(std::pair(0, 43));
    auto pr2 =map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

    EXPECT_EQ(std_map.size(), 5);
//    map.clear();


    map.print();
//    cout<<map.max_size() << endl;
//    cout<<"std ="<<std_map.max_size() << endl;
//    cout<<map.size() << endl;
    cout<< (*(pr.first)).second << endl;
    cout<< (*(pr2.first)).second << endl;
    cout<< pr.second << endl;
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}