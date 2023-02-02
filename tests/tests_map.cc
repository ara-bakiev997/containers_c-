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



};

TEST_F(S21Map_test, size) {
    EXPECT_EQ(map.size(), std_map.size());
}

TEST_F(S21Map_test, max_size) {
    EXPECT_EQ(map.max_size(), std_map.max_size());
}

TEST_F(S21Map_test, clear) {
    map.clear();
    EXPECT_EQ(map.size(), std_map.size());
}

TEST_F(S21Map_test, insert_delete) {

    map.insert(1, 25);
    auto pr = map.insert(std::pair(1, 43));
    auto pr2 =map.insert(std::pair(4, 4));
    map.insert(7, 11);
    std_map.insert(std::pair{1, 180});
    std_map.insert(std::pair(0, 4));
    std_map.insert(std::pair(4, 4));

    EXPECT_EQ(std_map.size(), 3);
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