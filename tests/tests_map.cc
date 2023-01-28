//
// Created by Qyburn Bongo on 1/24/23.
//

#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include "../src/sorted_container/associative_container/s21_map.h"

using namespace s21;

class S21Map_test : public ::testing::Test {
protected:
    void SetUp() override {}
    S21Map<int, int> map;


};

TEST_F(S21Map_test, emplace) {

    map.insert(1, 25);
    map.insert(0, 4);
    map.insert(4, 4);
    map.clear();


    //    map.insert(2);
//    map.insert(3);
//    map.insert(4);
//    map.insert(6);
//    map.insert(5);
//    map.insert(8);
    
//    map.print();
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}